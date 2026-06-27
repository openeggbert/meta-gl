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

    if (failed > 0)
        std::cerr << failed << " mock-loader test(s) failed.\n";
    return failed;
}
