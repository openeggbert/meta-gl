#pragma once

#include <cstddef>

namespace metagl
{
    // Low-level GL scalar types mirroring the OpenGL type aliases
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

    /// Function pointer type compatible with SDL_GL_GetProcAddress, glfwGetProcAddress, etc.
    using GlGetProcAddressFn = void* (*)(const char* name);
}
