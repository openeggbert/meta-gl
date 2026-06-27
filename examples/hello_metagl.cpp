// hello_metagl.cpp — minimal meta-gl usage example
//
// In a real application, replace mock_proc_address with the actual
// platform GetProcAddress callback, e.g.:
//   SDL_GL_GetProcAddress   (SDL2)
//   eglGetProcAddress       (EGL)
//   emscripten_webgl_get_proc_address  (Emscripten/WebGL)
//
// This example uses a no-op stub so it runs without a GPU, which is
// useful for verifying the library links and the public API compiles.

#include <metagl/metagl.hpp>
#include <GLES3/gl32.h>
#include <cstring>
#include <iostream>

// ---------------------------------------------------------------------------
// Stub GetProcAddress — returns minimal stubs so Initialize() succeeds
// ---------------------------------------------------------------------------

static const GLubyte* GL_APIENTRY stub_GetString(GLenum name)
{
    static const GLubyte version[]  = "OpenGL ES 3.0 (stub)";
    static const GLubyte vendor[]   = "StubVendor";
    static const GLubyte renderer[] = "StubRenderer";
    static const GLubyte glsl[]     = "OpenGL ES GLSL ES 3.00";
    static const GLubyte empty[]    = "";
    if (name == GL_VERSION)                  return version;
    if (name == GL_VENDOR)                   return vendor;
    if (name == GL_RENDERER)                 return renderer;
    if (name == GL_SHADING_LANGUAGE_VERSION) return glsl;
    return empty;
}

static void GL_APIENTRY stub_GetIntegerv(GLenum pname, GLint* params)
{
    if (!params) return;
    *params = 0;
    if (pname == GL_MAJOR_VERSION)  *params = 3;
    if (pname == GL_MINOR_VERSION)  *params = 0;
    if (pname == GL_NUM_EXTENSIONS) *params = 0;
}

static const GLubyte* GL_APIENTRY stub_GetStringi(GLenum, GLuint)
{
    static const GLubyte empty[] = "";
    return empty;
}

static void GL_APIENTRY stub_noop() {}

static void* mock_proc_address(const char* name)
{
    if (std::strcmp(name, "glGetString")   == 0) return reinterpret_cast<void*>(stub_GetString);
    if (std::strcmp(name, "glGetIntegerv") == 0) return reinterpret_cast<void*>(stub_GetIntegerv);
    if (std::strcmp(name, "glGetStringi")  == 0) return reinterpret_cast<void*>(stub_GetStringi);
    return reinterpret_cast<void*>(stub_noop);
}

// ---------------------------------------------------------------------------
// Application entry point
// ---------------------------------------------------------------------------

int main()
{
    // 1. Initialize the function-pointer table.
    //    In a real app, provide your platform's GetProcAddress here.
    if (!metagl::Initialize(mock_proc_address))
    {
        std::cerr << "metagl::Initialize failed\n";
        return 1;
    }

    // 2. Query context info and capabilities.
    const auto& info = metagl::GetContextInfo();
    const auto& caps = metagl::GetCapabilities();

    std::cout << "meta-gl initialized\n"
              << "  Version : " << caps.version_string << '\n'
              << "  Vendor  : " << caps.vendor         << '\n'
              << "  Renderer: " << caps.renderer       << '\n'
              << "  API     : ";
    switch (info.api)
    {
        case metagl::ApiKind::OpenGLES: std::cout << "OpenGL ES"; break;
        case metagl::ApiKind::WebGL:    std::cout << "WebGL";     break;
        default:                        std::cout << "Unknown";   break;
    }
    std::cout << ' ' << info.major << '.' << info.minor << '\n';

    std::cout << "  GLES 2.0: " << (caps.gles20 ? "yes" : "no") << '\n'
              << "  GLES 3.0: " << (caps.gles30 ? "yes" : "no") << '\n'
              << "  GLES 3.1: " << (caps.gles31 ? "yes" : "no") << '\n'
              << "  GLES 3.2: " << (caps.gles32 ? "yes" : "no") << '\n'
              << "  Extensions: " << caps.extensions.size()      << '\n';

    // 3. Demonstrate type-safe enum API (no actual GL calls in stub mode).
    using namespace metagl;
    const ClearBufferBit mask = ClearBufferBit::Color | ClearBufferBit::Depth;
    std::cout << "  ClearBufferBit mask: "
              << to_string(ClearBufferBit::Color) << " | "
              << to_string(ClearBufferBit::Depth) << '\n';
    (void)mask;

    // 4. Demonstrate handle types.
    const TextureId tex{42};
    std::cout << "  Handle example: " << to_string(tex) << '\n';

    std::cout << "Done.\n";
    return 0;
}
