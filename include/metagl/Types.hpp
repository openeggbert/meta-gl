#pragma once

#ifndef GL_GLES_PROTOTYPES
#define GL_GLES_PROTOTYPES 0
#endif
#include <GLES3/gl32.h>

namespace metagl
{
    using GlGetProcAddressFn = void* (*)(const char* name);

    using ::GLenum;
    using ::GLuint;
    using ::GLint;
    using ::GLsizei;
    using ::GLchar;
    using ::GLboolean;
    using ::GLbitfield;
    using ::GLfloat;
    using ::GLubyte;
    using ::GLsizeiptr;
    using ::GLintptr;
}
