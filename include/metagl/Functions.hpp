#pragma once

#include "Types.hpp"
#include "Enums.hpp"

namespace metagl
{
    // State Management
    // #1 (2.0+) Enables a server-side GL capability (e.g. depth test, blending, culling)
    void glEnable(Capability cap);
    // #2 (2.0+) Disables a server-side GL capability
    void glDisable(Capability cap);
    // #3 (3.2+) Enables a capability for a specific indexed target (per-draw-buffer)
    void glEnablei(Capability target, GLuint index);
    // #4 (3.2+) Disables a capability for a specific indexed target
    void glDisablei(Capability target, GLuint index);
    // #5 (2.0+) Returns whether a capability is currently enabled
    GLboolean glIsEnabled(Capability cap);
    // #6 (3.2+) Returns whether an indexed capability is enabled
    GLboolean glIsEnabledi(Capability target, GLuint index);
    // #7 (2.0+) Sets blend source and destination factors for all draw buffers
    void glBlendFunc(BlendFactor sfactor, BlendFactor dfactor);
    // #8 (2.0+) Sets separate blend factors for RGB and alpha for all draw buffers
    void glBlendFuncSeparate(BlendFactor sfactorRGB, BlendFactor dfactorRGB, BlendFactor sfactorAlpha, BlendFactor dfactorAlpha);
    // #9 (3.2+) Sets blend factors for a specific indexed draw buffer
    void glBlendFunci(GLuint buf, BlendFactor src, BlendFactor dst);
    // #10 (3.2+) Sets separate RGB/alpha blend factors for a specific draw buffer
    void glBlendFuncSeparatei(GLuint buf, BlendFactor srcRGB, BlendFactor dstRGB, BlendFactor srcAlpha, BlendFactor dstAlpha);
    // #11 (2.0+) Sets the blend equation (e.g. GL_FUNC_ADD) for all draw buffers
    void glBlendEquation(BlendEquation mode);
    // #12 (2.0+) Sets separate blend equations for RGB and alpha for all draw buffers
    void glBlendEquationSeparate(BlendEquation modeRGB, BlendEquation modeAlpha);
    // #13 (3.2+) Sets the blend equation for a specific indexed draw buffer
    void glBlendEquationi(GLuint buf, BlendEquation mode);
    // #14 (3.2+) Sets separate blend equations for a specific draw buffer
    void glBlendEquationSeparatei(GLuint buf, BlendEquation modeRGB, BlendEquation modeAlpha);
    // #15 (2.0+) Sets the constant blend color used in blend factor expressions
    void glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    // #16 (3.2+) Ensures prior fragment writes are visible before next blending operation
    void glBlendBarrier(void);
    // #17 (2.0+) Enables/disables writing of R, G, B, A components for all draw buffers
    void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
    // #18 (3.2+) Enables/disables writing of color components for a specific draw buffer
    void glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
    // #19 (2.0+) Sets the depth comparison function (e.g. GL_LESS, GL_LEQUAL)
    void glDepthFunc(CompareFunc func);
    // #20 (2.0+) Enables or disables writing to the depth buffer
    void glDepthMask(GLboolean flag);
    // #21 (2.0+) Maps NDC depth to window-space depth via near/far plane values
    void glDepthRangef(GLfloat n, GLfloat f);
    // #22 (2.0+) Sets the stencil test function for both front and back faces
    void glStencilFunc(CompareFunc func, GLint ref, GLuint mask);
    // #23 (2.0+) Sets the stencil test function separately for front and back faces
    void glStencilFuncSeparate(CullFace face, CompareFunc func, GLint ref, GLuint mask);
    // #24 (2.0+) Sets stencil operations (sfail, dpfail, dppass) for both faces
    void glStencilOp(StencilOp fail, StencilOp zfail, StencilOp zpass);
    // #25 (2.0+) Sets stencil operations separately for front and back faces
    void glStencilOpSeparate(CullFace face, StencilOp sfail, StencilOp dpfail, StencilOp dppass);
    // #26 (2.0+) Sets the stencil write mask for both faces
    void glStencilMask(GLuint mask);
    // #27 (2.0+) Sets the stencil write mask separately for front and back faces
    void glStencilMaskSeparate(CullFace face, GLuint mask);
    // #28 (2.0+) Defines a rectangular region outside which all fragments are discarded
    void glScissor(GLint x, GLint y, GLsizei width, GLsizei height);
    // #29 (2.0+) Sets the affine mapping from NDC to window-space coordinates
    void glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
    // #30 (2.0+) Specifies whether front, back, or both polygon faces are culled
    void glCullFace(CullFace mode);
    // #31 (2.0+) Sets the winding order (CW or CCW) that defines front-facing polygons
    void glFrontFace(FrontFace mode);
    // #32 (2.0+) Sets the width of rasterized lines (only 1.0 is guaranteed portable)
    void glLineWidth(GLfloat width);
    // #33 (2.0+) Adds a scaled depth bias to polygon fragments (resolves z-fighting)
    void glPolygonOffset(GLfloat factor, GLfloat units);
    // #34 (2.0+) Sets a sample coverage mask used in multisampled rendering
    void glSampleCoverage(GLfloat value, GLboolean invert);
    // #35 (3.1+) Sets a bitmask qualifying which samples are written during MSAA
    void glSampleMaski(GLuint maskNumber, GLbitfield mask);
    // #36 (3.2+) Sets the minimum fraction of samples for which per-sample shading runs
    void glMinSampleShading(GLfloat value);
    // #37 (2.0+) Provides a quality/performance trade-off hint for certain operations
    void glHint(HintTarget target, HintMode mode);
    // #38 (2.0+) Sets pixel pack/unpack alignment and stride for texture transfers
    void glPixelStorei(PixelStoreParam pname, GLint param);
    // #39 (2.0+) Blocks the CPU until all pending GL commands have finished on the GPU
    void glFinish(void);
    // #40 (2.0+) Submits all pending GL commands to the GPU without waiting for completion
    void glFlush(void);
    // #41 (2.0+) Returns the most recent GL error flag and clears it
    ErrorCode glGetError(void);
    // #42 (2.0+) Queries a named GL state parameter as a boolean value
    void glGetBooleanv(GetParameter pname, GLboolean * data);
    // #43 (2.0+) Queries a named GL state parameter as a 32-bit integer
    void glGetIntegerv(GetParameter pname, GLint * data);
    // #44 (2.0+) Queries a named GL state parameter as a float
    void glGetFloatv(GetParameter pname, GLfloat * data);
    // #45 (3.0+) Queries a named GL state parameter as a 64-bit integer
    void glGetInteger64v(GetParameter pname, GLint64 * data);
    // #46 (3.0+) Queries an indexed GL state parameter as a 32-bit integer
    void glGetIntegeri_v(GetParameter target, GLuint index, GLint * data);
    // #47 (3.0+) Queries an indexed GL state parameter as a 64-bit integer
    void glGetInteger64i_v(GetParameter target, GLuint index, GLint64 * data);
    // #48 (3.1+) Queries an indexed GL state parameter as a boolean
    void glGetBooleani_v(GetParameter target, GLuint index, GLboolean * data);
    // #49 (2.0+) Returns a global implementation string (renderer, vendor, version, etc.)
    const GLubyte* glGetString(StringName name);
    // #50 (3.0+) Returns an indexed string (e.g. the nth supported extension)
    const GLubyte* glGetStringi(StringName name, GLuint index);
    // #51 (3.2+) Returns pointer-valued GL state such as debug callback pointers
    void glGetPointerv(GetPointerParameter pname, void ** params);

    // Buffer Objects
    // #52 (2.0+) Generates one or more buffer object names
    void glGenBuffers(GLsizei n, GLuint * buffers);
    // #53 (2.0+) Deletes buffer objects and frees their GPU memory
    void glDeleteBuffers(GLsizei n, const GLuint * buffers);
    // #54 (2.0+) Binds a buffer to a target (ARRAY_BUFFER, ELEMENT_ARRAY_BUFFER, etc.)
    void glBindBuffer(BufferTarget target, GLuint buffer);
    // #55 (3.0+) Binds a buffer to an indexed binding point (e.g. UBO slot N)
    void glBindBufferBase(BufferTarget target, GLuint index, GLuint buffer);
    // #56 (3.0+) Binds a sub-range of a buffer to an indexed binding point
    void glBindBufferRange(BufferTarget target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
    // #57 (2.0+) Allocates and optionally initializes a buffer's GPU data store
    void glBufferData(BufferTarget target, GLsizeiptr size, const void * data, BufferUsage usage);
    // #58 (2.0+) Updates a sub-range of an existing buffer without reallocating
    void glBufferSubData(BufferTarget target, GLintptr offset, GLsizeiptr size, const void * data);
    // #59 (3.0+) Copies a region from one buffer to another entirely on the GPU
    void glCopyBufferSubData(BufferTarget readTarget, BufferTarget writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
    // #60 (3.0+) Maps a buffer sub-range into CPU address space for read/write
    void* glMapBufferRange(BufferTarget target, GLintptr offset, GLsizeiptr length, MapBufferAccessMask access);
    // #61 (3.0+) Flushes explicitly mapped writes when GL_MAP_FLUSH_EXPLICIT_BIT is set
    void glFlushMappedBufferRange(BufferTarget target, GLintptr offset, GLsizeiptr length);
    // #62 (3.0+) Releases a buffer mapping; returns GL_FALSE if data was corrupted
    GLboolean glUnmapBuffer(BufferTarget target);
    // #63 (2.0+) Returns GL_TRUE if the name is a valid buffer object
    GLboolean glIsBuffer(GLuint buffer);
    // #64 (2.0+) Queries buffer parameters (size, usage, map status) as 32-bit integer
    void glGetBufferParameteriv(BufferTarget target, BufferParameter pname, GLint * params);
    // #65 (3.0+) Queries buffer parameters (e.g. size on large buffers) as 64-bit integer
    void glGetBufferParameteri64v(BufferTarget target, BufferParameter pname, GLint64 * params);
    // #66 (3.0+) Returns the pointer to the currently mapped buffer data store
    void glGetBufferPointerv(BufferTarget target, BufferParameter pname, void ** params);

    // Vertex Arrays
    // #67 (3.0+) Generates one or more Vertex Array Object (VAO) names
    void glGenVertexArrays(GLsizei n, GLuint * arrays);
    // #68 (3.0+) Deletes VAOs
    void glDeleteVertexArrays(GLsizei n, const GLuint * arrays);
    // #69 (3.0+) Binds a VAO; all subsequent attribute state is recorded into it
    void glBindVertexArray(GLuint array);
    // #70 (3.0+) Returns GL_TRUE if the name is a valid VAO
    GLboolean glIsVertexArray(GLuint array);
    // #71 (2.0+) Enables a generic vertex attribute array at a given index
    void glEnableVertexAttribArray(GLuint index);
    // #72 (2.0+) Disables a generic vertex attribute array; attribute uses constant value
    void glDisableVertexAttribArray(GLuint index);
    // #73 (2.0+) Defines layout/source of a float or normalized-integer vertex attribute
    void glVertexAttribPointer(GLuint index, GLint size, DataType type, GLboolean normalized, GLsizei stride, const void * pointer);
    // #74 (3.0+) Defines layout/source of an integer vertex attribute (no normalization)
    void glVertexAttribIPointer(GLuint index, GLint size, DataType type, GLsizei stride, const void * pointer);
    // #75 (3.0+) Sets the instancing divisor for an attribute (0=per-vertex, N=per-N-instances)
    void glVertexAttribDivisor(GLuint index, GLuint divisor);
    // #76 (2.0+) Sets a constant float scalar value for a vertex attribute
    void glVertexAttrib1f(GLuint index, GLfloat x);
    // #77 (2.0+) Sets a constant vec2 float value for a vertex attribute
    void glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y);
    // #78 (2.0+) Sets a constant vec3 float value for a vertex attribute
    void glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z);
    // #79 (2.0+) Sets a constant vec4 float value for a vertex attribute
    void glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    // #80 (2.0+) Sets a constant float scalar for a vertex attribute from a pointer
    void glVertexAttrib1fv(GLuint index, const GLfloat * v);
    // #81 (2.0+) Sets a constant vec2 float value for a vertex attribute from a pointer
    void glVertexAttrib2fv(GLuint index, const GLfloat * v);
    // #82 (2.0+) Sets a constant vec3 float value for a vertex attribute from a pointer
    void glVertexAttrib3fv(GLuint index, const GLfloat * v);
    // #83 (2.0+) Sets a constant vec4 float value for a vertex attribute from a pointer
    void glVertexAttrib4fv(GLuint index, const GLfloat * v);
    // #84 (3.0+) Sets a constant ivec4 signed integer value for a vertex attribute
    void glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w);
    // #85 (3.0+) Sets a constant uvec4 unsigned integer value for a vertex attribute
    void glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
    // #86 (3.0+) Sets a constant ivec4 value for a vertex attribute from a pointer
    void glVertexAttribI4iv(GLuint index, const GLint * v);
    // #87 (3.0+) Sets a constant uvec4 value for a vertex attribute from a pointer
    void glVertexAttribI4uiv(GLuint index, const GLuint * v);
    // #88 (2.0+) Queries float state of a vertex attribute (type, size, stride, etc.)
    void glGetVertexAttribfv(GLuint index, VertexAttribParameter pname, GLfloat * params);
    // #89 (2.0+) Queries integer state of a vertex attribute
    void glGetVertexAttribiv(GLuint index, VertexAttribParameter pname, GLint * params);
    // #90 (3.0+) Queries integer state of an integer-type vertex attribute
    void glGetVertexAttribIiv(GLuint index, VertexAttribParameter pname, GLint * params);
    // #91 (3.0+) Queries unsigned integer state of an unsigned-integer vertex attribute
    void glGetVertexAttribIuiv(GLuint index, VertexAttribParameter pname, GLuint * params);
    // #92 (2.0+) Returns the offset/pointer stored for a vertex attribute
    void glGetVertexAttribPointerv(GLuint index, VertexAttribParameter pname, void ** pointer);
    // #93 (3.1+) Specifies float attribute format independently from buffer binding
    void glVertexAttribFormat(GLuint attribindex, GLint size, DataType type, GLboolean normalized, GLuint relativeoffset);
    // #94 (3.1+) Specifies integer attribute format independently from buffer binding
    void glVertexAttribIFormat(GLuint attribindex, GLint size, DataType type, GLuint relativeoffset);
    // #95 (3.1+) Associates a vertex attribute index with a vertex buffer binding point
    void glVertexAttribBinding(GLuint attribindex, GLuint bindingindex);
    // #96 (3.1+) Binds a buffer to a vertex buffer binding point with offset and stride
    void glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
    // #97 (3.1+) Sets the instancing divisor for a vertex buffer binding point
    void glVertexBindingDivisor(GLuint bindingindex, GLuint divisor);

    // Drawing
    // #98 (2.0+) Renders primitives from vertex arrays starting at a given offset
    void glDrawArrays(PrimitiveType mode, GLint first, GLsizei count);
    // #99 (3.0+) Renders multiple instances of geometry using vertex arrays
    void glDrawArraysInstanced(PrimitiveType mode, GLint first, GLsizei count, GLsizei instancecount);
    // #100 (3.1+) Renders instances; draw parameters read from GL_DRAW_INDIRECT_BUFFER
    void glDrawArraysIndirect(PrimitiveType mode, const void * indirect);
    // #101 (2.0+) Renders indexed primitives from vertex arrays and an index buffer
    void glDrawElements(PrimitiveType mode, GLsizei count, DataType type, const void * indices);
    // #102 (3.0+) Renders multiple instances using indexed drawing
    void glDrawElementsInstanced(PrimitiveType mode, GLsizei count, DataType type, const void * indices, GLsizei instancecount);
    // #103 (3.0+) Indexed draw with index range hints for driver prefetch optimization
    void glDrawRangeElements(PrimitiveType mode, GLuint start, GLuint end, GLsizei count, DataType type, const void * indices);
    // #104 (3.2+) Indexed draw with a constant base vertex offset added to each index
    void glDrawElementsBaseVertex(PrimitiveType mode, GLsizei count, DataType type, const void * indices, GLint basevertex);
    // #105 (3.2+) Instanced indexed draw with a base vertex offset
    void glDrawElementsInstancedBaseVertex(PrimitiveType mode, GLsizei count, DataType type, const void * indices, GLsizei instancecount, GLint basevertex);
    // #106 (3.2+) Range-indexed draw with a base vertex offset
    void glDrawRangeElementsBaseVertex(PrimitiveType mode, GLuint start, GLuint end, GLsizei count, DataType type, const void * indices, GLint basevertex);
    // #107 (3.1+) Indexed instanced draw; parameters read from GL_DRAW_INDIRECT_BUFFER
    void glDrawElementsIndirect(PrimitiveType mode, DataType type, const void * indirect);
    // #108 (3.0+) Specifies the list of color buffers that fragment outputs are written to
    void glDrawBuffers(GLsizei n, const DrawBuffer * bufs);
    // #109 (3.0+) Selects a color buffer as the source for glReadPixels and copy operations
    void glReadBuffer(ReadBuffer src);
    // #110 (2.0+) Reads a rectangular block of pixels from the framebuffer into CPU memory
    void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, PixelFormat format, PixelType type, void * pixels);
    // #111 (3.2+) Reads pixels with an explicit destination buffer size for robustness
    void glReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, PixelFormat format, PixelType type, GLsizei bufSize, void * data);
    // #112 (2.0+) Clears color, depth, and/or stencil buffers to their clear values
    void glClear(ClearBufferBit mask);
    // #113 (2.0+) Sets the RGBA value used when clearing the color buffer
    void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    // #114 (2.0+) Sets the float depth value (0.0–1.0) used when clearing the depth buffer
    void glClearDepthf(GLfloat d);
    // #115 (2.0+) Sets the integer value used when clearing the stencil buffer
    void glClearStencil(GLint s);
    // #116 (3.0+) Clears a float color or depth buffer attachment to a given value
    void glClearBufferfv(ClearBuffer buffer, GLint drawbuffer, const GLfloat * value);
    // #117 (3.0+) Clears an integer color or stencil buffer attachment to a given value
    void glClearBufferiv(ClearBuffer buffer, GLint drawbuffer, const GLint * value);
    // #118 (3.0+) Clears an unsigned integer color buffer attachment to a given value
    void glClearBufferuiv(ClearBuffer buffer, GLint drawbuffer, const GLuint * value);
    // #119 (3.0+) Clears depth and stencil buffer attachments together in one call
    void glClearBufferfi(ClearBuffer buffer, GLint drawbuffer, GLfloat depth, GLint stencil);

    // Shaders
    // #120 (2.0+) Creates a shader object of the given type and returns its handle
    GLuint glCreateShader(ShaderType type);
    // #121 (2.0+) Marks a shader for deletion (deferred until detached from all programs)
    void glDeleteShader(GLuint shader);
    // #122 (2.0+) Loads GLSL source strings into a shader object
    void glShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length);
    // #123 (2.0+) Compiles the GLSL source previously loaded into a shader object
    void glCompileShader(GLuint shader);
    // #124 (2.0+) Loads pre-compiled binary shader code into one or more shader objects
    void glShaderBinary(GLsizei count, const GLuint * shaders, ShaderBinaryFormat binaryFormat, const void * binary, GLsizei length);
    // #125 (2.0+) Hints that the GLSL compiler resources may be freed
    void glReleaseShaderCompiler(void);
    // #126 (2.0+) Queries shader parameters (compile status, type, source length, etc.)
    void glGetShaderiv(GLuint shader, ShaderParameter pname, GLint * params);
    // #127 (2.0+) Returns the compiler info log for a shader (errors and warnings)
    void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
    // #128 (2.0+) Returns the GLSL source code stored in a shader object
    void glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source);
    // #129 (2.0+) Returns the precision range for lowp/mediump/highp in vertex/fragment shaders
    void glGetShaderPrecisionFormat(ShaderType shadertype, PrecisionType precisiontype, GLint * range, GLint * precision);
    // #130 (2.0+) Returns GL_TRUE if the name is a valid shader object
    GLboolean glIsShader(GLuint shader);
    // #131 (2.0+) Creates a program object and returns its handle
    GLuint glCreateProgram(void);
    // #132 (2.0+) Deletes a program object (deferred until no longer in use)
    void glDeleteProgram(GLuint program);
    // #133 (2.0+) Attaches a compiled shader to a program for the next link operation
    void glAttachShader(GLuint program, GLuint shader);
    // #134 (2.0+) Detaches a shader from a program
    void glDetachShader(GLuint program, GLuint shader);
    // #135 (2.0+) Links all attached shaders into an executable GPU program
    void glLinkProgram(GLuint program);
    // #136 (2.0+) Installs a linked program as part of the current rendering state
    void glUseProgram(GLuint program);
    // #137 (2.0+) Validates whether a program can execute given the current GL state
    void glValidateProgram(GLuint program);
    // #138 (2.0+) Queries program parameters (link status, active uniforms, etc.)
    void glGetProgramiv(GLuint program, ProgramParameter pname, GLint * params);
    // #139 (2.0+) Returns the linker info log for a program (errors and warnings)
    void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
    // #140 (2.0+) Returns GL_TRUE if the name is a valid program object
    GLboolean glIsProgram(GLuint program);
    // #141 (2.0+) Returns the shader objects currently attached to a program
    void glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders);
    // #142 (2.0+) Associates a vertex shader input variable with an attribute index before link
    void glBindAttribLocation(GLuint program, GLuint index, const GLchar * name);
    // #143 (2.0+) Returns the attribute index of a named vertex shader input in a linked program
    GLint glGetAttribLocation(GLuint program, const GLchar * name);
    // #144 (2.0+) Returns name, type, and size of an active vertex attribute variable
    void glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, UniformType * type, GLchar * name);
    // #145 (3.0+) Returns the binary representation of a linked program for caching
    void glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei * length, ProgramBinaryFormat * binaryFormat, void * binary);
    // #146 (3.0+) Loads a cached binary into a program, bypassing compilation and linking
    void glProgramBinary(GLuint program, ProgramBinaryFormat binaryFormat, const void * binary, GLsizei length);
    // #147 (3.0+) Sets program parameters (binary retrievable hint, separable flag)
    void glProgramParameteri(GLuint program, ProgramParameter pname, GLint value);
    // #148 (3.0+) Returns the fragment output location for a named output variable
    GLint glGetFragDataLocation(GLuint program, const GLchar * name);
    // #149 (3.1+) Queries properties of a program interface (e.g. number of active uniforms)
    void glGetProgramInterfaceiv(GLuint program, ProgramInterface programInterface, ProgramInterfaceParameter pname, GLint * params);
    // #150 (3.1+) Returns the index of a named resource within a program interface
    GLuint glGetProgramResourceIndex(GLuint program, ProgramInterface programInterface, const GLchar * name);
    // #151 (3.1+) Returns the name of a resource at a given index in a program interface
    void glGetProgramResourceName(GLuint program, ProgramInterface programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name);
    // #152 (3.1+) Returns multiple properties of a program interface resource in one call
    void glGetProgramResourceiv(GLuint program, ProgramInterface programInterface, GLuint index, GLsizei propCount, const ProgramResourceProperty * props, GLsizei count, GLsizei * length, GLint * params);
    // #153 (3.1+) Returns the location of a named resource within a program interface
    GLint glGetProgramResourceLocation(GLuint program, ProgramInterface programInterface, const GLchar * name);

    // Uniforms
    // #154 (2.0+) Returns the integer location of a named uniform in a linked program
    GLint glGetUniformLocation(GLuint program, const GLchar * name);
    // #155 (2.0+) Returns the name, type, and size of an active uniform variable
    void glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, UniformType * type, GLchar * name);
    // #156 (3.0+) Queries parameters for multiple uniforms by index in one call
    void glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, UniformParameter pname, GLint * params);
    // #157 (3.0+) Returns the indices of multiple named uniform variables
    void glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices);
    // #158 (3.0+) Returns the index of a named uniform block in a linked program
    GLuint glGetUniformBlockIndex(GLuint program, const GLchar * uniformBlockName);
    // #159 (3.0+) Queries parameters of a uniform block (size, binding, member count)
    void glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, UniformBlockParameter pname, GLint * params);
    // #160 (3.0+) Returns the name string of a uniform block at a given index
    void glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName);
    // #161 (3.0+) Assigns a uniform block to a specific uniform buffer binding point
    void glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
    // #162 (2.0+) Sets a float scalar uniform in the current program
    void glUniform1f(GLint location, GLfloat v0);
    // #163 (2.0+) Sets a vec2 float uniform in the current program
    void glUniform2f(GLint location, GLfloat v0, GLfloat v1);
    // #164 (2.0+) Sets a vec3 float uniform in the current program
    void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
    // #165 (2.0+) Sets a vec4 float uniform in the current program
    void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
    // #166 (2.0+) Sets an array of float scalar uniforms in the current program
    void glUniform1fv(GLint location, GLsizei count, const GLfloat * value);
    // #167 (2.0+) Sets an array of vec2 uniforms in the current program
    void glUniform2fv(GLint location, GLsizei count, const GLfloat * value);
    // #168 (2.0+) Sets an array of vec3 uniforms in the current program
    void glUniform3fv(GLint location, GLsizei count, const GLfloat * value);
    // #169 (2.0+) Sets an array of vec4 uniforms in the current program
    void glUniform4fv(GLint location, GLsizei count, const GLfloat * value);
    // #170 (2.0+) Sets an int scalar uniform; also used to assign sampler texture units
    void glUniform1i(GLint location, GLint v0);
    // #171 (2.0+) Sets an ivec2 uniform in the current program
    void glUniform2i(GLint location, GLint v0, GLint v1);
    // #172 (2.0+) Sets an ivec3 uniform in the current program
    void glUniform3i(GLint location, GLint v0, GLint v1, GLint v2);
    // #173 (2.0+) Sets an ivec4 uniform in the current program
    void glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
    // #174 (2.0+) Sets an array of int scalar uniforms in the current program
    void glUniform1iv(GLint location, GLsizei count, const GLint * value);
    // #175 (2.0+) Sets an array of ivec2 uniforms in the current program
    void glUniform2iv(GLint location, GLsizei count, const GLint * value);
    // #176 (2.0+) Sets an array of ivec3 uniforms in the current program
    void glUniform3iv(GLint location, GLsizei count, const GLint * value);
    // #177 (2.0+) Sets an array of ivec4 uniforms in the current program
    void glUniform4iv(GLint location, GLsizei count, const GLint * value);
    // #178 (3.0+) Sets an unsigned int scalar uniform in the current program
    void glUniform1ui(GLint location, GLuint v0);
    // #179 (3.0+) Sets a uvec2 uniform in the current program
    void glUniform2ui(GLint location, GLuint v0, GLuint v1);
    // #180 (3.0+) Sets a uvec3 uniform in the current program
    void glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2);
    // #181 (3.0+) Sets a uvec4 uniform in the current program
    void glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
    // #182 (3.0+) Sets an array of unsigned int scalar uniforms
    void glUniform1uiv(GLint location, GLsizei count, const GLuint * value);
    // #183 (3.0+) Sets an array of uvec2 uniforms
    void glUniform2uiv(GLint location, GLsizei count, const GLuint * value);
    // #184 (3.0+) Sets an array of uvec3 uniforms
    void glUniform3uiv(GLint location, GLsizei count, const GLuint * value);
    // #185 (3.0+) Sets an array of uvec4 uniforms
    void glUniform4uiv(GLint location, GLsizei count, const GLuint * value);
    // #186 (2.0+) Sets a mat2 uniform (or array of mat2) in the current program
    void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
    // #187 (2.0+) Sets a mat3 uniform (or array of mat3) in the current program
    void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
    // #188 (2.0+) Sets a mat4 uniform (or array of mat4) in the current program
    void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
    // #189 (3.0+) Sets a mat2x3 uniform (2 columns, 3 rows); non-square matrices not in ES 2.0
    void glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
    // #190 (3.0+) Sets a mat2x4 uniform in the current program
    void glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
    // #191 (3.0+) Sets a mat3x2 uniform in the current program
    void glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
    // #192 (3.0+) Sets a mat3x4 uniform in the current program
    void glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
    // #193 (3.0+) Sets a mat4x2 uniform in the current program
    void glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
    // #194 (3.0+) Sets a mat4x3 uniform in the current program
    void glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
    // #195 (2.0+) Returns the current value of a float uniform from a linked program
    void glGetUniformfv(GLuint program, GLint location, GLfloat * params);
    // #196 (2.0+) Returns the current value of an integer uniform from a linked program
    void glGetUniformiv(GLuint program, GLint location, GLint * params);
    // #197 (3.0+) Returns the current value of an unsigned integer uniform
    void glGetUniformuiv(GLuint program, GLint location, GLuint * params);
    // #198 (3.2+) Returns float uniform values with an explicit destination buffer size for robustness
    void glGetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat * params);
    // #199 (3.2+) Returns integer uniform values with an explicit destination buffer size for robustness
    void glGetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint * params);
    // #200 (3.2+) Returns unsigned integer uniform values with an explicit destination buffer size for robustness
    void glGetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint * params);
    // #201 (3.1+) Sets a float scalar uniform in a specific program without binding it
    void glProgramUniform1f(GLuint program, GLint location, GLfloat v0);
    // #202 (3.1+) Sets a vec2 float uniform in a specific program without binding it
    void glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1);
    // #203 (3.1+) Sets a vec3 float uniform in a specific program without binding it
    void glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
    // #204 (3.1+) Sets a vec4 float uniform in a specific program without binding it
    void glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
    // #205 (3.1+) Sets an array of float scalar uniforms in a specific program
    void glProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat * value);
    // #206 (3.1+) Sets an array of vec2 uniforms in a specific program
    void glProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat * value);
    // #207 (3.1+) Sets an array of vec3 uniforms in a specific program
    void glProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat * value);
    // #208 (3.1+) Sets an array of vec4 uniforms in a specific program
    void glProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat * value);
    // #209 (3.1+) Sets an int scalar uniform in a specific program
    void glProgramUniform1i(GLuint program, GLint location, GLint v0);
    // #210 (3.1+) Sets an ivec2 uniform in a specific program
    void glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1);
    // #211 (3.1+) Sets an ivec3 uniform in a specific program
    void glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
    // #212 (3.1+) Sets an ivec4 uniform in a specific program
    void glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
    // #213 (3.1+) Sets an array of int scalars in a specific program
    void glProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint * value);
    // #214 (3.1+) Sets an array of ivec2 uniforms in a specific program
    void glProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint * value);
    // #215 (3.1+) Sets an array of ivec3 uniforms in a specific program
    void glProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint * value);
    // #216 (3.1+) Sets an array of ivec4 uniforms in a specific program
    void glProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint * value);
    // #217 (3.1+) Sets an unsigned int scalar uniform in a specific program
    void glProgramUniform1ui(GLuint program, GLint location, GLuint v0);
    // #218 (3.1+) Sets a uvec2 uniform in a specific program
    void glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1);
    // #219 (3.1+) Sets a uvec3 uniform in a specific program
    void glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
    // #220 (3.1+) Sets a uvec4 uniform in a specific program
    void glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
    // #221 (3.1+) Sets an array of unsigned int scalars in a specific program
    void glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint * value);
    // #222 (3.1+) Sets an array of uvec2 uniforms in a specific program
    void glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint * value);
    // #223 (3.1+) Sets an array of uvec3 uniforms in a specific program
    void glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint * value);
    // #224 (3.1+) Sets an array of uvec4 uniforms in a specific program
    void glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint * value);
    // #225 (3.1+) Sets a mat2 uniform in a specific program
    void glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
    // #226 (3.1+) Sets a mat3 uniform in a specific program
    void glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
    // #227 (3.1+) Sets a mat4 uniform in a specific program
    void glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
    // #228 (3.1+) Sets a mat2x3 uniform in a specific program
    void glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
    // #229 (3.1+) Sets a mat2x4 uniform in a specific program
    void glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
    // #230 (3.1+) Sets a mat3x2 uniform in a specific program
    void glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
    // #231 (3.1+) Sets a mat3x4 uniform in a specific program
    void glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
    // #232 (3.1+) Sets a mat4x2 uniform in a specific program
    void glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
    // #233 (3.1+) Sets a mat4x3 uniform in a specific program
    void glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);

    // Textures
    // #234 (2.0+) Generates one or more texture object names
    void glGenTextures(GLsizei n, GLuint * textures);
    // #235 (2.0+) Deletes texture objects and frees their GPU memory
    void glDeleteTextures(GLsizei n, const GLuint * textures);
    // #236 (2.0+) Binds a texture to a target in the active texture unit
    void glBindTexture(TextureTarget target, GLuint texture);
    // #237 (2.0+) Selects the active texture unit for subsequent texture operations
    void glActiveTexture(TextureUnit texture);
    // #238 (2.0+) Returns GL_TRUE if the name is a valid texture object
    GLboolean glIsTexture(GLuint texture);
    // #239 (2.0+) Specifies a 2D texture image and allocates GPU storage
    void glTexImage2D(TextureTarget target, GLint level, InternalFormat internalformat, GLsizei width, GLsizei height, GLint border, PixelFormat format, PixelType type, const void * pixels);
    // #240 (3.0+) Specifies a 3D or 2D-array texture image and allocates GPU storage
    void glTexImage3D(TextureTarget target, GLint level, InternalFormat internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, PixelFormat format, PixelType type, const void * pixels);
    // #241 (2.0+) Updates a sub-region of an existing 2D texture image
    void glTexSubImage2D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, PixelFormat format, PixelType type, const void * pixels);
    // #242 (3.0+) Updates a sub-region of an existing 3D or 2D-array texture
    void glTexSubImage3D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, PixelFormat format, PixelType type, const void * pixels);
    // #243 (3.0+) Allocates immutable storage for all mip levels of a 2D texture
    void glTexStorage2D(TextureTarget target, GLsizei levels, InternalFormat internalformat, GLsizei width, GLsizei height);
    // #244 (3.0+) Allocates immutable storage for all mip levels of a 3D or array texture
    void glTexStorage3D(TextureTarget target, GLsizei levels, InternalFormat internalformat, GLsizei width, GLsizei height, GLsizei depth);
    // #245 (3.1+) Allocates immutable multisample storage for a 2D MSAA texture
    void glTexStorage2DMultisample(TextureTarget target, GLsizei samples, InternalFormat internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
    // #246 (3.2+) Allocates immutable multisample storage for a 2D MSAA array texture
    void glTexStorage3DMultisample(TextureTarget target, GLsizei samples, InternalFormat internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
    // #247 (2.0+) Loads compressed image data (ETC2, ASTC, etc.) into a 2D texture
    void glCompressedTexImage2D(TextureTarget target, GLint level, CompressedInternalFormat internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data);
    // #248 (3.0+) Loads compressed image data into a 3D or 2D-array texture
    void glCompressedTexImage3D(TextureTarget target, GLint level, CompressedInternalFormat internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data);
    // #249 (2.0+) Updates a sub-region of an existing compressed 2D texture
    void glCompressedTexSubImage2D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, CompressedInternalFormat format, GLsizei imageSize, const void * data);
    // #250 (3.0+) Updates a sub-region of an existing compressed 3D or array texture
    void glCompressedTexSubImage3D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, CompressedInternalFormat format, GLsizei imageSize, const void * data);
    // #251 (2.0+) Copies pixels from the read framebuffer into a 2D texture image
    void glCopyTexImage2D(TextureTarget target, GLint level, InternalFormat internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
    // #252 (2.0+) Copies a framebuffer region into a sub-region of a 2D texture
    void glCopyTexSubImage2D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
    // #253 (3.0+) Copies a framebuffer region into a slice of a 3D or array texture
    void glCopyTexSubImage3D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
    // #254 (3.2+) Copies a region between two textures without format conversion
    void glCopyImageSubData(GLuint srcName, TextureTarget srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, TextureTarget dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
    // #255 (2.0+) Auto-generates all mipmap levels below the base level by downsampling
    void glGenerateMipmap(TextureTarget target);
    // #256 (2.0+) Sets a float texture sampling parameter (filter, LOD, wrap mode)
    void glTexParameterf(TextureTarget target, TextureParameter pname, GLfloat param);
    // #257 (2.0+) Sets an integer texture sampling parameter
    void glTexParameteri(TextureTarget target, TextureParameter pname, GLint param);
    // #258 (2.0+) Sets multiple float texture parameters from a pointer
    void glTexParameterfv(TextureTarget target, TextureParameter pname, const GLfloat * params);
    // #259 (2.0+) Sets multiple integer texture parameters from a pointer
    void glTexParameteriv(TextureTarget target, TextureParameter pname, const GLint * params);
    // #260 (3.2+) Sets integer texture parameters without integer-to-float conversion
    void glTexParameterIiv(TextureTarget target, TextureParameter pname, const GLint * params);
    // #261 (3.2+) Sets unsigned integer texture parameters without conversion
    void glTexParameterIuiv(TextureTarget target, TextureParameter pname, const GLuint * params);
    // #262 (2.0+) Returns float texture sampling parameters
    void glGetTexParameterfv(TextureTarget target, TextureParameter pname, GLfloat * params);
    // #263 (2.0+) Returns integer texture sampling parameters
    void glGetTexParameteriv(TextureTarget target, TextureParameter pname, GLint * params);
    // #264 (3.2+) Returns integer texture parameters as raw integers
    void glGetTexParameterIiv(TextureTarget target, TextureParameter pname, GLint * params);
    // #265 (3.2+) Returns unsigned integer texture parameters as raw unsigned integers
    void glGetTexParameterIuiv(TextureTarget target, TextureParameter pname, GLuint * params);
    // #266 (3.1+) Returns integer parameters of a specific texture mipmap level
    void glGetTexLevelParameteriv(TextureTarget target, GLint level, TextureLevelParameter pname, GLint * params);
    // #267 (3.1+) Returns float parameters of a specific texture mipmap level
    void glGetTexLevelParameterfv(TextureTarget target, GLint level, TextureLevelParameter pname, GLfloat * params);
    // #268 (3.2+) Attaches a buffer object's data store to a buffer texture
    void glTexBuffer(TextureTarget target, InternalFormat internalformat, GLuint buffer);
    // #269 (3.2+) Attaches a sub-range of a buffer object to a buffer texture
    void glTexBufferRange(TextureTarget target, InternalFormat internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
    // #270 (3.1+) Returns the location of a specific sample in a multisample texture
    void glGetMultisamplefv(MultisampleParameter pname, GLuint index, GLfloat * val);
    // #271 (3.0+) Queries implementation properties for a given internal format and target
    void glGetInternalformativ(InternalFormatTarget target, InternalFormat internalformat, InternalFormatParameter pname, GLsizei count, GLint * params);
    // #272 (3.1+) Binds a texture level to an image unit for image load/store in shaders
    void glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, ImageAccess access, InternalFormat format);

    // Samplers
    // #273 (3.0+) Generates one or more sampler object names
    void glGenSamplers(GLsizei count, GLuint * samplers);
    // #274 (3.0+) Deletes sampler objects
    void glDeleteSamplers(GLsizei count, const GLuint * samplers);
    // #275 (3.0+) Binds a sampler to a texture unit, overriding the texture's own sampling state
    void glBindSampler(GLuint unit, GLuint sampler);
    // #276 (3.0+) Returns GL_TRUE if the name is a valid sampler object
    GLboolean glIsSampler(GLuint sampler);
    // #277 (3.0+) Sets a float sampling parameter on a sampler object
    void glSamplerParameterf(GLuint sampler, TextureParameter pname, GLfloat param);
    // #278 (3.0+) Sets an integer sampling parameter on a sampler object
    void glSamplerParameteri(GLuint sampler, TextureParameter pname, GLint param);
    // #279 (3.0+) Sets multiple float sampling parameters on a sampler from a pointer
    void glSamplerParameterfv(GLuint sampler, TextureParameter pname, const GLfloat * param);
    // #280 (3.0+) Sets multiple integer sampling parameters on a sampler from a pointer
    void glSamplerParameteriv(GLuint sampler, TextureParameter pname, const GLint * param);
    // #281 (3.2+) Sets signed integer sampler parameters without conversion
    void glSamplerParameterIiv(GLuint sampler, TextureParameter pname, const GLint * param);
    // #282 (3.2+) Sets unsigned integer sampler parameters without conversion
    void glSamplerParameterIuiv(GLuint sampler, TextureParameter pname, const GLuint * param);
    // #283 (3.0+) Returns float sampling parameters from a sampler object
    void glGetSamplerParameterfv(GLuint sampler, TextureParameter pname, GLfloat * params);
    // #284 (3.0+) Returns integer sampling parameters from a sampler object
    void glGetSamplerParameteriv(GLuint sampler, TextureParameter pname, GLint * params);
    // #285 (3.2+) Returns signed integer sampler parameters as raw integers
    void glGetSamplerParameterIiv(GLuint sampler, TextureParameter pname, GLint * params);
    // #286 (3.2+) Returns unsigned integer sampler parameters as raw unsigned integers
    void glGetSamplerParameterIuiv(GLuint sampler, TextureParameter pname, GLuint * params);

    // Framebuffers
    // #287 (2.0+) Generates one or more framebuffer object names
    void glGenFramebuffers(GLsizei n, GLuint * framebuffers);
    // #288 (2.0+) Deletes framebuffer objects
    void glDeleteFramebuffers(GLsizei n, const GLuint * framebuffers);
    // #289 (2.0+) Binds a framebuffer to GL_FRAMEBUFFER, GL_READ_FRAMEBUFFER, or GL_DRAW_FRAMEBUFFER
    void glBindFramebuffer(FramebufferTarget target, GLuint framebuffer);
    // #290 (2.0+) Returns GL_TRUE if the name is a valid framebuffer object
    GLboolean glIsFramebuffer(GLuint framebuffer);
    // #291 (2.0+) Returns the completeness status of the bound framebuffer
    FramebufferStatus glCheckFramebufferStatus(FramebufferTarget target);
    // #292 (2.0+) Attaches a 2D texture level as a framebuffer color/depth/stencil attachment
    void glFramebufferTexture2D(FramebufferTarget target, FramebufferAttachment attachment, TextureTarget textarget, GLuint texture, GLint level);
    // #293 (3.0+) Attaches a single layer of a layered texture to a framebuffer attachment point
    void glFramebufferTextureLayer(FramebufferTarget target, FramebufferAttachment attachment, GLuint texture, GLint level, GLint layer);
    // #294 (3.2+) Attaches an entire layered texture to a framebuffer (for geometry shader layered rendering)
    void glFramebufferTexture(FramebufferTarget target, FramebufferAttachment attachment, GLuint texture, GLint level);
    // #295 (2.0+) Attaches a renderbuffer as a framebuffer color/depth/stencil attachment
    void glFramebufferRenderbuffer(FramebufferTarget target, FramebufferAttachment attachment, RenderbufferTarget renderbuffertarget, GLuint renderbuffer);
    // #296 (3.1+) Sets default parameters on a framebuffer that has no attachments
    void glFramebufferParameteri(FramebufferTarget target, FramebufferDefaultParameter pname, GLint param);
    // #297 (3.1+) Returns parameters set on a framebuffer via glFramebufferParameteri
    void glGetFramebufferParameteriv(FramebufferTarget target, FramebufferDefaultParameter pname, GLint * params);
    // #298 (2.0+) Returns parameters of a specific framebuffer attachment
    void glGetFramebufferAttachmentParameteriv(FramebufferTarget target, FramebufferAttachment attachment, FramebufferAttachmentParameter pname, GLint * params);
    // #299 (3.0+) Copies a rectangle between framebuffers; also resolves MSAA
    void glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, ClearBufferBit mask, TextureFilter filter);
    // #300 (3.0+) Hints that attachment contents are no longer needed (bandwidth optimization)
    void glInvalidateFramebuffer(FramebufferTarget target, GLsizei numAttachments, const FramebufferAttachment * attachments);
    // #301 (3.0+) Invalidates a sub-rectangle of framebuffer attachments
    void glInvalidateSubFramebuffer(FramebufferTarget target, GLsizei numAttachments, const FramebufferAttachment * attachments, GLint x, GLint y, GLsizei width, GLsizei height);

    // Renderbuffers
    // #302 (2.0+) Generates one or more renderbuffer object names
    void glGenRenderbuffers(GLsizei n, GLuint * renderbuffers);
    // #303 (2.0+) Deletes renderbuffer objects and frees their GPU memory
    void glDeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers);
    // #304 (2.0+) Binds a renderbuffer to the GL_RENDERBUFFER target
    void glBindRenderbuffer(RenderbufferTarget target, GLuint renderbuffer);
    // #305 (2.0+) Returns GL_TRUE if the name is a valid renderbuffer object
    GLboolean glIsRenderbuffer(GLuint renderbuffer);
    // #306 (2.0+) Allocates single-sample GPU storage for a renderbuffer
    void glRenderbufferStorage(RenderbufferTarget target, InternalFormat internalformat, GLsizei width, GLsizei height);
    // #307 (3.0+) Allocates multisample GPU storage for a renderbuffer (for MSAA)
    void glRenderbufferStorageMultisample(RenderbufferTarget target, GLsizei samples, InternalFormat internalformat, GLsizei width, GLsizei height);
    // #308 (2.0+) Returns parameters of the bound renderbuffer (width, height, format, samples)
    void glGetRenderbufferParameteriv(RenderbufferTarget target, RenderbufferParameter pname, GLint * params);

    // Transform Feedback
    // #309 (3.0+) Generates one or more transform feedback object names
    void glGenTransformFeedbacks(GLsizei n, GLuint * ids);
    // #310 (3.0+) Deletes transform feedback objects
    void glDeleteTransformFeedbacks(GLsizei n, const GLuint * ids);
    // #311 (3.0+) Binds a transform feedback object to capture its output buffer state
    void glBindTransformFeedback(TransformFeedbackTarget target, GLuint id);
    // #312 (3.0+) Returns GL_TRUE if the name is a valid transform feedback object
    GLboolean glIsTransformFeedback(GLuint id);
    // #313 (3.0+) Starts capturing vertex shader outputs into transform feedback buffers
    void glBeginTransformFeedback(PrimitiveType primitiveMode);
    // #314 (3.0+) Ends the current transform feedback capture session
    void glEndTransformFeedback(void);
    // #315 (3.0+) Pauses an active transform feedback session (can be resumed)
    void glPauseTransformFeedback(void);
    // #316 (3.0+) Resumes a previously paused transform feedback session
    void glResumeTransformFeedback(void);
    // #317 (3.0+) Specifies which vertex shader outputs to capture before linking
    void glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const* varyings, TransformFeedbackBufferMode bufferMode);
    // #318 (3.0+) Returns name, type, and size of a transform feedback varying by index
    void glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, UniformType * type, GLchar * name);

    // Query Objects
    // #319 (3.0+) Generates one or more query object names
    void glGenQueries(GLsizei n, GLuint * ids);
    // #320 (3.0+) Deletes query objects
    void glDeleteQueries(GLsizei n, const GLuint * ids);
    // #321 (3.0+) Returns GL_TRUE if the name is a valid query object
    GLboolean glIsQuery(GLuint id);
    // #322 (3.0+) Begins recording a GPU query (occlusion, primitives written, etc.)
    void glBeginQuery(QueryTarget target, GLuint id);
    // #323 (3.0+) Ends a query; result becomes available asynchronously
    void glEndQuery(QueryTarget target);
    // #324 (3.0+) Returns info about a query target (active query name, counter bits)
    void glGetQueryiv(QueryTarget target, QueryParameter pname, GLint * params);
    // #325 (3.0+) Returns the result of a completed query as an unsigned integer
    void glGetQueryObjectuiv(GLuint id, QueryObjectParameter pname, GLuint * params);

    // Sync Objects
    // #326 (3.0+) Creates a sync object and inserts a fence into the GL command stream
    GLsync glFenceSync(SyncCondition condition, SyncFlag flags);
    // #327 (3.0+) Deletes a sync object
    void glDeleteSync(GLsync sync);
    // #328 (3.0+) Returns GL_TRUE if the object is a valid sync
    GLboolean glIsSync(GLsync sync);
    // #329 (3.0+) Blocks the CPU until a sync is signaled or the timeout expires
    SyncWaitResult glClientWaitSync(GLsync sync, SyncFlushMask flags, GLuint64 timeout);
    // #330 (3.0+) Blocks the GPU command processor until a sync is signaled (CPU not blocked)
    void glWaitSync(GLsync sync, SyncFlag flags, GLuint64 timeout);
    // #331 (3.0+) Returns the status or type of a sync object (signaled / unsignaled)
    void glGetSynciv(GLsync sync, SyncParameter pname, GLsizei count, GLsizei * length, GLint * values);

    // Compute Shaders
    // #332 (3.1+) Launches a compute shader with a 3D grid of work groups
    void glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
    // #333 (3.1+) Launches compute; work group dimensions read from GL_DISPATCH_INDIRECT_BUFFER
    void glDispatchComputeIndirect(GLintptr indirect);
    // #334 (3.1+) Inserts a memory barrier ensuring visibility of image/SSBO/atomic writes
    void glMemoryBarrier(MemoryBarrierMask barriers);
    // #335 (3.1+) Tile-friendly memory barrier guaranteeing visibility within the current region
    void glMemoryBarrierByRegion(MemoryBarrierMask barriers);

    // Program Pipelines
    // #336 (3.1+) Generates one or more program pipeline object names
    void glGenProgramPipelines(GLsizei n, GLuint * pipelines);
    // #337 (3.1+) Deletes program pipeline objects
    void glDeleteProgramPipelines(GLsizei n, const GLuint * pipelines);
    // #338 (3.1+) Binds a program pipeline for rendering
    void glBindProgramPipeline(GLuint pipeline);
    // #339 (3.1+) Returns GL_TRUE if the name is a valid program pipeline object
    GLboolean glIsProgramPipeline(GLuint pipeline);
    // #340 (3.1+) Installs shader stages from a separable program into a pipeline
    void glUseProgramStages(GLuint pipeline, ShaderStageMask stages, GLuint program);
    // #341 (3.1+) Sets the active program in a pipeline for direct uniform calls
    void glActiveShaderProgram(GLuint pipeline, GLuint program);
    // #342 (3.1+) Compiles, links, and creates a separable program in one step
    GLuint glCreateShaderProgramv(ShaderType type, GLsizei count, const GLchar *const* strings);
    // #343 (3.1+) Validates a pipeline can execute given current GL state
    void glValidateProgramPipeline(GLuint pipeline);
    // #344 (3.1+) Returns parameters of a program pipeline (installed stages, validate status)
    void glGetProgramPipelineiv(GLuint pipeline, ProgramPipelineParameter pname, GLint * params);
    // #345 (3.1+) Returns the info log for a pipeline (validation results, linker messages)
    void glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog);

    // Geometry / Tessellation
    // #346 (3.2+) Sets the number of vertices per patch for tessellation (GL_PATCH_VERTICES)
    void glPatchParameteri(TessellationParameter pname, GLint value);
    // #347 (3.2+) Provides a bounding box hint for tessellated/geometry-shader geometry
    void glPrimitiveBoundingBox(GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);

    // Debug
    // #348 (3.2+) Registers a callback invoked when the GL generates a debug message
    void glDebugMessageCallback(GLDEBUGPROC callback, const void * userParam);
    // #349 (3.2+) Filters which debug messages are generated by source, type, and severity
    void glDebugMessageControl(DebugSource source, DebugType type, DebugSeverity severity, GLsizei count, const GLuint * ids, GLboolean enabled);
    // #350 (3.2+) Inserts an application-generated message into the GL debug stream
    void glDebugMessageInsert(DebugSource source, DebugType type, GLuint id, DebugSeverity severity, GLsizei length, const GLchar * buf);
    // #351 (3.2+) Retrieves queued debug messages from the GL internal message log
    GLuint glGetDebugMessageLog(GLuint count, GLsizei bufSize, DebugSource * sources, DebugType * types, GLuint * ids, DebugSeverity * severities, GLsizei * lengths, GLchar * messageLog);
    // #352 (3.2+) Pushes a named debug group onto the stack (visible in GPU debuggers)
    void glPushDebugGroup(DebugSource source, GLuint id, GLsizei length, const GLchar * message);
    // #353 (3.2+) Pops the innermost debug group from the stack
    void glPopDebugGroup(void);
    // #354 (3.2+) Assigns a human-readable label to any GL object for GPU debugger tools
    void glObjectLabel(DebugObjectLabel identifier, GLuint name, GLsizei length, const GLchar * label);
    // #355 (3.2+) Assigns a label to a sync object (identified by pointer)
    void glObjectPtrLabel(const void * ptr, GLsizei length, const GLchar * label);
    // #356 (3.2+) Returns the label previously assigned to a GL object
    void glGetObjectLabel(DebugObjectLabel identifier, GLuint name, GLsizei bufSize, GLsizei * length, GLchar * label);
    // #357 (3.2+) Returns the label previously assigned to a sync object
    void glGetObjectPtrLabel(const void * ptr, GLsizei bufSize, GLsizei * length, GLchar * label);

    // Robustness
    // #358 (3.2+) Returns the graphics reset status for robustness/error recovery
    GraphicsResetStatus glGetGraphicsResetStatus(void);
}
