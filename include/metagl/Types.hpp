#pragma once

#ifndef GL_GLES_PROTOTYPES
#define GL_GLES_PROTOTYPES 0
#endif
#include <GLES3/gl32.h>

#include <concepts>
#include <type_traits>

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

    /// Satisfied by any lightweight handle struct that exposes a `GLuint value` member.
    template<typename T>
    concept GlHandle = requires(T h) {
        { h.value } -> std::convertible_to<GLuint>;
    };

    /// Satisfied by any enum class whose underlying type is GLenum.
    template<typename T>
    concept GlEnum =
        std::is_enum_v<T> &&
        std::same_as<std::underlying_type_t<T>, GLenum>;

    /// Satisfied by types that can be safely used in std::span<const T> for GL data uploads.
    /// Requires trivial copyability and standard layout so the byte representation is well-defined.
    template<typename T>
    concept SpanCompatible =
        std::is_trivially_copyable_v<T> &&
        std::is_standard_layout_v<T>;

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
