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

    const GLubyte* GL_APIENTRY stub_GetString(GLenum name)
    {
        static const GLubyte version[]  = "OpenGL ES 3.0 Mock";
        static const GLubyte vendor[]   = "MockVendor";
        static const GLubyte renderer[] = "MockRenderer";
        static const GLubyte glsl[]     = "OpenGL ES GLSL ES 3.00";
        static const GLubyte empty[]    = "";
        if (name == GL_VERSION)                  return version;
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
        return reinterpret_cast<void*>(stub_noop);
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

    // ==========================================================================
    // I6 — ContextEvents: listener registration and notification
    // ==========================================================================

    struct MockListener : metagl::ContextListener
    {
        int lost_count     = 0;
        int restored_count = 0;
        void OnContextLost()     override { ++lost_count; }
        void OnContextRestored() override { ++restored_count; }
    };

    // Single listener receives both notifications
    MockListener ml1;
    metagl::AddContextListener(&ml1);
    metagl::AddContextListener(&ml1); // duplicate registration is ignored

    metagl::NotifyContextLost();
    check("NotifyContextLost fires OnContextLost",     ml1.lost_count     == 1);
    check("NotifyContextLost does not fire Restored",  ml1.restored_count == 0);

    // A restore event without a successful reload is rejected.
    metagl::NotifyContextRestored();
    check("NotifyContextRestored requires a reload", ml1.restored_count == 0);
    check("Rejected restore remains Lost",
          metagl::GetContextStatus() == metagl::ContextStatus::Lost);

    check("RestoreCurrentContext succeeds",
          metagl::RestoreCurrentContext(mock_proc_address));
    check("RestoreCurrentContext fires OnContextRestored", ml1.restored_count == 1);
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

    // Clean up
    metagl::RemoveContextListener(&ml2);
    metagl::NotifyContextLost();
    check("No listeners: NotifyContextLost is silent (ml1 unchanged)", ml1.lost_count == 2);
    check("No listeners: NotifyContextLost is silent (ml2 unchanged)", ml2.lost_count == 1);

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
    // I7 — HasExtension / GetCapabilities with fake extension string
    // ==========================================================================

    // After the initial mock_proc_address Initialize(), extensions list is empty
    check("No extensions reported by default stub",
          metagl::GetCapabilities().extensions.empty());
    check("HasExtension returns false for unknown extension",
          !metagl::HasExtension("GL_EXT_texture_filter_anisotropic"));

    // Re-initialize with a stub that advertises one extension via glGetStringi
    {
        static const char* ext_name = "GL_EXT_texture_filter_anisotropic";

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
            return reinterpret_cast<void*>(stub_noop);
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

    if (failed > 0)
        std::cerr << failed << " mock-loader test(s) failed.\n";
    return failed;
}
