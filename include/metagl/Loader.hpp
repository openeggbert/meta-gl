#pragma once

#include "Types.hpp"

#include <string_view>

namespace metagl
{
    /// Convenient alias matching the issue description naming.
    using GetProcAddress = GlGetProcAddressFn;

    /// Initialize meta-gl by loading GL function pointers via the provided loader.
    /// Compatible loaders: SDL_GL_GetProcAddress, glfwGetProcAddress, eglGetProcAddress, …
    ///
    /// On success:
    ///   - All existing metagl::gl* wrappers work.
    ///   - Context generation is incremented.
    ///   - Context status is set to Current.
    ///   - Capabilities are (re-)detected.
    ///
    /// Returns true when the core set of functions was loaded successfully.
    bool Initialize(GlGetProcAddressFn loader);

    /// Explicit-loader variant with the new naming from the issue description.
    /// Equivalent to Initialize(); provided for API consistency.
    ///
    /// Android usage:
    ///   Call from GLSurfaceView.Renderer::onSurfaceCreated (via JNI) or from
    ///   the SDL/EGL context-creation path after each context recreation.
    ///   Old GL handles (textures, buffers, shaders, …) are invalid after
    ///   context loss; do not attempt glDelete* on them.
    inline bool LoadCurrentContext(GlGetProcAddressFn getProcAddress)
    {
        return Initialize(getProcAddress);
    }

    /// Returns true if Initialize() succeeded previously.
    bool IsInitialized();

    /// Returns true if the named GL function was loaded successfully during the
    /// last Initialize() / LoadCurrentContext() call.
    [[nodiscard]] bool IsFunctionAvailable(std::string_view name) noexcept;
}
