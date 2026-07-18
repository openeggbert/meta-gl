#include <metagl/metagl.hpp>

#include <EGL/egl.h>

#include <iostream>

namespace
{
    void* egl_loader(const char* name)
    {
        return reinterpret_cast<void*>(eglGetProcAddress(name));
    }

    struct EglContext
    {
        EGLDisplay display = EGL_NO_DISPLAY;
        EGLSurface surface = EGL_NO_SURFACE;
        EGLContext context = EGL_NO_CONTEXT;

        ~EglContext()
        {
            if (display == EGL_NO_DISPLAY) return;
            eglMakeCurrent(
                display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
            if (context != EGL_NO_CONTEXT)
                eglDestroyContext(display, context);
            if (surface != EGL_NO_SURFACE)
                eglDestroySurface(display, surface);
            eglTerminate(display);
        }
    };
}

int main()
{
    EglContext egl;
    egl.display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (egl.display == EGL_NO_DISPLAY)
    {
        std::cerr << "eglGetDisplay failed\n";
        return 1;
    }

    EGLint egl_major = 0;
    EGLint egl_minor = 0;
    if (eglInitialize(egl.display, &egl_major, &egl_minor) != EGL_TRUE)
    {
        std::cerr << "eglInitialize failed\n";
        return 1;
    }
    if (eglBindAPI(EGL_OPENGL_ES_API) != EGL_TRUE)
    {
        std::cerr << "eglBindAPI failed\n";
        return 1;
    }

    constexpr EGLint config_attributes[] = {
        EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_NONE
    };
    EGLConfig config = nullptr;
    EGLint config_count = 0;
    if (eglChooseConfig(
            egl.display, config_attributes, &config, 1, &config_count)
            != EGL_TRUE
        || config_count == 0)
    {
        std::cerr << "eglChooseConfig failed\n";
        return 1;
    }

    constexpr EGLint surface_attributes[] = {
        EGL_WIDTH, 1,
        EGL_HEIGHT, 1,
        EGL_NONE
    };
    egl.surface = eglCreatePbufferSurface(
        egl.display, config, surface_attributes);
    if (egl.surface == EGL_NO_SURFACE)
    {
        std::cerr << "eglCreatePbufferSurface failed\n";
        return 1;
    }

    constexpr EGLint context_attributes[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };
    egl.context = eglCreateContext(
        egl.display, config, EGL_NO_CONTEXT, context_attributes);
    if (egl.context == EGL_NO_CONTEXT
        || eglMakeCurrent(egl.display, egl.surface, egl.surface, egl.context)
            != EGL_TRUE)
    {
        std::cerr << "EGL context creation failed\n";
        return 1;
    }

    if (!metagl::Initialize(egl_loader))
    {
        std::cerr << "metagl::Initialize failed on the EGL context\n";
        return 1;
    }
    if (!metagl::SupportsGLES20()
        || metagl::GetContextStatus() != metagl::ContextStatus::Current)
    {
        std::cerr << "unexpected meta-gl context capabilities\n";
        return 1;
    }

    metagl::glViewport(0, 0, 1, 1);
    metagl::glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    metagl::glClear(metagl::ClearBufferBit::Color);
    metagl::glFinish();
    if (metagl::glGetError() != metagl::ErrorCode::NoError)
    {
        std::cerr << "real GL wrapper smoke produced an error\n";
        return 1;
    }

    metagl::NotifyContextLost();
    return 0;
}
