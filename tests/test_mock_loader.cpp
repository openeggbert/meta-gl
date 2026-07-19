#include <metagl/metagl.hpp>
#include <GLES3/gl32.h>
#include <cstring>
#include <iostream>

// =============================================================================
// I9 — Mock-loader integration test
//
// Provides stub GL function pointers so Initialize() completes without a
// real GPU. Verifies loader state and context detection.
// =============================================================================

namespace
{
    // Stubs for functions called by UpdateContextAfterLoad() -------------------

    const char* mock_version = "OpenGL ES 3.0 Mock";
    const char* omitted_function = nullptr;

    const GLubyte* GL_APIENTRY stub_GetString(GLenum name)
    {
        static const GLubyte vendor[]   = "MockVendor";
        static const GLubyte renderer[] = "MockRenderer";
        static const GLubyte glsl[]     = "OpenGL ES GLSL ES 3.00";
        static const GLubyte empty[]    = "";
        if (name == GL_VERSION)
            return reinterpret_cast<const GLubyte*>(mock_version);
        if (name == GL_VENDOR)                   return vendor;
        if (name == GL_RENDERER)                 return renderer;
        if (name == GL_SHADING_LANGUAGE_VERSION) return glsl;
        return empty;
    }

    void GL_APIENTRY stub_GetIntegerv(GLenum pname, GLint* params)
    {
        if (!params) return;
        *params = 0;
        if (pname == GL_MAJOR_VERSION)   *params = 3;
        if (pname == GL_MINOR_VERSION)   *params = 0;
        if (pname == GL_NUM_EXTENSIONS)  *params = 0;
    }

    const GLubyte* GL_APIENTRY stub_GetStringi(GLenum /*name*/, GLuint /*index*/)
    {
        static const GLubyte empty[] = "";
        return empty;
    }

    GLenum GL_APIENTRY stub_GetError()
    {
        return GL_NO_ERROR;
    }

    GLint GL_APIENTRY stub_GetAttribLocation(GLuint, const GLchar*)
    {
        return -1;
    }

    const GLubyte* GL_APIENTRY stub_DesktopGetString(GLenum name)
    {
        static const GLubyte version[]  = "4.6.0 Mock Desktop";
        static const GLubyte vendor[]   = "MockVendor";
        static const GLubyte renderer[] = "Mock Desktop Renderer";
        static const GLubyte glsl[]     = "4.60 Mock";
        static const GLubyte empty[]    = "";
        if (name == GL_VERSION)                  return version;
        if (name == GL_VENDOR)                   return vendor;
        if (name == GL_RENDERER)                 return renderer;
        if (name == GL_SHADING_LANGUAGE_VERSION) return glsl;
        return empty;
    }

    const GLubyte* GL_APIENTRY stub_AngleGetString(GLenum name)
    {
        static const GLubyte renderer[] =
            "ANGLE (Mock GPU, Vulkan 1.3)";
        if (name == GL_RENDERER) return renderer;
        return stub_GetString(name);
    }

    int desktop_depth_range_calls = 0;
    int desktop_clear_depth_calls = 0;

    struct ClearBufferCall
    {
        GLenum buffer = GL_NONE;
        GLint drawbuffer = -1;
        GLfloat depth = 0.0f;
        GLint stencil = 0;
    };

    ClearBufferCall clear_buffer_call;

    struct CopyImageCall
    {
        GLuint src_name = 0;
        GLenum src_target = GL_NONE;
        GLint src_level = -1;
        GLint src_x = -1;
        GLint src_y = -1;
        GLint src_z = -1;
        GLuint dst_name = 0;
        GLenum dst_target = GL_NONE;
        GLint dst_level = -1;
        GLint dst_x = -1;
        GLint dst_y = -1;
        GLint dst_z = -1;
        GLsizei width = -1;
        GLsizei height = -1;
        GLsizei depth = -1;
    };

    CopyImageCall copy_image_call;

    void GL_APIENTRY stub_DesktopDepthRange(double, double)
    {
        ++desktop_depth_range_calls;
    }

    void GL_APIENTRY stub_DesktopClearDepth(double)
    {
        ++desktop_clear_depth_calls;
    }

    void GL_APIENTRY stub_ClearBufferfv(
        GLenum buffer, GLint drawbuffer, const GLfloat*)
    {
        clear_buffer_call.buffer = buffer;
        clear_buffer_call.drawbuffer = drawbuffer;
    }

    void GL_APIENTRY stub_ClearBufferiv(
        GLenum buffer, GLint drawbuffer, const GLint*)
    {
        clear_buffer_call.buffer = buffer;
        clear_buffer_call.drawbuffer = drawbuffer;
    }

    void GL_APIENTRY stub_ClearBufferuiv(
        GLenum buffer, GLint drawbuffer, const GLuint*)
    {
        clear_buffer_call.buffer = buffer;
        clear_buffer_call.drawbuffer = drawbuffer;
    }

    void GL_APIENTRY stub_ClearBufferfi(
        GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
    {
        clear_buffer_call = {buffer, drawbuffer, depth, stencil};
    }

    void GL_APIENTRY stub_CopyImageSubData(
        GLuint src_name, GLenum src_target, GLint src_level,
        GLint src_x, GLint src_y, GLint src_z,
        GLuint dst_name, GLenum dst_target, GLint dst_level,
        GLint dst_x, GLint dst_y, GLint dst_z,
        GLsizei width, GLsizei height, GLsizei depth)
    {
        copy_image_call = {
            src_name, src_target, src_level, src_x, src_y, src_z,
            dst_name, dst_target, dst_level, dst_x, dst_y, dst_z,
            width, height, depth
        };
    }

    // No-op for all other functions (never actually called after Initialize)
    void GL_APIENTRY stub_noop() {}

    void* mock_proc_address(const char* name)
    {
        if (std::strcmp(name, "glGetString")   == 0)
            return reinterpret_cast<void*>(stub_GetString);
        if (std::strcmp(name, "glGetIntegerv") == 0)
            return reinterpret_cast<void*>(stub_GetIntegerv);
        if (std::strcmp(name, "glGetStringi")  == 0)
            return reinterpret_cast<void*>(stub_GetStringi);
        if (std::strcmp(name, "glGetError")    == 0)
            return reinterpret_cast<void*>(stub_GetError);
        if (std::strcmp(name, "glGetAttribLocation") == 0)
            return reinterpret_cast<void*>(stub_GetAttribLocation);
        if (std::strcmp(name, "glClearBufferfv") == 0)
            return reinterpret_cast<void*>(stub_ClearBufferfv);
        if (std::strcmp(name, "glClearBufferiv") == 0)
            return reinterpret_cast<void*>(stub_ClearBufferiv);
        if (std::strcmp(name, "glClearBufferuiv") == 0)
            return reinterpret_cast<void*>(stub_ClearBufferuiv);
        if (std::strcmp(name, "glClearBufferfi") == 0)
            return reinterpret_cast<void*>(stub_ClearBufferfi);
        if (std::strcmp(name, "glCopyImageSubData") == 0)
            return reinterpret_cast<void*>(stub_CopyImageSubData);
        return reinterpret_cast<void*>(stub_noop);
    }

    void* omitting_proc_address(const char* name)
    {
        if (omitted_function
            && std::strcmp(name, omitted_function) == 0)
            return nullptr;
        return mock_proc_address(name);
    }
}

int main()
{
    int failed = 0;
    auto check = [&](const char* label, bool cond)
    {
        if (!cond) {
            std::cerr << "FAIL: " << label << '\n';
            ++failed;
        }
    };
    // --- Initialize with mock loader -----------------------------------------
    check("Initialize returns true",
          metagl::Initialize(mock_proc_address));

    // --- Loader state ---------------------------------------------------------
    check("IsInitialized() == true",
          metagl::IsInitialized());

    check("IsFunctionAvailable(glEnable)",
          metagl::IsFunctionAvailable("glEnable"));

    check("IsFunctionAvailable(glGetString)",
          metagl::IsFunctionAvailable("glGetString"));

    // All pointers are non-null (stub_noop for everything) -> all loaded
    check("AllFunctionsLoaded() == true",
          metagl::AllFunctionsLoaded());

    // --- Context detection ----------------------------------------------------
    // Version string "OpenGL ES 3.0 Mock" must have been parsed correctly
    check("GetContextStatus == Current",
          metagl::GetContextStatus() == metagl::ContextStatus::Current);

    const auto& info = metagl::GetContextInfo();
    check("ContextInfo.api == OpenGLES",
          info.api == metagl::ApiKind::OpenGLES);
    check("ContextInfo.major == 3",
          info.major == 3);
    check("ContextInfo.minor == 0",
          info.minor == 0);

    const auto& caps = metagl::GetCapabilities();
    check("Capabilities.gles20 == true",  caps.gles20);
    check("Capabilities.gles30 == true",  caps.gles30);
    check("Capabilities.gles31 == false", !caps.gles31);
    check("Capabilities.gles32 == false", !caps.gles32);
    check("Capabilities.vendor non-empty", !caps.vendor.empty());
    check("Capabilities.version_string contains 'OpenGL ES 3.0'",
          caps.version_string.find("OpenGL ES 3.0") != std::string::npos);
    check("glGetAttribLocation preserves -1",
          metagl::glGetAttribLocation(metagl::ProgramId{1}, "missing").value == -1);

    // Exact clear-buffer domains forward their only legal GL tokens.
    GLfloat float_value[4]{};
    metagl::glClearBuffer(
        metagl::FloatClearBuffer::Depth, 0, float_value);
    check("Float clear forwards GL_DEPTH",
          clear_buffer_call.buffer == GL_DEPTH
          && clear_buffer_call.drawbuffer == 0);

    GLint signed_value[4]{};
    metagl::glClearBuffer(
        metagl::SignedIntegerClearBuffer::Stencil, 0, signed_value);
    check("Signed integer clear forwards GL_STENCIL",
          clear_buffer_call.buffer == GL_STENCIL
          && clear_buffer_call.drawbuffer == 0);

    GLuint unsigned_value[4]{};
    metagl::glClearBuffer(
        metagl::UnsignedIntegerClearBuffer::Color, 2, unsigned_value);
    check("Unsigned integer clear forwards GL_COLOR and draw buffer",
          clear_buffer_call.buffer == GL_COLOR
          && clear_buffer_call.drawbuffer == 2);

    metagl::glClearBufferfi(0.25f, 7);
    check("Depth-stencil clear fixes raw target and draw buffer",
          clear_buffer_call.buffer == GL_DEPTH_STENCIL
          && clear_buffer_call.drawbuffer == 0);
    check("Depth-stencil clear forwards values",
          clear_buffer_call.depth == 0.25f
          && clear_buffer_call.stencil == 7);

    // Typed image-copy overloads normalize all four endpoint combinations.
    metagl::glCopyImageSubData(
        metagl::TextureId{11}, metagl::ImageCopyTextureTarget::Texture3D,
        2, 1, 2, 3,
        metagl::TextureId{12},
        metagl::ImageCopyTextureTarget::Texture2DArray,
        4, 5, 6, 7, 8, 9, 10);
    check("Texture-to-texture copy forwards typed endpoints",
          copy_image_call.src_name == 11
          && copy_image_call.src_target == GL_TEXTURE_3D
          && copy_image_call.src_level == 2
          && copy_image_call.src_z == 3
          && copy_image_call.dst_name == 12
          && copy_image_call.dst_target == GL_TEXTURE_2D_ARRAY
          && copy_image_call.dst_level == 4
          && copy_image_call.dst_z == 7
          && copy_image_call.width == 8
          && copy_image_call.height == 9
          && copy_image_call.depth == 10);

    metagl::glCopyImageSubData(
        metagl::TextureId{21}, metagl::ImageCopyTextureTarget::TextureCubeMap,
        3, 4, 5, 2,
        metagl::RenderbufferId{22}, 6, 7, 8, 9);
    check("Texture-to-renderbuffer copy fixes destination metadata",
          copy_image_call.src_name == 21
          && copy_image_call.src_target == GL_TEXTURE_CUBE_MAP
          && copy_image_call.dst_name == 22
          && copy_image_call.dst_target == GL_RENDERBUFFER
          && copy_image_call.dst_level == 0
          && copy_image_call.dst_z == 0
          && copy_image_call.depth == 1);

    metagl::glCopyImageSubData(
        metagl::RenderbufferId{31}, 1, 2,
        metagl::TextureId{32},
        metagl::ImageCopyTextureTarget::TextureCubeMapArray,
        3, 4, 5, 6, 7, 8);
    check("Renderbuffer-to-texture copy fixes source metadata",
          copy_image_call.src_name == 31
          && copy_image_call.src_target == GL_RENDERBUFFER
          && copy_image_call.src_level == 0
          && copy_image_call.src_z == 0
          && copy_image_call.dst_name == 32
          && copy_image_call.dst_target == GL_TEXTURE_CUBE_MAP_ARRAY
          && copy_image_call.depth == 1);

    metagl::glCopyImageSubData(
        metagl::RenderbufferId{41}, 1, 2,
        metagl::RenderbufferId{42}, 3, 4, 5, 6);
    check("Renderbuffer-to-renderbuffer copy fixes both endpoint metadata",
          copy_image_call.src_name == 41
          && copy_image_call.src_target == GL_RENDERBUFFER
          && copy_image_call.src_level == 0
          && copy_image_call.src_z == 0
          && copy_image_call.dst_name == 42
          && copy_image_call.dst_target == GL_RENDERBUFFER
          && copy_image_call.dst_level == 0
          && copy_image_call.dst_z == 0
          && copy_image_call.width == 5
          && copy_image_call.height == 6
          && copy_image_call.depth == 1);

    // ==========================================================================
    // I5 — Context lifecycle state transitions
    // ==========================================================================

    const auto gen1 = metagl::GetContextInfo().generation;
    check("Initial generation > 0", gen1 > 0);

    // Lost transition
    metagl::MarkContextLost();
    check("After MarkContextLost: status == Lost",
          metagl::GetContextStatus() == metagl::ContextStatus::Lost);
    check("IsContextLost() == true", metagl::IsContextLost());
    check("Generation unchanged after MarkContextLost",
          metagl::GetContextInfo().generation == gen1);
    check("Lost context clears initialized state",
          !metagl::IsInitialized());
    check("Lost context hides individual function availability",
          !metagl::IsFunctionAvailable("glEnable")
          && !metagl::IsFunctionAvailable("glGetString"));
    check("Lost context hides complete loader state",
          !metagl::AllFunctionsLoaded());

    const auto lost_info = metagl::GetContextInfo();
    check("Lost context clears current API identity",
          lost_info.api == metagl::ApiKind::Unknown
          && lost_info.major == 0
          && lost_info.minor == 0);

    const auto& lost_caps = metagl::GetCapabilities();
    check("Lost context clears capability strings and extensions",
          lost_caps.version_string.empty()
          && lost_caps.vendor.empty()
          && lost_caps.renderer.empty()
          && lost_caps.extensions.empty());
    check("Lost context clears capability flags",
          !metagl::SupportsGLES20()
          && !metagl::SupportsGLES30()
          && !metagl::SupportsGLES31()
          && !metagl::SupportsGLES32()
          && !metagl::SupportsWebGL2()
          && !metagl::SupportsDesktopOpenGL()
          && !metagl::IsAngle());

    // Restored transition (without reloading function pointers — just state)
    metagl::MarkContextRestored();
    check("After MarkContextRestored: status == Restored",
          metagl::GetContextStatus() == metagl::ContextStatus::Restored);
    check("IsContextLost() == false after Restored", !metagl::IsContextLost());

    // LoadCurrentContext re-initializes and bumps generation
    check("LoadCurrentContext returns true",
          metagl::LoadCurrentContext(mock_proc_address));
    check("After LoadCurrentContext: status == Current",
          metagl::GetContextStatus() == metagl::ContextStatus::Current);
    check("Generation incremented after LoadCurrentContext",
          metagl::GetContextInfo().generation > gen1);
    check("Reload republishes loader availability",
          metagl::IsInitialized()
          && metagl::IsFunctionAvailable("glEnable")
          && metagl::AllFunctionsLoaded());
    check("Reload republishes API identity and capabilities",
          metagl::GetContextInfo().api == metagl::ApiKind::OpenGLES
          && metagl::SupportsGLES20()
          && metagl::SupportsGLES30()
          && !metagl::GetCapabilities().version_string.empty());

    // ==========================================================================
    // I6 — ContextEvents: listener registration and notification
    // ==========================================================================

    struct MockListener : metagl::ContextListener
    {
        int lost_count     = 0;
        int restored_count = 0;
        bool lost_saw_invalidated_state = false;
        bool restored_saw_current_state = false;

        void OnContextLost() override
        {
            ++lost_count;
            lost_saw_invalidated_state =
                !metagl::IsInitialized()
                && !metagl::IsFunctionAvailable("glEnable")
                && !metagl::AllFunctionsLoaded()
                && !metagl::SupportsGLES20();
        }

        void OnContextRestored() override
        {
            ++restored_count;
            restored_saw_current_state =
                metagl::IsInitialized()
                && metagl::IsFunctionAvailable("glEnable")
                && metagl::AllFunctionsLoaded()
                && metagl::SupportsGLES20();
        }
    };

    // Single listener receives both notifications
    MockListener ml1;
    metagl::AddContextListener(&ml1);
    metagl::AddContextListener(&ml1); // duplicate registration is ignored

    metagl::NotifyContextLost();
    check("NotifyContextLost fires OnContextLost",     ml1.lost_count     == 1);
    check("NotifyContextLost does not fire Restored",  ml1.restored_count == 0);
    check("Lost listener sees invalidated public state",
          ml1.lost_saw_invalidated_state);

    // A restore event without a successful reload is rejected.
    metagl::NotifyContextRestored();
    check("NotifyContextRestored requires a reload", ml1.restored_count == 0);
    check("Rejected restore remains Lost",
          metagl::GetContextStatus() == metagl::ContextStatus::Lost);

    check("RestoreCurrentContext succeeds",
          metagl::RestoreCurrentContext(mock_proc_address));
    check("RestoreCurrentContext fires OnContextRestored", ml1.restored_count == 1);
    check("Restored listener sees republished current state",
          ml1.restored_saw_current_state);
    check("NotifyContextRestored does not fire Lost",      ml1.lost_count     == 1);
    check("RestoreCurrentContext finishes Current",
          metagl::GetContextStatus() == metagl::ContextStatus::Current);

    // Multiple listeners
    MockListener ml2;
    metagl::AddContextListener(&ml2);

    metagl::NotifyContextLost();
    check("Both listeners receive NotifyContextLost (ml1)", ml1.lost_count == 2);
    check("Both listeners receive NotifyContextLost (ml2)", ml2.lost_count == 1);

    // Removing a listener stops notifications
    metagl::RemoveContextListener(&ml1);
    check("Reload before manual restored notification",
          metagl::LoadCurrentContext(mock_proc_address));
    metagl::NotifyContextRestored();
    check("Removed listener does not receive NotifyContextRestored", ml1.restored_count == 1);
    check("Active listener still receives NotifyContextRestored",    ml2.restored_count == 1);

    // ==========================================================================
    // R54-R56 — Listener safe dispatch (snapshot + re-check)
    // ==========================================================================

    struct RemovingOtherListener : metagl::ContextListener
    {
        metagl::ContextListener* other;
        int calls = 0;
        void OnContextLost() override
        {
            ++calls;
            metagl::RemoveContextListener(other);
        }
    } remover;

    MockListener victim;
    remover.other = &victim;
    metagl::AddContextListener(&remover);
    metagl::AddContextListener(&victim);

    check("Reload before safe dispatch test",
          metagl::LoadCurrentContext(mock_proc_address));
    metagl::NotifyContextLost();

    check("Remover called", remover.calls == 1);
    check("Victim NOT called (removed by remover during dispatch)", victim.lost_count == 0);

    // Clean up
    metagl::RemoveContextListener(&remover);
    metagl::RemoveContextListener(&ml2);
    metagl::NotifyContextLost();
    check("No listeners: NotifyContextLost is silent (ml1 unchanged)", ml1.lost_count == 2);
    check("No listeners: NotifyContextLost is silent (ml2 unchanged)", ml2.lost_count == 2);

    // Listener mutation during dispatch uses a stable snapshot.
    struct SelfRemovingListener : metagl::ContextListener
    {
        int calls = 0;
        void OnContextLost() override
        {
            ++calls;
            metagl::RemoveContextListener(this);
        }
    } self_removing;
    metagl::AddContextListener(&self_removing);
    check("Reload before mutation test",
          metagl::LoadCurrentContext(mock_proc_address));
    metagl::NotifyContextLost();
    check("Self-removing listener called once", self_removing.calls == 1);
    check("Reload after mutation test",
          metagl::LoadCurrentContext(mock_proc_address));
    metagl::NotifyContextLost();
    check("Self-removing listener stays removed", self_removing.calls == 1);

    // A failed non-null loader must not leak the previous context state.
    const auto generation_before_failure = metagl::GetContextGeneration();
    auto incomplete_loader = [](const char* name) -> void*
    {
        if (std::strcmp(name, "glBindAttribLocation") == 0)
            return nullptr;
        return mock_proc_address(name);
    };
    check("Incomplete core loader fails",
          !metagl::Initialize(incomplete_loader));
    check("Failed load clears initialized state", !metagl::IsInitialized());
    check("Failed reload remains Lost",
          metagl::GetContextStatus() == metagl::ContextStatus::Lost);
    check("Failed load preserves generation",
          metagl::GetContextGeneration() == generation_before_failure);
    check("Failed load clears old capabilities",
          !metagl::SupportsGLES20()
          && metagl::GetCapabilities().version_string.empty());
    check("Recovery after failed loader succeeds",
          metagl::RestoreCurrentContext(mock_proc_address));

    // ==========================================================================
    // L4 — Version-aware loader validation
    // ==========================================================================

    mock_version = nullptr;
    check("Null GL_VERSION is rejected",
          !metagl::Initialize(mock_proc_address));
    check("Null GL_VERSION does not publish bootstrap functions",
          !metagl::IsInitialized()
          && !metagl::IsFunctionAvailable("glGetString"));

    mock_version = "OpenGL ES three";
    check("Malformed GL_VERSION is rejected",
          !metagl::Initialize(mock_proc_address));

    mock_version = "OpenGL ES 3.0 Mock";
    omitted_function = "glGetIntegerv";
    check("Missing bootstrap function is rejected",
          !metagl::Initialize(omitting_proc_address));
    omitted_function = nullptr;

    mock_version = "2.1 Mock Desktop";
    check("Desktop OpenGL below 3.3 is rejected",
          !metagl::Initialize(mock_proc_address));

    mock_version = "WebGL 1.0 Mock";
    omitted_function = "glReadBuffer";
    check("WebGL 1 accepts a missing GLES 3.0 function",
          metagl::Initialize(omitting_proc_address));

    mock_version = "WebGL 2.0 Mock";
    omitted_function = "glDispatchCompute";
    check("WebGL 2 accepts a non-WebGL GLES 3.1 function",
          metagl::Initialize(omitting_proc_address));
    omitted_function = "glGetStringi";
    check("WebGL 2 requires glGetStringi",
          !metagl::Initialize(omitting_proc_address));

    // A function is optional below the version that introduced it and
    // mandatory from that version onward.
    mock_version = "OpenGL ES 2.0 Mock";
    omitted_function = "glReadBuffer";
    check("GLES 2.0 accepts a missing GLES 3.0 function",
          metagl::Initialize(omitting_proc_address));

    mock_version = "OpenGL ES 3.0 Mock";
    check("GLES 3.0 rejects a missing GLES 3.0 function",
          !metagl::Initialize(omitting_proc_address));

    omitted_function = "glGetStringi";
    check("GLES 3.0 requires glGetStringi",
          !metagl::Initialize(omitting_proc_address));

    omitted_function = "glDispatchCompute";
    check("GLES 3.0 accepts a missing GLES 3.1 function",
          metagl::Initialize(omitting_proc_address));

    mock_version = "OpenGL ES 3.1 Mock";
    check("GLES 3.1 rejects a missing GLES 3.1 function",
          !metagl::Initialize(omitting_proc_address));

    omitted_function = "glBlendBarrier";
    check("GLES 3.1 accepts a missing GLES 3.2 function",
          metagl::Initialize(omitting_proc_address));

    mock_version = "OpenGL ES 3.2 Mock";
    check("GLES 3.2 rejects a missing GLES 3.2 function",
          !metagl::Initialize(omitting_proc_address));

    omitted_function = nullptr;
    check("Complete GLES 3.2 loader succeeds",
          metagl::Initialize(mock_proc_address));
    check("GLES 3.2 capabilities are published after validation",
          metagl::SupportsGLES20()
          && metagl::SupportsGLES30()
          && metagl::SupportsGLES31()
          && metagl::SupportsGLES32());

    mock_version = "OpenGL ES 3.0 Mock";
    check("Default GLES 3.0 context restored after tier tests",
          metagl::Initialize(mock_proc_address));

    // ==========================================================================
    // I7 — HasExtension / GetCapabilities with fake extension string
    // ==========================================================================

    // After the initial mock_proc_address Initialize(), extensions list is empty
    check("No extensions reported by default stub",
          metagl::GetCapabilities().extensions.empty());
    check("HasExtension returns false for unknown extension",
          !metagl::HasExtension("GL_EXT_texture_filter_anisotropic"));

    // Re-initialize with a stub that advertises one extension via glGetStringi
    {
        static auto ext_GetIntegerv = [](GLenum pname, GLint* params)
        {
            if (!params) return;
            *params = 0;
            if (pname == GL_MAJOR_VERSION)   *params = 3;
            if (pname == GL_MINOR_VERSION)   *params = 0;
            if (pname == GL_NUM_EXTENSIONS)  *params = 1; // one extension
        };

        static auto ext_GetStringi = [](GLenum /*name*/, GLuint index) -> const GLubyte*
        {
            static const GLubyte aniso[] = "GL_EXT_texture_filter_anisotropic";
            static const GLubyte empty[] = "";
            return (index == 0) ? aniso : empty;
        };

        auto ext_loader = [](const char* name) -> void*
        {
            if (std::strcmp(name, "glGetString")   == 0)
                return reinterpret_cast<void*>(stub_GetString);
            if (std::strcmp(name, "glGetIntegerv") == 0)
                return reinterpret_cast<void*>(+ext_GetIntegerv);
            if (std::strcmp(name, "glGetStringi")  == 0)
                return reinterpret_cast<void*>(+ext_GetStringi);
            return mock_proc_address(name);
        };

        check("Re-Initialize with extension stub returns true",
              metagl::Initialize(ext_loader));
    }

    check("GetCapabilities().extensions has 1 entry",
          metagl::GetCapabilities().extensions.size() == 1);
    check("HasExtension finds GL_EXT_texture_filter_anisotropic",
          metagl::HasExtension("GL_EXT_texture_filter_anisotropic"));
    check("HasExtension returns false for absent extension",
          !metagl::HasExtension("GL_OES_nonexistent"));

    // SupportsGLES* convenience helpers
    check("SupportsGLES20() == true",  metagl::SupportsGLES20());
    check("SupportsGLES30() == true",  metagl::SupportsGLES30());
    check("SupportsGLES31() == false", !metagl::SupportsGLES31());
    check("SupportsGLES32() == false", !metagl::SupportsGLES32());

    // Desktop OpenGL uses double-precision depth entry points and does not
    // require the GLES-only shader compiler query functions.
    auto desktop_loader = [](const char* name) -> void*
    {
        if (omitted_function
            && std::strcmp(name, omitted_function) == 0)
            return nullptr;
        if (std::strcmp(name, "glGetString") == 0)
            return reinterpret_cast<void*>(stub_DesktopGetString);
        if (std::strcmp(name, "glDepthRange") == 0)
            return reinterpret_cast<void*>(stub_DesktopDepthRange);
        if (std::strcmp(name, "glClearDepth") == 0)
            return reinterpret_cast<void*>(stub_DesktopClearDepth);
        if (std::strcmp(name, "glDepthRangef") == 0
            || std::strcmp(name, "glClearDepthf") == 0
            || std::strcmp(name, "glGetShaderPrecisionFormat") == 0
            || std::strcmp(name, "glShaderBinary") == 0
            || std::strcmp(name, "glReleaseShaderCompiler") == 0)
            return nullptr;
        return mock_proc_address(name);
    };

    omitted_function = "glGetStringi";
    check("Desktop OpenGL 3.3+ requires glGetStringi",
          !metagl::Initialize(desktop_loader));
    omitted_function = nullptr;

    check("Desktop OpenGL loader succeeds",
          metagl::Initialize(desktop_loader));
    check("Desktop API kind detected",
          metagl::GetContextInfo().api == metagl::ApiKind::OpenGL);
    check("Desktop version parsed",
          metagl::GetContextInfo().major == 4
          && metagl::GetContextInfo().minor == 6);
    check("Desktop capability exposed", metagl::SupportsDesktopOpenGL());
    check("Desktop context does not claim GLES", !metagl::SupportsGLES20());
    metagl::glDepthRangef(0.0f, 1.0f);
    metagl::glClearDepthf(1.0f);
    check("Desktop glDepthRange adapter called", desktop_depth_range_calls == 1);
    check("Desktop glClearDepth adapter called", desktop_clear_depth_calls == 1);

    auto angle_loader = [](const char* name) -> void*
    {
        if (std::strcmp(name, "glGetString") == 0)
            return reinterpret_cast<void*>(stub_AngleGetString);
        return mock_proc_address(name);
    };
    check("ANGLE loader succeeds", metagl::Initialize(angle_loader));
    check("ANGLE backend detected", metagl::IsAngle());
    check("ANGLE mock remains OpenGL ES",
          metagl::GetContextInfo().api == metagl::ApiKind::OpenGLES);

    // Flush while the process and any shared library are fully operational.
    // Windows DLL teardown runs under the loader lock and must not perform I/O.
    metagl::FlushDebugLog();

    if (failed > 0)
        std::cerr << failed << " mock-loader test(s) failed.\n";
    return failed;
}
