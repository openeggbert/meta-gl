#include <metagl/metagl.hpp>
#include <metagl/DesktopEsTier.hpp>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_set>

// =============================================================================
// R78 — Desktop OpenGL ES-tier equivalence boundary tests
//
// Exercises the internal-only metagl::detail::GetDesktopEsTier() diagnostic
// (R76) and its GL_ARB_ES3_1/3_2_compatibility fast-path (R77) across
// boundary desktop OpenGL versions (3.3, 4.1, 4.3), with and without those
// extensions, using a mock loader (no real GPU required).
// =============================================================================

namespace
{
    const char* g_version = "3.3.0 Mock Desktop";
    std::unordered_set<std::string> g_omitted;
    std::unordered_set<std::string> g_extensions;

    const GLubyte* GL_APIENTRY stub_GetString(GLenum name)
    {
        static const GLubyte vendor[]   = "MockVendor";
        static const GLubyte renderer[] = "Mock Desktop Renderer";
        static const GLubyte glsl[]     = "4.60 Mock";
        static const GLubyte empty[]    = "";
        if (name == GL_VERSION)                  return reinterpret_cast<const GLubyte*>(g_version);
        if (name == GL_VENDOR)                   return vendor;
        if (name == GL_RENDERER)                 return renderer;
        if (name == GL_SHADING_LANGUAGE_VERSION) return glsl;
        return empty;
    }

    void GL_APIENTRY stub_GetIntegerv(GLenum pname, GLint* params)
    {
        if (!params) return;
        *params = 0;
        if (pname == GL_NUM_EXTENSIONS)
            *params = static_cast<GLint>(g_extensions.size());
    }

    const GLubyte* GL_APIENTRY stub_GetStringi(GLenum name, GLuint index)
    {
        static const GLubyte empty[] = "";
        if (name != GL_EXTENSIONS) return empty;
        if (index >= g_extensions.size()) return empty;
        auto it = g_extensions.begin();
        std::advance(it, index);
        // Extension strings must outlive the call; store them statically.
        static std::string storage;
        storage = *it;
        return reinterpret_cast<const GLubyte*>(storage.c_str());
    }

    GLenum GL_APIENTRY stub_GetError() { return GL_NO_ERROR; }
    void   GL_APIENTRY stub_noop() {}

    void* mock_proc_address(const char* name)
    {
        if (g_omitted.count(name)) return nullptr;
        if (std::strcmp(name, "glGetString")   == 0) return reinterpret_cast<void*>(stub_GetString);
        if (std::strcmp(name, "glGetIntegerv") == 0) return reinterpret_cast<void*>(stub_GetIntegerv);
        if (std::strcmp(name, "glGetStringi")  == 0) return reinterpret_cast<void*>(stub_GetStringi);
        if (std::strcmp(name, "glGetError")    == 0) return reinterpret_cast<void*>(stub_GetError);
        // Desktop double-precision depth entry points are not needed here
        // because glDepthRangef/glClearDepthf are provided via stub_noop.
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

    using metagl::detail::DesktopEsTier;

    // --- Boundary 1: desktop 3.3, no ES3_1/3_2 extensions, missing an
    //     ES-3.1-only and an ES-3.2-only entry point -> stalls at Es30. ------
    g_version = "3.3.0 Mock Desktop";
    g_extensions = {};
    g_omitted = {"glDispatchCompute", "glBlendBarrier"};
    check("3.3 baseline: Initialize succeeds", metagl::Initialize(mock_proc_address));
    check("3.3 baseline: tier == Es30",
          metagl::detail::GetDesktopEsTier() == DesktopEsTier::Es30);

    // --- Boundary 2: desktop 3.3 + GL_ARB_ES3_1_compatibility, same missing
    //     entry points -> the extension covers the ES-3.1 gap but not the
    //     ES-3.2 one -> Es31. ---------------------------------------------
    g_extensions = {"GL_ARB_ES3_1_compatibility"};
    check("3.3+ES3_1_compat: Initialize succeeds", metagl::Initialize(mock_proc_address));
    check("3.3+ES3_1_compat: tier == Es31",
          metagl::detail::GetDesktopEsTier() == DesktopEsTier::Es31);

    // --- Boundary 3: desktop 3.3 + GL_ARB_ES3_2_compatibility, same missing
    //     entry points -> the extension covers both gaps -> Es32. ---------
    g_extensions = {"GL_ARB_ES3_2_compatibility"};
    check("3.3+ES3_2_compat: Initialize succeeds", metagl::Initialize(mock_proc_address));
    check("3.3+ES3_2_compat: tier == Es32",
          metagl::detail::GetDesktopEsTier() == DesktopEsTier::Es32);

    // --- Boundary 4: desktop 4.1, missing an ES-3.0-only entry point (no
    //     extension can compensate for the ES-3.0 baseline) -> Baseline. --
    g_version = "4.1.0 Mock Desktop";
    g_extensions = {"GL_ARB_ES3_1_compatibility", "GL_ARB_ES3_2_compatibility"};
    g_omitted = {"glTexStorage2D"};
    check("4.1 missing ES3.0 entry point: Initialize succeeds",
          metagl::Initialize(mock_proc_address));
    check("4.1 missing ES3.0 entry point: tier == Baseline",
          metagl::detail::GetDesktopEsTier() == DesktopEsTier::Baseline);

    // --- Boundary 5: desktop 4.3, every mandatory entry point resolves and
    //     no extension is needed -> Es32 via plain function availability. -
    g_version = "4.3.0 Mock Desktop";
    g_extensions = {};
    g_omitted = {};
    check("4.3 fully populated: Initialize succeeds",
          metagl::Initialize(mock_proc_address));
    check("4.3 fully populated: tier == Es32",
          metagl::detail::GetDesktopEsTier() == DesktopEsTier::Es32);

    // --- A non-desktop (GLES) context never reports a desktop tier. ------
    g_version = "OpenGL ES 3.2 Mock";
    check("GLES context: Initialize succeeds", metagl::Initialize(mock_proc_address));
    check("GLES context: tier == None",
          metagl::detail::GetDesktopEsTier() == DesktopEsTier::None);

    // --- Context loss hides the diagnostic like every other loader state. -
    g_version = "4.3.0 Mock Desktop";
    check("Reload desktop before loss test", metagl::Initialize(mock_proc_address));
    check("Desktop reload: tier == Es32",
          metagl::detail::GetDesktopEsTier() == DesktopEsTier::Es32);
    metagl::MarkContextLost();
    check("After MarkContextLost: tier == None",
          metagl::detail::GetDesktopEsTier() == DesktopEsTier::None);

    if (failed > 0)
        std::cerr << failed << " desktop-es-tier test(s) failed.\n";
    return failed;
}
