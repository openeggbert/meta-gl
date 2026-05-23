#pragma once

#include "Types.hpp"
#include "Enums.hpp"
#include <cstddef>

namespace metagl
{
    // Buffers
    void glGenBuffers(int n, unsigned int* buffers);
    void glDeleteBuffers(int n, const unsigned int* buffers);
    void glBindBuffer(BufferTarget target, unsigned int buffer);
    void glBufferData(BufferTarget target, std::ptrdiff_t size, const void* data, BufferUsage usage);
    void glBufferSubData(BufferTarget target, std::ptrdiff_t offset, std::ptrdiff_t size, const void* data);
    void glBindBufferBase(BufferTarget target, unsigned int index, unsigned int buffer);

    // Context info
    const char* glGetString(StringName name);
    const char* glGetStringi(StringName name, unsigned int index);
    void glGetIntegerv(IntegerName pname, int* data);
    /// Raw variant for special cases (e.g. GL_VIEWPORT = 0x0BA2)
    void glGetIntegervRaw(unsigned int pname, int* data);

    // Shaders
    unsigned int glCreateShader(ShaderType type);
    void glShaderSource(unsigned int shader, int count, const char* const* string, const int* length);
    void glCompileShader(unsigned int shader);
    void glGetShaderiv(unsigned int shader, ShaderParameter pname, int* params);
    void glGetShaderInfoLog(unsigned int shader, int bufSize, int* length, char* infoLog);
    void glDeleteShader(unsigned int shader);

    // Programs
    unsigned int glCreateProgram();
    void glAttachShader(unsigned int program, unsigned int shader);
    void glDetachShader(unsigned int program, unsigned int shader);
    void glLinkProgram(unsigned int program);
    void glGetProgramiv(unsigned int program, ProgramParameter pname, int* params);
    void glGetProgramInfoLog(unsigned int program, int bufSize, int* length, char* infoLog);
    void glUseProgram(unsigned int program);
    void glDeleteProgram(unsigned int program);

    // Uniforms
    int glGetUniformLocation(unsigned int program, const char* name);
    void glUniform1i(int location, int v0);
    void glUniform1f(int location, float v0);
    void glUniform3f(int location, float v0, float v1, float v2);
    void glUniform4f(int location, float v0, float v1, float v2, float v3);
    void glUniformMatrix4fv(int location, int count, unsigned char transpose, const float* value);

    // Vertex arrays
    void glGenVertexArrays(int n, unsigned int* arrays);
    void glDeleteVertexArrays(int n, const unsigned int* arrays);
    void glBindVertexArray(unsigned int array);
    void glEnableVertexAttribArray(unsigned int index);
    void glVertexAttribPointer(unsigned int index, int size, DataType type, unsigned char normalized, std::size_t stride, const void* pointer);

    // Commands
    void glClear(ClearBufferBit mask);
    void glClearColor(float red, float green, float blue, float alpha);
    void glViewport(int x, int y, int width, int height);
    void glDrawArrays(PrimitiveType mode, int first, int count);
    void glDrawElements(PrimitiveType mode, int count, DataType type, const void* indices);

    // Textures
    void glGenTextures(int n, unsigned int* textures);
    void glDeleteTextures(int n, const unsigned int* textures);
    void glBindTexture(TextureTarget target, unsigned int texture);
    void glActiveTexture(unsigned int textureUnit); // GL_TEXTURE0 + index
    void glPixelStorei(unsigned int pname, int param);
    void glPixelStoreParam(PixelStoreParam pname, int param);
    void glTexImage2D(TextureTarget target, int level, PixelFormat internalformat,
                      int width, int height, int border,
                      PixelFormat format, PixelType type, const void* pixels);
    void glTexParameteri(TextureTarget target, TextureParameter pname, int param);
    void glTexParameteriFilter(TextureTarget target, TextureParameter pname, TextureFilter filter);
    void glTexParameteriWrap(TextureTarget target, TextureParameter pname, TextureWrap wrap);

    // State
    void glEnable(Capability cap);
    void glDisable(Capability cap);
    void glBlendFunc(BlendFactor sfactor, BlendFactor dfactor);
    void glDepthFunc(CompareFunc func);
    void glDepthMask(unsigned char flag);
    void glClearDepth(double depth);
    void glClearDepthf(float depth);
    void glCullFace(CullFace mode);
    void glFrontFace(FrontFace mode);

    // Raw BlendFunc variant for factors not yet covered by BlendFactor enum
    void glBlendFuncRaw(unsigned int sfactor, unsigned int dfactor);
}
