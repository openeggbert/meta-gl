#pragma once

#ifndef GL_GLES_PROTOTYPES
#define GL_GLES_PROTOTYPES 0
#endif
#include <GLES3/gl32.h>

namespace metagl
{
    using GlGetProcAddressFn = void* (*)(const char* name);

    struct ShaderId        { GLuint value{}; };
    struct ProgramId       { GLuint value{}; };
    struct TextureId       { GLuint value{}; };
    struct BufferId        { GLuint value{}; };
    struct FramebufferId   { GLuint value{}; };
    struct RenderbufferId  { GLuint value{}; };
    struct SamplerId       { GLuint value{}; };
    struct VertexArrayId   { GLuint value{}; };
    struct QueryId              { GLuint value{}; };
    struct TransformFeedbackId  { GLuint value{}; };
    struct ProgramPipelineId    { GLuint value{}; };
    struct UniformLocation      { GLint  value{-1}; };
    struct AttribLocation       { GLuint value{}; };
    struct ImageUnit            { GLuint value{}; };

    using ::GLbitfield;
    using ::GLboolean;
    using ::GLbyte;
    using ::GLchar;
    using ::GLclampf;
    using ::GLenum;
    using ::GLfixed;
    using ::GLfloat;
    using ::GLhalf;
    using ::GLint;
    using ::GLint64;
    using ::GLintptr;
    using ::GLshort;
    using ::GLsizei;
    using ::GLsizeiptr;
    using ::GLsync;
    using ::GLubyte;
    using ::GLuint;
    using ::GLuint64;
    using ::GLushort;
    using ::GLvoid;
    using ::GLDEBUGPROC;
}
