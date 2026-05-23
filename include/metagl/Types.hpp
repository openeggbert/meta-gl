#pragma once

#include <cstddef>

namespace metagl
{
    /// Function pointer type compatible with SDL_GL_GetProcAddress, glfwGetProcAddress, etc.
    using GlGetProcAddressFn = void* (*)(const char* name);

    namespace detail
    {
        // Raw GL scalar types — internal use only, not part of the public easy-gl API
        using GLsizei    = int;
        using GLuint     = unsigned int;
        using GLint      = int;
        using GLenum     = unsigned int;
        using GLchar     = char;
        using GLboolean  = unsigned char;
        using GLbitfield = unsigned int;
        using GLfloat    = float;
        using GLdouble   = double;
        using GLsizeiptr = long;
        using GLintptr   = long;
    }
}
