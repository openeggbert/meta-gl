#pragma once

#include "Types.hpp"

namespace metagl
{
    /// Initialize meta-gl by loading GL function pointers via the provided loader.
    /// Compatible loaders: SDL_GL_GetProcAddress, glfwGetProcAddress, etc.
    bool Initialize(GlGetProcAddressFn loader);

    /// Returns true if Initialize() succeeded previously.
    bool IsInitialized();
}
