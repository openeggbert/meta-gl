#pragma once

#include "Types.hpp"
#include "Enums.hpp"

namespace metagl
{
    // Buffers
    void glGenBuffers(GLsizei n, GLuint* buffers);
    void glDeleteBuffers(GLsizei n, const GLuint* buffers);
    void glBindBuffer(BufferTarget target, GLuint buffer);
    void glBufferData(BufferTarget target, GLsizeiptr size, const void* data, BufferUsage usage);
    void glBufferSubData(BufferTarget target, GLintptr offset, GLsizeiptr size, const void* data);
    void glBindBufferBase(BufferTarget target, GLuint index, GLuint buffer);

    // Context info
    const GLchar* glGetString(StringName name);
    const GLchar* glGetStringi(StringName name, GLuint index);
    void glGetIntegerv(IntegerName pname, GLint* data);
    /// Raw variant for special cases (e.g. GL_VIEWPORT = 0x0BA2)
    void glGetIntegervRaw(GLenum pname, GLint* data);

    // Shaders
    GLuint glCreateShader(ShaderType type);
    void glShaderSource(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
    void glCompileShader(GLuint shader);
    void glGetShaderiv(GLuint shader, ShaderParameter pname, GLint* params);
    void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
    void glDeleteShader(GLuint shader);

    // Programs
    GLuint glCreateProgram();
    void glAttachShader(GLuint program, GLuint shader);
    void glDetachShader(GLuint program, GLuint shader);
    void glLinkProgram(GLuint program);
    void glGetProgramiv(GLuint program, ProgramParameter pname, GLint* params);
    void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
    void glUseProgram(GLuint program);
    void glDeleteProgram(GLuint program);

    // Uniforms
    GLint glGetUniformLocation(GLuint program, const GLchar* name);
    void glUniform1i(GLint location, GLint v0);
    void glUniform1f(GLint location, GLfloat v0);
    void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
    void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
    void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

    // Vertex arrays
    void glGenVertexArrays(GLsizei n, GLuint* arrays);
    void glDeleteVertexArrays(GLsizei n, const GLuint* arrays);
    void glBindVertexArray(GLuint array);
    void glEnableVertexAttribArray(GLuint index);
    void glVertexAttribPointer(GLuint index, GLint size, DataType type, GLboolean normalized, GLsizei stride, const void* pointer);

    // Commands
    void glClear(ClearBufferBit mask);
    void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    void glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
    void glDrawArrays(PrimitiveType mode, GLint first, GLsizei count);
    void glDrawElements(PrimitiveType mode, GLsizei count, DataType type, const void* indices);

    // Textures
    void glGenTextures(GLsizei n, GLuint* textures);
    void glDeleteTextures(GLsizei n, const GLuint* textures);
    void glBindTexture(TextureTarget target, GLuint texture);
    void glActiveTexture(GLenum textureUnit); // GL_TEXTURE0 + index
    void glPixelStorei(GLenum pname, GLint param);
    void glPixelStoreParam(PixelStoreParam pname, GLint param);
    void glTexImage2D(TextureTarget target, GLint level, PixelFormat internalformat,
                      GLsizei width, GLsizei height, GLint border,
                      PixelFormat format, PixelType type, const void* pixels);
    void glTexParameteri(TextureTarget target, TextureParameter pname, GLint param);
    void glTexParameteriFilter(TextureTarget target, TextureParameter pname, TextureFilter filter);
    void glTexParameteriWrap(TextureTarget target, TextureParameter pname, TextureWrap wrap);

    // State
    void glEnable(Capability cap);
    void glDisable(Capability cap);
    void glBlendFunc(BlendFactor sfactor, BlendFactor dfactor);
    void glDepthFunc(CompareFunc func);
    void glDepthMask(GLboolean flag);
    void glClearDepth(GLdouble depth);
    void glClearDepthf(GLfloat depth);
    void glCullFace(CullFace mode);
    void glFrontFace(FrontFace mode);

    // Raw BlendFunc variant for factors not yet covered by BlendFactor enum
    void glBlendFuncRaw(GLenum sfactor, GLenum dfactor);
}
