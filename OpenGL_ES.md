# OpenGL ES Function Reference

meta-gl targets **modern shader-based OpenGL ES**. This document covers all functions
from the ES 2.0 baseline through ES 3.2. It contains all 358 core function prototypes from `GLES3/gl32.h` for ES 2.0, 3.0, 3.1, and 3.2, excluding extensions and excluding OpenGL ES 1.x.

## What is and is not supported

| API | Support |
|-----|---------|
| OpenGL ES 1.0 / 1.1 | **Not supported** — fixed-function pipeline, no GLSL shaders |
| OpenGL ES 2.0 | **Supported** — programmable shader baseline (vertex + fragment) |
| OpenGL ES 3.0 | **Supported** — VAOs, UBOs, transform feedback, sync objects, MSAA, etc. |
| OpenGL ES 3.1 | **Supported** — compute shaders, SSBOs, program pipelines, indirect draw |
| OpenGL ES 3.2 | **Supported** — geometry/tessellation shaders, debug API, buffer textures |

## Architecture

OpenGL ES 2.0 introduced programmable shaders and replaced the ES 1.x fixed-function
pipeline entirely. ES 3.0, 3.1, and 3.2 are **incremental additions** on top of
ES 2.0 — every ES 3.x context includes all ES 2.0 functions.

meta-gl intentionally includes ES 2.0 functions because they form the mandatory
baseline of all modern shader-based OpenGL ES. Fixed-function ES 1.x APIs
(`glMatrixMode`, `glLoadIdentity`, `glLight*`, `glMaterial*`, `glVertexPointer`,
`glColorPointer`, etc.) are **not included** and never will be.

## Version key

| Version | Meaning |
|---------|---------|
| `2.0+`  | ES 2.0 baseline — present in all ES 2.0, 3.0, 3.1, and 3.2 contexts |
| `3.0+`  | Added in ES 3.0 — present in ES 3.0, 3.1, and 3.2 contexts |
| `3.1+`  | Added in ES 3.1 — present in ES 3.1 and 3.2 contexts |
| `3.2+`  | Added in ES 3.2 — present in ES 3.2 contexts only |

---

| # | Group | Function | Version | Description |
|---|-------|----------|---------|-------------|
| 1 | State Management | `void glEnable(GLenum cap)` | 2.0+ | Enables a server-side GL capability (e.g. depth test, blending, culling) |
| 2 | State Management | `void glDisable(GLenum cap)` | 2.0+ | Disables a server-side GL capability |
| 3 | State Management | `void glEnablei(GLenum target, GLuint index)` | 3.2+ | Enables a capability for a specific indexed target (per-draw-buffer) |
| 4 | State Management | `void glDisablei(GLenum target, GLuint index)` | 3.2+ | Disables a capability for a specific indexed target |
| 5 | State Management | `GLboolean glIsEnabled(GLenum cap)` | 2.0+ | Returns whether a capability is currently enabled |
| 6 | State Management | `GLboolean glIsEnabledi(GLenum target, GLuint index)` | 3.2+ | Returns whether an indexed capability is enabled |
| 7 | State Management | `void glBlendFunc(GLenum sfactor, GLenum dfactor)` | 2.0+ | Sets blend source and destination factors for all draw buffers |
| 8 | State Management | `void glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)` | 2.0+ | Sets separate blend factors for RGB and alpha for all draw buffers |
| 9 | State Management | `void glBlendFunci(GLuint buf, GLenum src, GLenum dst)` | 3.2+ | Sets blend factors for a specific indexed draw buffer |
| 10 | State Management | `void glBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)` | 3.2+ | Sets separate RGB/alpha blend factors for a specific draw buffer |
| 11 | State Management | `void glBlendEquation(GLenum mode)` | 2.0+ | Sets the blend equation (e.g. GL_FUNC_ADD) for all draw buffers |
| 12 | State Management | `void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)` | 2.0+ | Sets separate blend equations for RGB and alpha for all draw buffers |
| 13 | State Management | `void glBlendEquationi(GLuint buf, GLenum mode)` | 3.2+ | Sets the blend equation for a specific indexed draw buffer |
| 14 | State Management | `void glBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha)` | 3.2+ | Sets separate blend equations for a specific draw buffer |
| 15 | State Management | `void glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)` | 2.0+ | Sets the constant blend color used in blend factor expressions |
| 16 | State Management | `void glBlendBarrier(void)` | 3.2+ | Ensures prior fragment writes are visible before next blending operation |
| 17 | State Management | `void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)` | 2.0+ | Enables/disables writing of R, G, B, A components for all draw buffers |
| 18 | State Management | `void glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)` | 3.2+ | Enables/disables writing of color components for a specific draw buffer |
| 19 | State Management | `void glDepthFunc(GLenum func)` | 2.0+ | Sets the depth comparison function (e.g. GL_LESS, GL_LEQUAL) |
| 20 | State Management | `void glDepthMask(GLboolean flag)` | 2.0+ | Enables or disables writing to the depth buffer |
| 21 | State Management | `void glDepthRangef(GLfloat n, GLfloat f)` | 2.0+ | Maps NDC depth to window-space depth via near/far plane values |
| 22 | State Management | `void glStencilFunc(GLenum func, GLint ref, GLuint mask)` | 2.0+ | Sets the stencil test function for both front and back faces |
| 23 | State Management | `void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)` | 2.0+ | Sets the stencil test function separately for front and back faces |
| 24 | State Management | `void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)` | 2.0+ | Sets stencil operations (sfail, dpfail, dppass) for both faces |
| 25 | State Management | `void glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)` | 2.0+ | Sets stencil operations separately for front and back faces |
| 26 | State Management | `void glStencilMask(GLuint mask)` | 2.0+ | Sets the stencil write mask for both faces |
| 27 | State Management | `void glStencilMaskSeparate(GLenum face, GLuint mask)` | 2.0+ | Sets the stencil write mask separately for front and back faces |
| 28 | State Management | `void glScissor(GLint x, GLint y, GLsizei width, GLsizei height)` | 2.0+ | Defines a rectangular region outside which all fragments are discarded |
| 29 | State Management | `void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)` | 2.0+ | Sets the affine mapping from NDC to window-space coordinates |
| 30 | State Management | `void glCullFace(GLenum mode)` | 2.0+ | Specifies whether front, back, or both polygon faces are culled |
| 31 | State Management | `void glFrontFace(GLenum mode)` | 2.0+ | Sets the winding order (CW or CCW) that defines front-facing polygons |
| 32 | State Management | `void glLineWidth(GLfloat width)` | 2.0+ | Sets the width of rasterized lines (only 1.0 is guaranteed portable) |
| 33 | State Management | `void glPolygonOffset(GLfloat factor, GLfloat units)` | 2.0+ | Adds a scaled depth bias to polygon fragments (resolves z-fighting) |
| 34 | State Management | `void glSampleCoverage(GLfloat value, GLboolean invert)` | 2.0+ | Sets a sample coverage mask used in multisampled rendering |
| 35 | State Management | `void glSampleMaski(GLuint maskNumber, GLbitfield mask)` | 3.1+ | Sets a bitmask qualifying which samples are written during MSAA |
| 36 | State Management | `void glMinSampleShading(GLfloat value)` | 3.2+ | Sets the minimum fraction of samples for which per-sample shading runs |
| 37 | State Management | `void glHint(GLenum target, GLenum mode)` | 2.0+ | Provides a quality/performance trade-off hint for certain operations |
| 38 | State Management | `void glPixelStorei(GLenum pname, GLint param)` | 2.0+ | Sets pixel pack/unpack alignment and stride for texture transfers |
| 39 | State Management | `void glFinish(void)` | 2.0+ | Blocks the CPU until all pending GL commands have finished on the GPU |
| 40 | State Management | `void glFlush(void)` | 2.0+ | Submits all pending GL commands to the GPU without waiting for completion |
| 41 | State Management | `GLenum glGetError(void)` | 2.0+ | Returns the most recent GL error flag and clears it |
| 42 | State Management | `void glGetBooleanv(GLenum pname, GLboolean *data)` | 2.0+ | Queries a named GL state parameter as a boolean value |
| 43 | State Management | `void glGetIntegerv(GLenum pname, GLint *data)` | 2.0+ | Queries a named GL state parameter as a 32-bit integer |
| 44 | State Management | `void glGetFloatv(GLenum pname, GLfloat *data)` | 2.0+ | Queries a named GL state parameter as a float |
| 45 | State Management | `void glGetInteger64v(GLenum pname, GLint64 *data)` | 3.0+ | Queries a named GL state parameter as a 64-bit integer |
| 46 | State Management | `void glGetIntegeri_v(GLenum target, GLuint index, GLint *data)` | 3.0+ | Queries an indexed GL state parameter as a 32-bit integer |
| 47 | State Management | `void glGetInteger64i_v(GLenum target, GLuint index, GLint64 *data)` | 3.0+ | Queries an indexed GL state parameter as a 64-bit integer |
| 48 | State Management | `void glGetBooleani_v(GLenum target, GLuint index, GLboolean *data)` | 3.1+ | Queries an indexed GL state parameter as a boolean |
| 49 | State Management | `const GLubyte* glGetString(GLenum name)` | 2.0+ | Returns a global implementation string (renderer, vendor, version, etc.) |
| 50 | State Management | `const GLubyte* glGetStringi(GLenum name, GLuint index)` | 3.0+ | Returns an indexed string (e.g. the nth supported extension) |
| 51 | State Management | `void glGetPointerv(GLenum pname, void **params)` | 3.2+ | Returns pointer-valued GL state such as debug callback pointers |
| 52 | Buffer Objects | `void glGenBuffers(GLsizei n, GLuint *buffers)` | 2.0+ | Generates one or more buffer object names |
| 53 | Buffer Objects | `void glDeleteBuffers(GLsizei n, const GLuint *buffers)` | 2.0+ | Deletes buffer objects and frees their GPU memory |
| 54 | Buffer Objects | `void glBindBuffer(GLenum target, GLuint buffer)` | 2.0+ | Binds a buffer to a target (ARRAY_BUFFER, ELEMENT_ARRAY_BUFFER, etc.) |
| 55 | Buffer Objects | `void glBindBufferBase(GLenum target, GLuint index, GLuint buffer)` | 3.0+ | Binds a buffer to an indexed binding point (e.g. UBO slot N) |
| 56 | Buffer Objects | `void glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)` | 3.0+ | Binds a sub-range of a buffer to an indexed binding point |
| 57 | Buffer Objects | `void glBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage)` | 2.0+ | Allocates and optionally initializes a buffer's GPU data store |
| 58 | Buffer Objects | `void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void *data)` | 2.0+ | Updates a sub-range of an existing buffer without reallocating |
| 59 | Buffer Objects | `void glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)` | 3.0+ | Copies a region from one buffer to another entirely on the GPU |
| 60 | Buffer Objects | `void* glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)` | 3.0+ | Maps a buffer sub-range into CPU address space for read/write |
| 61 | Buffer Objects | `void glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length)` | 3.0+ | Flushes explicitly mapped writes when GL_MAP_FLUSH_EXPLICIT_BIT is set |
| 62 | Buffer Objects | `GLboolean glUnmapBuffer(GLenum target)` | 3.0+ | Releases a buffer mapping; returns GL_FALSE if data was corrupted |
| 63 | Buffer Objects | `GLboolean glIsBuffer(GLuint buffer)` | 2.0+ | Returns GL_TRUE if the name is a valid buffer object |
| 64 | Buffer Objects | `void glGetBufferParameteriv(GLenum target, GLenum pname, GLint *params)` | 2.0+ | Queries buffer parameters (size, usage, map status) as 32-bit integer |
| 65 | Buffer Objects | `void glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64 *params)` | 3.0+ | Queries buffer parameters (e.g. size on large buffers) as 64-bit integer |
| 66 | Buffer Objects | `void glGetBufferPointerv(GLenum target, GLenum pname, void **params)` | 3.0+ | Returns the pointer to the currently mapped buffer data store |
| 67 | Vertex Arrays | `void glGenVertexArrays(GLsizei n, GLuint *arrays)` | 3.0+ | Generates one or more Vertex Array Object (VAO) names |
| 68 | Vertex Arrays | `void glDeleteVertexArrays(GLsizei n, const GLuint *arrays)` | 3.0+ | Deletes VAOs |
| 69 | Vertex Arrays | `void glBindVertexArray(GLuint array)` | 3.0+ | Binds a VAO; all subsequent attribute state is recorded into it |
| 70 | Vertex Arrays | `GLboolean glIsVertexArray(GLuint array)` | 3.0+ | Returns GL_TRUE if the name is a valid VAO |
| 71 | Vertex Arrays | `void glEnableVertexAttribArray(GLuint index)` | 2.0+ | Enables a generic vertex attribute array at a given index |
| 72 | Vertex Arrays | `void glDisableVertexAttribArray(GLuint index)` | 2.0+ | Disables a generic vertex attribute array; attribute uses constant value |
| 73 | Vertex Arrays | `void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)` | 2.0+ | Defines layout/source of a float or normalized-integer vertex attribute |
| 74 | Vertex Arrays | `void glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer)` | 3.0+ | Defines layout/source of an integer vertex attribute (no normalization) |
| 75 | Vertex Arrays | `void glVertexAttribDivisor(GLuint index, GLuint divisor)` | 3.0+ | Sets the instancing divisor for an attribute (0=per-vertex, N=per-N-instances) |
| 76 | Vertex Arrays | `void glVertexAttrib1f(GLuint index, GLfloat x)` | 2.0+ | Sets a constant float scalar value for a vertex attribute |
| 77 | Vertex Arrays | `void glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y)` | 2.0+ | Sets a constant vec2 float value for a vertex attribute |
| 78 | Vertex Arrays | `void glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)` | 2.0+ | Sets a constant vec3 float value for a vertex attribute |
| 79 | Vertex Arrays | `void glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)` | 2.0+ | Sets a constant vec4 float value for a vertex attribute |
| 80 | Vertex Arrays | `void glVertexAttrib1fv(GLuint index, const GLfloat *v)` | 2.0+ | Sets a constant float scalar for a vertex attribute from a pointer |
| 81 | Vertex Arrays | `void glVertexAttrib2fv(GLuint index, const GLfloat *v)` | 2.0+ | Sets a constant vec2 float value for a vertex attribute from a pointer |
| 82 | Vertex Arrays | `void glVertexAttrib3fv(GLuint index, const GLfloat *v)` | 2.0+ | Sets a constant vec3 float value for a vertex attribute from a pointer |
| 83 | Vertex Arrays | `void glVertexAttrib4fv(GLuint index, const GLfloat *v)` | 2.0+ | Sets a constant vec4 float value for a vertex attribute from a pointer |
| 84 | Vertex Arrays | `void glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w)` | 3.0+ | Sets a constant ivec4 signed integer value for a vertex attribute |
| 85 | Vertex Arrays | `void glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)` | 3.0+ | Sets a constant uvec4 unsigned integer value for a vertex attribute |
| 86 | Vertex Arrays | `void glVertexAttribI4iv(GLuint index, const GLint *v)` | 3.0+ | Sets a constant ivec4 value for a vertex attribute from a pointer |
| 87 | Vertex Arrays | `void glVertexAttribI4uiv(GLuint index, const GLuint *v)` | 3.0+ | Sets a constant uvec4 value for a vertex attribute from a pointer |
| 88 | Vertex Arrays | `void glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat *params)` | 2.0+ | Queries float state of a vertex attribute (type, size, stride, etc.) |
| 89 | Vertex Arrays | `void glGetVertexAttribiv(GLuint index, GLenum pname, GLint *params)` | 2.0+ | Queries integer state of a vertex attribute |
| 90 | Vertex Arrays | `void glGetVertexAttribIiv(GLuint index, GLenum pname, GLint *params)` | 3.0+ | Queries integer state of an integer-type vertex attribute |
| 91 | Vertex Arrays | `void glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint *params)` | 3.0+ | Queries unsigned integer state of an unsigned-integer vertex attribute |
| 92 | Vertex Arrays | `void glGetVertexAttribPointerv(GLuint index, GLenum pname, void **pointer)` | 2.0+ | Returns the offset/pointer stored for a vertex attribute |
| 93 | Vertex Arrays | `void glVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)` | 3.1+ | Specifies float attribute format independently from buffer binding |
| 94 | Vertex Arrays | `void glVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)` | 3.1+ | Specifies integer attribute format independently from buffer binding |
| 95 | Vertex Arrays | `void glVertexAttribBinding(GLuint attribindex, GLuint bindingindex)` | 3.1+ | Associates a vertex attribute index with a vertex buffer binding point |
| 96 | Vertex Arrays | `void glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)` | 3.1+ | Binds a buffer to a vertex buffer binding point with offset and stride |
| 97 | Vertex Arrays | `void glVertexBindingDivisor(GLuint bindingindex, GLuint divisor)` | 3.1+ | Sets the instancing divisor for a vertex buffer binding point |
| 98 | Drawing | `void glDrawArrays(GLenum mode, GLint first, GLsizei count)` | 2.0+ | Renders primitives from vertex arrays starting at a given offset |
| 99 | Drawing | `void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount)` | 3.0+ | Renders multiple instances of geometry using vertex arrays |
| 100 | Drawing | `void glDrawArraysIndirect(GLenum mode, const void *indirect)` | 3.1+ | Renders instances; draw parameters read from GL_DRAW_INDIRECT_BUFFER |
| 101 | Drawing | `void glDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices)` | 2.0+ | Renders indexed primitives from vertex arrays and an index buffer |
| 102 | Drawing | `void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount)` | 3.0+ | Renders multiple instances using indexed drawing |
| 103 | Drawing | `void glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices)` | 3.0+ | Indexed draw with index range hints for driver prefetch optimization |
| 104 | Drawing | `void glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex)` | 3.2+ | Indexed draw with a constant base vertex offset added to each index |
| 105 | Drawing | `void glDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex)` | 3.2+ | Instanced indexed draw with a base vertex offset |
| 106 | Drawing | `void glDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex)` | 3.2+ | Range-indexed draw with a base vertex offset |
| 107 | Drawing | `void glDrawElementsIndirect(GLenum mode, GLenum type, const void *indirect)` | 3.1+ | Indexed instanced draw; parameters read from GL_DRAW_INDIRECT_BUFFER |
| 108 | Drawing | `void glDrawBuffers(GLsizei n, const GLenum *bufs)` | 3.0+ | Specifies the list of color buffers that fragment outputs are written to |
| 109 | Drawing | `void glReadBuffer(GLenum src)` | 3.0+ | Selects a color buffer as the source for glReadPixels and copy operations |
| 110 | Drawing | `void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels)` | 2.0+ | Reads a rectangular block of pixels from the framebuffer into CPU memory |
| 111 | Drawing | `void glReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data)` | 3.2+ | Reads pixels with an explicit destination buffer size for robustness |
| 112 | Drawing | `void glClear(GLbitfield mask)` | 2.0+ | Clears color, depth, and/or stencil buffers to their clear values |
| 113 | Drawing | `void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)` | 2.0+ | Sets the RGBA value used when clearing the color buffer |
| 114 | Drawing | `void glClearDepthf(GLfloat d)` | 2.0+ | Sets the float depth value (0.0–1.0) used when clearing the depth buffer |
| 115 | Drawing | `void glClearStencil(GLint s)` | 2.0+ | Sets the integer value used when clearing the stencil buffer |
| 116 | Drawing | `void glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat *value)` | 3.0+ | Clears a float color or depth buffer attachment to a given value |
| 117 | Drawing | `void glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint *value)` | 3.0+ | Clears an integer color or stencil buffer attachment to a given value |
| 118 | Drawing | `void glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint *value)` | 3.0+ | Clears an unsigned integer color buffer attachment to a given value |
| 119 | Drawing | `void glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)` | 3.0+ | Clears depth and stencil buffer attachments together in one call |
| 120 | Shaders | `GLuint glCreateShader(GLenum type)` | 2.0+ | Creates a shader object of the given type and returns its handle |
| 121 | Shaders | `void glDeleteShader(GLuint shader)` | 2.0+ | Marks a shader for deletion (deferred until detached from all programs) |
| 122 | Shaders | `void glShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length)` | 2.0+ | Loads GLSL source strings into a shader object |
| 123 | Shaders | `void glCompileShader(GLuint shader)` | 2.0+ | Compiles the GLSL source previously loaded into a shader object |
| 124 | Shaders | `void glShaderBinary(GLsizei count, const GLuint *shaders, GLenum binaryFormat, const void *binary, GLsizei length)` | 2.0+ | Loads pre-compiled binary shader code into one or more shader objects |
| 125 | Shaders | `void glReleaseShaderCompiler(void)` | 2.0+ | Hints that the GLSL compiler resources may be freed |
| 126 | Shaders | `void glGetShaderiv(GLuint shader, GLenum pname, GLint *params)` | 2.0+ | Queries shader parameters (compile status, type, source length, etc.) |
| 127 | Shaders | `void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog)` | 2.0+ | Returns the compiler info log for a shader (errors and warnings) |
| 128 | Shaders | `void glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source)` | 2.0+ | Returns the GLSL source code stored in a shader object |
| 129 | Shaders | `void glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision)` | 2.0+ | Returns the precision range for lowp/mediump/highp in vertex/fragment shaders |
| 130 | Shaders | `GLboolean glIsShader(GLuint shader)` | 2.0+ | Returns GL_TRUE if the name is a valid shader object |
| 131 | Shaders | `GLuint glCreateProgram(void)` | 2.0+ | Creates a program object and returns its handle |
| 132 | Shaders | `void glDeleteProgram(GLuint program)` | 2.0+ | Deletes a program object (deferred until no longer in use) |
| 133 | Shaders | `void glAttachShader(GLuint program, GLuint shader)` | 2.0+ | Attaches a compiled shader to a program for the next link operation |
| 134 | Shaders | `void glDetachShader(GLuint program, GLuint shader)` | 2.0+ | Detaches a shader from a program |
| 135 | Shaders | `void glLinkProgram(GLuint program)` | 2.0+ | Links all attached shaders into an executable GPU program |
| 136 | Shaders | `void glUseProgram(GLuint program)` | 2.0+ | Installs a linked program as part of the current rendering state |
| 137 | Shaders | `void glValidateProgram(GLuint program)` | 2.0+ | Validates whether a program can execute given the current GL state |
| 138 | Shaders | `void glGetProgramiv(GLuint program, GLenum pname, GLint *params)` | 2.0+ | Queries program parameters (link status, active uniforms, etc.) |
| 139 | Shaders | `void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog)` | 2.0+ | Returns the linker info log for a program (errors and warnings) |
| 140 | Shaders | `GLboolean glIsProgram(GLuint program)` | 2.0+ | Returns GL_TRUE if the name is a valid program object |
| 141 | Shaders | `void glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders)` | 2.0+ | Returns the shader objects currently attached to a program |
| 142 | Shaders | `void glBindAttribLocation(GLuint program, GLuint index, const GLchar *name)` | 2.0+ | Associates a vertex shader input variable with an attribute index before link |
| 143 | Shaders | `GLint glGetAttribLocation(GLuint program, const GLchar *name)` | 2.0+ | Returns the attribute index of a named vertex shader input in a linked program |
| 144 | Shaders | `void glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name)` | 2.0+ | Returns name, type, and size of an active vertex attribute variable |
| 145 | Shaders | `void glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary)` | 3.0+ | Returns the binary representation of a linked program for caching |
| 146 | Shaders | `void glProgramBinary(GLuint program, GLenum binaryFormat, const void *binary, GLsizei length)` | 3.0+ | Loads a cached binary into a program, bypassing compilation and linking |
| 147 | Shaders | `void glProgramParameteri(GLuint program, GLenum pname, GLint value)` | 3.0+ | Sets program parameters (binary retrievable hint, separable flag) |
| 148 | Shaders | `GLint glGetFragDataLocation(GLuint program, const GLchar *name)` | 3.0+ | Returns the fragment output location for a named output variable |
| 149 | Shaders | `void glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint *params)` | 3.1+ | Queries properties of a program interface (e.g. number of active uniforms) |
| 150 | Shaders | `GLuint glGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar *name)` | 3.1+ | Returns the index of a named resource within a program interface |
| 151 | Shaders | `void glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name)` | 3.1+ | Returns the name of a resource at a given index in a program interface |
| 152 | Shaders | `void glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei count, GLsizei *length, GLint *params)` | 3.1+ | Returns multiple properties of a program interface resource in one call |
| 153 | Shaders | `GLint glGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar *name)` | 3.1+ | Returns the location of a named resource within a program interface |
| 154 | Uniforms | `GLint glGetUniformLocation(GLuint program, const GLchar *name)` | 2.0+ | Returns the integer location of a named uniform in a linked program |
| 155 | Uniforms | `void glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name)` | 2.0+ | Returns the name, type, and size of an active uniform variable |
| 156 | Uniforms | `void glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params)` | 3.0+ | Queries parameters for multiple uniforms by index in one call |
| 157 | Uniforms | `void glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices)` | 3.0+ | Returns the indices of multiple named uniform variables |
| 158 | Uniforms | `GLuint glGetUniformBlockIndex(GLuint program, const GLchar *uniformBlockName)` | 3.0+ | Returns the index of a named uniform block in a linked program |
| 159 | Uniforms | `void glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params)` | 3.0+ | Queries parameters of a uniform block (size, binding, member count) |
| 160 | Uniforms | `void glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName)` | 3.0+ | Returns the name string of a uniform block at a given index |
| 161 | Uniforms | `void glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)` | 3.0+ | Assigns a uniform block to a specific uniform buffer binding point |
| 162 | Uniforms | `void glUniform1f(GLint location, GLfloat v0)` | 2.0+ | Sets a float scalar uniform in the current program |
| 163 | Uniforms | `void glUniform2f(GLint location, GLfloat v0, GLfloat v1)` | 2.0+ | Sets a vec2 float uniform in the current program |
| 164 | Uniforms | `void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)` | 2.0+ | Sets a vec3 float uniform in the current program |
| 165 | Uniforms | `void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)` | 2.0+ | Sets a vec4 float uniform in the current program |
| 166 | Uniforms | `void glUniform1fv(GLint location, GLsizei count, const GLfloat *value)` | 2.0+ | Sets an array of float scalar uniforms in the current program |
| 167 | Uniforms | `void glUniform2fv(GLint location, GLsizei count, const GLfloat *value)` | 2.0+ | Sets an array of vec2 uniforms in the current program |
| 168 | Uniforms | `void glUniform3fv(GLint location, GLsizei count, const GLfloat *value)` | 2.0+ | Sets an array of vec3 uniforms in the current program |
| 169 | Uniforms | `void glUniform4fv(GLint location, GLsizei count, const GLfloat *value)` | 2.0+ | Sets an array of vec4 uniforms in the current program |
| 170 | Uniforms | `void glUniform1i(GLint location, GLint v0)` | 2.0+ | Sets an int scalar uniform; also used to assign sampler texture units |
| 171 | Uniforms | `void glUniform2i(GLint location, GLint v0, GLint v1)` | 2.0+ | Sets an ivec2 uniform in the current program |
| 172 | Uniforms | `void glUniform3i(GLint location, GLint v0, GLint v1, GLint v2)` | 2.0+ | Sets an ivec3 uniform in the current program |
| 173 | Uniforms | `void glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)` | 2.0+ | Sets an ivec4 uniform in the current program |
| 174 | Uniforms | `void glUniform1iv(GLint location, GLsizei count, const GLint *value)` | 2.0+ | Sets an array of int scalar uniforms in the current program |
| 175 | Uniforms | `void glUniform2iv(GLint location, GLsizei count, const GLint *value)` | 2.0+ | Sets an array of ivec2 uniforms in the current program |
| 176 | Uniforms | `void glUniform3iv(GLint location, GLsizei count, const GLint *value)` | 2.0+ | Sets an array of ivec3 uniforms in the current program |
| 177 | Uniforms | `void glUniform4iv(GLint location, GLsizei count, const GLint *value)` | 2.0+ | Sets an array of ivec4 uniforms in the current program |
| 178 | Uniforms | `void glUniform1ui(GLint location, GLuint v0)` | 3.0+ | Sets an unsigned int scalar uniform in the current program |
| 179 | Uniforms | `void glUniform2ui(GLint location, GLuint v0, GLuint v1)` | 3.0+ | Sets a uvec2 uniform in the current program |
| 180 | Uniforms | `void glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2)` | 3.0+ | Sets a uvec3 uniform in the current program |
| 181 | Uniforms | `void glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)` | 3.0+ | Sets a uvec4 uniform in the current program |
| 182 | Uniforms | `void glUniform1uiv(GLint location, GLsizei count, const GLuint *value)` | 3.0+ | Sets an array of unsigned int scalar uniforms |
| 183 | Uniforms | `void glUniform2uiv(GLint location, GLsizei count, const GLuint *value)` | 3.0+ | Sets an array of uvec2 uniforms |
| 184 | Uniforms | `void glUniform3uiv(GLint location, GLsizei count, const GLuint *value)` | 3.0+ | Sets an array of uvec3 uniforms |
| 185 | Uniforms | `void glUniform4uiv(GLint location, GLsizei count, const GLuint *value)` | 3.0+ | Sets an array of uvec4 uniforms |
| 186 | Uniforms | `void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)` | 2.0+ | Sets a mat2 uniform (or array of mat2) in the current program |
| 187 | Uniforms | `void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)` | 2.0+ | Sets a mat3 uniform (or array of mat3) in the current program |
| 188 | Uniforms | `void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)` | 2.0+ | Sets a mat4 uniform (or array of mat4) in the current program |
| 189 | Uniforms | `void glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)` | 3.0+ | Sets a mat2x3 uniform (2 columns, 3 rows); non-square matrices not in ES 2.0 |
| 190 | Uniforms | `void glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)` | 3.0+ | Sets a mat2x4 uniform in the current program |
| 191 | Uniforms | `void glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)` | 3.0+ | Sets a mat3x2 uniform in the current program |
| 192 | Uniforms | `void glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)` | 3.0+ | Sets a mat3x4 uniform in the current program |
| 193 | Uniforms | `void glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)` | 3.0+ | Sets a mat4x2 uniform in the current program |
| 194 | Uniforms | `void glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)` | 3.0+ | Sets a mat4x3 uniform in the current program |
| 195 | Uniforms | `void glGetUniformfv(GLuint program, GLint location, GLfloat *params)` | 2.0+ | Returns the current value of a float uniform from a linked program |
| 196 | Uniforms | `void glGetUniformiv(GLuint program, GLint location, GLint *params)` | 2.0+ | Returns the current value of an integer uniform from a linked program |
| 197 | Uniforms | `void glGetUniformuiv(GLuint program, GLint location, GLuint *params)` | 3.0+ | Returns the current value of an unsigned integer uniform |
| 198 | Uniforms | `void glGetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat *params)` | 3.2+ | Returns float uniform values with an explicit destination buffer size for robustness |
| 199 | Uniforms | `void glGetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint *params)` | 3.2+ | Returns integer uniform values with an explicit destination buffer size for robustness |
| 200 | Uniforms | `void glGetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint *params)` | 3.2+ | Returns unsigned integer uniform values with an explicit destination buffer size for robustness |
| 201 | Uniforms | `void glProgramUniform1f(GLuint program, GLint location, GLfloat v0)` | 3.1+ | Sets a float scalar uniform in a specific program without binding it |
| 202 | Uniforms | `void glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1)` | 3.1+ | Sets a vec2 float uniform in a specific program without binding it |
| 203 | Uniforms | `void glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)` | 3.1+ | Sets a vec3 float uniform in a specific program without binding it |
| 204 | Uniforms | `void glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)` | 3.1+ | Sets a vec4 float uniform in a specific program without binding it |
| 205 | Uniforms | `void glProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat *value)` | 3.1+ | Sets an array of float scalar uniforms in a specific program |
| 206 | Uniforms | `void glProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat *value)` | 3.1+ | Sets an array of vec2 uniforms in a specific program |
| 207 | Uniforms | `void glProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat *value)` | 3.1+ | Sets an array of vec3 uniforms in a specific program |
| 208 | Uniforms | `void glProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat *value)` | 3.1+ | Sets an array of vec4 uniforms in a specific program |
| 209 | Uniforms | `void glProgramUniform1i(GLuint program, GLint location, GLint v0)` | 3.1+ | Sets an int scalar uniform in a specific program |
| 210 | Uniforms | `void glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1)` | 3.1+ | Sets an ivec2 uniform in a specific program |
| 211 | Uniforms | `void glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2)` | 3.1+ | Sets an ivec3 uniform in a specific program |
| 212 | Uniforms | `void glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3)` | 3.1+ | Sets an ivec4 uniform in a specific program |
| 213 | Uniforms | `void glProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint *value)` | 3.1+ | Sets an array of int scalars in a specific program |
| 214 | Uniforms | `void glProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint *value)` | 3.1+ | Sets an array of ivec2 uniforms in a specific program |
| 215 | Uniforms | `void glProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint *value)` | 3.1+ | Sets an array of ivec3 uniforms in a specific program |
| 216 | Uniforms | `void glProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint *value)` | 3.1+ | Sets an array of ivec4 uniforms in a specific program |
| 217 | Uniforms | `void glProgramUniform1ui(GLuint program, GLint location, GLuint v0)` | 3.1+ | Sets an unsigned int scalar uniform in a specific program |
| 218 | Uniforms | `void glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1)` | 3.1+ | Sets a uvec2 uniform in a specific program |
| 219 | Uniforms | `void glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2)` | 3.1+ | Sets a uvec3 uniform in a specific program |
| 220 | Uniforms | `void glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)` | 3.1+ | Sets a uvec4 uniform in a specific program |
| 221 | Uniforms | `void glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint *value)` | 3.1+ | Sets an array of unsigned int scalars in a specific program |
| 222 | Uniforms | `void glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint *value)` | 3.1+ | Sets an array of uvec2 uniforms in a specific program |
| 223 | Uniforms | `void glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint *value)` | 3.1+ | Sets an array of uvec3 uniforms in a specific program |
| 224 | Uniforms | `void glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint *value)` | 3.1+ | Sets an array of uvec4 uniforms in a specific program |
| 225 | Uniforms | `void glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)` | 3.1+ | Sets a mat2 uniform in a specific program |
| 226 | Uniforms | `void glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)` | 3.1+ | Sets a mat3 uniform in a specific program |
| 227 | Uniforms | `void glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)` | 3.1+ | Sets a mat4 uniform in a specific program |
| 228 | Uniforms | `void glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)` | 3.1+ | Sets a mat2x3 uniform in a specific program |
| 229 | Uniforms | `void glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)` | 3.1+ | Sets a mat2x4 uniform in a specific program |
| 230 | Uniforms | `void glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)` | 3.1+ | Sets a mat3x2 uniform in a specific program |
| 231 | Uniforms | `void glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)` | 3.1+ | Sets a mat3x4 uniform in a specific program |
| 232 | Uniforms | `void glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)` | 3.1+ | Sets a mat4x2 uniform in a specific program |
| 233 | Uniforms | `void glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)` | 3.1+ | Sets a mat4x3 uniform in a specific program |
| 234 | Textures | `void glGenTextures(GLsizei n, GLuint *textures)` | 2.0+ | Generates one or more texture object names |
| 235 | Textures | `void glDeleteTextures(GLsizei n, const GLuint *textures)` | 2.0+ | Deletes texture objects and frees their GPU memory |
| 236 | Textures | `void glBindTexture(GLenum target, GLuint texture)` | 2.0+ | Binds a texture to a target in the active texture unit |
| 237 | Textures | `void glActiveTexture(GLenum texture)` | 2.0+ | Selects the active texture unit for subsequent texture operations |
| 238 | Textures | `GLboolean glIsTexture(GLuint texture)` | 2.0+ | Returns GL_TRUE if the name is a valid texture object |
| 239 | Textures | `void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels)` | 2.0+ | Specifies a 2D texture image and allocates GPU storage |
| 240 | Textures | `void glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels)` | 3.0+ | Specifies a 3D or 2D-array texture image and allocates GPU storage |
| 241 | Textures | `void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels)` | 2.0+ | Updates a sub-region of an existing 2D texture image |
| 242 | Textures | `void glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels)` | 3.0+ | Updates a sub-region of an existing 3D or 2D-array texture |
| 243 | Textures | `void glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)` | 3.0+ | Allocates immutable storage for all mip levels of a 2D texture |
| 244 | Textures | `void glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)` | 3.0+ | Allocates immutable storage for all mip levels of a 3D or array texture |
| 245 | Textures | `void glTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)` | 3.1+ | Allocates immutable multisample storage for a 2D MSAA texture |
| 246 | Textures | `void glTexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)` | 3.2+ | Allocates immutable multisample storage for a 2D MSAA array texture |
| 247 | Textures | `void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data)` | 2.0+ | Loads compressed image data (ETC2, ASTC, etc.) into a 2D texture |
| 248 | Textures | `void glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data)` | 3.0+ | Loads compressed image data into a 3D or 2D-array texture |
| 249 | Textures | `void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data)` | 2.0+ | Updates a sub-region of an existing compressed 2D texture |
| 250 | Textures | `void glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data)` | 3.0+ | Updates a sub-region of an existing compressed 3D or array texture |
| 251 | Textures | `void glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)` | 2.0+ | Copies pixels from the read framebuffer into a 2D texture image |
| 252 | Textures | `void glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)` | 2.0+ | Copies a framebuffer region into a sub-region of a 2D texture |
| 253 | Textures | `void glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)` | 3.0+ | Copies a framebuffer region into a slice of a 3D or array texture |
| 254 | Textures | `void glCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth)` | 3.2+ | Copies a region between texture or renderbuffer image objects without format conversion |
| 255 | Textures | `void glGenerateMipmap(GLenum target)` | 2.0+ | Auto-generates all mipmap levels below the base level by downsampling |
| 256 | Textures | `void glTexParameterf(GLenum target, GLenum pname, GLfloat param)` | 2.0+ | Sets a float texture sampling parameter (filter, LOD, wrap mode) |
| 257 | Textures | `void glTexParameteri(GLenum target, GLenum pname, GLint param)` | 2.0+ | Sets an integer texture sampling parameter |
| 258 | Textures | `void glTexParameterfv(GLenum target, GLenum pname, const GLfloat *params)` | 2.0+ | Sets multiple float texture parameters from a pointer |
| 259 | Textures | `void glTexParameteriv(GLenum target, GLenum pname, const GLint *params)` | 2.0+ | Sets multiple integer texture parameters from a pointer |
| 260 | Textures | `void glTexParameterIiv(GLenum target, GLenum pname, const GLint *params)` | 3.2+ | Sets integer texture parameters without integer-to-float conversion |
| 261 | Textures | `void glTexParameterIuiv(GLenum target, GLenum pname, const GLuint *params)` | 3.2+ | Sets unsigned integer texture parameters without conversion |
| 262 | Textures | `void glGetTexParameterfv(GLenum target, GLenum pname, GLfloat *params)` | 2.0+ | Returns float texture sampling parameters |
| 263 | Textures | `void glGetTexParameteriv(GLenum target, GLenum pname, GLint *params)` | 2.0+ | Returns integer texture sampling parameters |
| 264 | Textures | `void glGetTexParameterIiv(GLenum target, GLenum pname, GLint *params)` | 3.2+ | Returns integer texture parameters as raw integers |
| 265 | Textures | `void glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint *params)` | 3.2+ | Returns unsigned integer texture parameters as raw unsigned integers |
| 266 | Textures | `void glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint *params)` | 3.1+ | Returns integer parameters of a specific texture mipmap level |
| 267 | Textures | `void glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat *params)` | 3.1+ | Returns float parameters of a specific texture mipmap level |
| 268 | Textures | `void glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer)` | 3.2+ | Attaches a buffer object's data store to a buffer texture |
| 269 | Textures | `void glTexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)` | 3.2+ | Attaches a sub-range of a buffer object to a buffer texture |
| 270 | Textures | `void glGetMultisamplefv(GLenum pname, GLuint index, GLfloat *val)` | 3.1+ | Returns the location of a specific sample in a multisample texture |
| 271 | Textures | `void glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint *params)` | 3.0+ | Queries implementation properties for a given internal format and target |
| 272 | Textures | `void glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format)` | 3.1+ | Binds a texture level to an image unit for image load/store in shaders |
| 273 | Samplers | `void glGenSamplers(GLsizei count, GLuint *samplers)` | 3.0+ | Generates one or more sampler object names |
| 274 | Samplers | `void glDeleteSamplers(GLsizei count, const GLuint *samplers)` | 3.0+ | Deletes sampler objects |
| 275 | Samplers | `void glBindSampler(GLuint unit, GLuint sampler)` | 3.0+ | Binds a sampler to a texture unit, overriding the texture's own sampling state |
| 276 | Samplers | `GLboolean glIsSampler(GLuint sampler)` | 3.0+ | Returns GL_TRUE if the name is a valid sampler object |
| 277 | Samplers | `void glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param)` | 3.0+ | Sets a float sampling parameter on a sampler object |
| 278 | Samplers | `void glSamplerParameteri(GLuint sampler, GLenum pname, GLint param)` | 3.0+ | Sets an integer sampling parameter on a sampler object |
| 279 | Samplers | `void glSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat *param)` | 3.0+ | Sets multiple float sampling parameters on a sampler from a pointer |
| 280 | Samplers | `void glSamplerParameteriv(GLuint sampler, GLenum pname, const GLint *param)` | 3.0+ | Sets multiple integer sampling parameters on a sampler from a pointer |
| 281 | Samplers | `void glSamplerParameterIiv(GLuint sampler, GLenum pname, const GLint *param)` | 3.2+ | Sets signed integer sampler parameters without conversion |
| 282 | Samplers | `void glSamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint *param)` | 3.2+ | Sets unsigned integer sampler parameters without conversion |
| 283 | Samplers | `void glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat *params)` | 3.0+ | Returns float sampling parameters from a sampler object |
| 284 | Samplers | `void glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint *params)` | 3.0+ | Returns integer sampling parameters from a sampler object |
| 285 | Samplers | `void glGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint *params)` | 3.2+ | Returns signed integer sampler parameters as raw integers |
| 286 | Samplers | `void glGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint *params)` | 3.2+ | Returns unsigned integer sampler parameters as raw unsigned integers |
| 287 | Framebuffers | `void glGenFramebuffers(GLsizei n, GLuint *framebuffers)` | 2.0+ | Generates one or more framebuffer object names |
| 288 | Framebuffers | `void glDeleteFramebuffers(GLsizei n, const GLuint *framebuffers)` | 2.0+ | Deletes framebuffer objects |
| 289 | Framebuffers | `void glBindFramebuffer(GLenum target, GLuint framebuffer)` | 2.0+ | Binds a framebuffer to GL_FRAMEBUFFER, GL_READ_FRAMEBUFFER, or GL_DRAW_FRAMEBUFFER |
| 290 | Framebuffers | `GLboolean glIsFramebuffer(GLuint framebuffer)` | 2.0+ | Returns GL_TRUE if the name is a valid framebuffer object |
| 291 | Framebuffers | `GLenum glCheckFramebufferStatus(GLenum target)` | 2.0+ | Returns the completeness status of the bound framebuffer |
| 292 | Framebuffers | `void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)` | 2.0+ | Attaches a 2D texture level as a framebuffer color/depth/stencil attachment |
| 293 | Framebuffers | `void glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)` | 3.0+ | Attaches a single layer of a layered texture to a framebuffer attachment point |
| 294 | Framebuffers | `void glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level)` | 3.2+ | Attaches an entire layered texture to a framebuffer (for geometry shader layered rendering) |
| 295 | Framebuffers | `void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)` | 2.0+ | Attaches a renderbuffer as a framebuffer color/depth/stencil attachment |
| 296 | Framebuffers | `void glFramebufferParameteri(GLenum target, GLenum pname, GLint param)` | 3.1+ | Sets default parameters on a framebuffer that has no attachments |
| 297 | Framebuffers | `void glGetFramebufferParameteriv(GLenum target, GLenum pname, GLint *params)` | 3.1+ | Returns parameters set on a framebuffer via glFramebufferParameteri |
| 298 | Framebuffers | `void glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint *params)` | 2.0+ | Returns parameters of a specific framebuffer attachment |
| 299 | Framebuffers | `void glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)` | 3.0+ | Copies a rectangle between framebuffers; also resolves MSAA |
| 300 | Framebuffers | `void glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments)` | 3.0+ | Hints that attachment contents are no longer needed (bandwidth optimization) |
| 301 | Framebuffers | `void glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height)` | 3.0+ | Invalidates a sub-rectangle of framebuffer attachments |
| 302 | Renderbuffers | `void glGenRenderbuffers(GLsizei n, GLuint *renderbuffers)` | 2.0+ | Generates one or more renderbuffer object names |
| 303 | Renderbuffers | `void glDeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers)` | 2.0+ | Deletes renderbuffer objects and frees their GPU memory |
| 304 | Renderbuffers | `void glBindRenderbuffer(GLenum target, GLuint renderbuffer)` | 2.0+ | Binds a renderbuffer to the GL_RENDERBUFFER target |
| 305 | Renderbuffers | `GLboolean glIsRenderbuffer(GLuint renderbuffer)` | 2.0+ | Returns GL_TRUE if the name is a valid renderbuffer object |
| 306 | Renderbuffers | `void glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)` | 2.0+ | Allocates single-sample GPU storage for a renderbuffer |
| 307 | Renderbuffers | `void glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)` | 3.0+ | Allocates multisample GPU storage for a renderbuffer (for MSAA) |
| 308 | Renderbuffers | `void glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint *params)` | 2.0+ | Returns parameters of the bound renderbuffer (width, height, format, samples) |
| 309 | Transform Feedback | `void glGenTransformFeedbacks(GLsizei n, GLuint *ids)` | 3.0+ | Generates one or more transform feedback object names |
| 310 | Transform Feedback | `void glDeleteTransformFeedbacks(GLsizei n, const GLuint *ids)` | 3.0+ | Deletes transform feedback objects |
| 311 | Transform Feedback | `void glBindTransformFeedback(GLenum target, GLuint id)` | 3.0+ | Binds a transform feedback object to capture its output buffer state |
| 312 | Transform Feedback | `GLboolean glIsTransformFeedback(GLuint id)` | 3.0+ | Returns GL_TRUE if the name is a valid transform feedback object |
| 313 | Transform Feedback | `void glBeginTransformFeedback(GLenum primitiveMode)` | 3.0+ | Starts capturing vertex shader outputs into transform feedback buffers |
| 314 | Transform Feedback | `void glEndTransformFeedback(void)` | 3.0+ | Ends the current transform feedback capture session |
| 315 | Transform Feedback | `void glPauseTransformFeedback(void)` | 3.0+ | Pauses an active transform feedback session (can be resumed) |
| 316 | Transform Feedback | `void glResumeTransformFeedback(void)` | 3.0+ | Resumes a previously paused transform feedback session |
| 317 | Transform Feedback | `void glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode)` | 3.0+ | Specifies which vertex shader outputs to capture before linking |
| 318 | Transform Feedback | `void glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name)` | 3.0+ | Returns name, type, and size of a transform feedback varying by index |
| 319 | Query Objects | `void glGenQueries(GLsizei n, GLuint *ids)` | 3.0+ | Generates one or more query object names |
| 320 | Query Objects | `void glDeleteQueries(GLsizei n, const GLuint *ids)` | 3.0+ | Deletes query objects |
| 321 | Query Objects | `GLboolean glIsQuery(GLuint id)` | 3.0+ | Returns GL_TRUE if the name is a valid query object |
| 322 | Query Objects | `void glBeginQuery(GLenum target, GLuint id)` | 3.0+ | Begins recording a GPU query (occlusion, primitives written, etc.) |
| 323 | Query Objects | `void glEndQuery(GLenum target)` | 3.0+ | Ends a query; result becomes available asynchronously |
| 324 | Query Objects | `void glGetQueryiv(GLenum target, GLenum pname, GLint *params)` | 3.0+ | Returns info about a query target (active query name, counter bits) |
| 325 | Query Objects | `void glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint *params)` | 3.0+ | Returns the result of a completed query as an unsigned integer |
| 326 | Sync Objects | `GLsync glFenceSync(GLenum condition, GLbitfield flags)` | 3.0+ | Creates a sync object and inserts a fence into the GL command stream |
| 327 | Sync Objects | `void glDeleteSync(GLsync sync)` | 3.0+ | Deletes a sync object |
| 328 | Sync Objects | `GLboolean glIsSync(GLsync sync)` | 3.0+ | Returns GL_TRUE if the object is a valid sync |
| 329 | Sync Objects | `GLenum glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)` | 3.0+ | Blocks the CPU until a sync is signaled or the timeout expires |
| 330 | Sync Objects | `void glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)` | 3.0+ | Blocks the GPU command processor until a sync is signaled (CPU not blocked) |
| 331 | Sync Objects | `void glGetSynciv(GLsync sync, GLenum pname, GLsizei count, GLsizei *length, GLint *values)` | 3.0+ | Returns the status or type of a sync object (signaled / unsignaled) |
| 332 | Compute Shaders | `void glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z)` | 3.1+ | Launches a compute shader with a 3D grid of work groups |
| 333 | Compute Shaders | `void glDispatchComputeIndirect(GLintptr indirect)` | 3.1+ | Launches compute; work group dimensions read from GL_DISPATCH_INDIRECT_BUFFER |
| 334 | Compute Shaders | `void glMemoryBarrier(GLbitfield barriers)` | 3.1+ | Inserts a memory barrier ensuring visibility of image/SSBO/atomic writes |
| 335 | Compute Shaders | `void glMemoryBarrierByRegion(GLbitfield barriers)` | 3.1+ | Tile-friendly memory barrier guaranteeing visibility within the current region |
| 336 | Program Pipelines | `void glGenProgramPipelines(GLsizei n, GLuint *pipelines)` | 3.1+ | Generates one or more program pipeline object names |
| 337 | Program Pipelines | `void glDeleteProgramPipelines(GLsizei n, const GLuint *pipelines)` | 3.1+ | Deletes program pipeline objects |
| 338 | Program Pipelines | `void glBindProgramPipeline(GLuint pipeline)` | 3.1+ | Binds a program pipeline for rendering |
| 339 | Program Pipelines | `GLboolean glIsProgramPipeline(GLuint pipeline)` | 3.1+ | Returns GL_TRUE if the name is a valid program pipeline object |
| 340 | Program Pipelines | `void glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program)` | 3.1+ | Installs shader stages from a separable program into a pipeline |
| 341 | Program Pipelines | `void glActiveShaderProgram(GLuint pipeline, GLuint program)` | 3.1+ | Sets the active program in a pipeline for direct uniform calls |
| 342 | Program Pipelines | `GLuint glCreateShaderProgramv(GLenum type, GLsizei count, const GLchar *const*strings)` | 3.1+ | Compiles, links, and creates a separable program in one step |
| 343 | Program Pipelines | `void glValidateProgramPipeline(GLuint pipeline)` | 3.1+ | Validates a pipeline can execute given current GL state |
| 344 | Program Pipelines | `void glGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint *params)` | 3.1+ | Returns parameters of a program pipeline (installed stages, validate status) |
| 345 | Program Pipelines | `void glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog)` | 3.1+ | Returns the info log for a pipeline (validation results, linker messages) |
| 346 | Geometry / Tessellation | `void glPatchParameteri(GLenum pname, GLint value)` | 3.2+ | Sets the number of vertices per patch for tessellation (GL_PATCH_VERTICES) |
| 347 | Geometry / Tessellation | `void glPrimitiveBoundingBox(GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW)` | 3.2+ | Provides a bounding box hint for tessellated/geometry-shader geometry |
| 348 | Debug | `void glDebugMessageCallback(GLDEBUGPROC callback, const void *userParam)` | 3.2+ | Registers a callback invoked when the GL generates a debug message |
| 349 | Debug | `void glDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled)` | 3.2+ | Filters which debug messages are generated by source, type, and severity |
| 350 | Debug | `void glDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf)` | 3.2+ | Inserts an application-generated message into the GL debug stream |
| 351 | Debug | `GLuint glGetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog)` | 3.2+ | Retrieves queued debug messages from the GL internal message log |
| 352 | Debug | `void glPushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar *message)` | 3.2+ | Pushes a named debug group onto the stack (visible in GPU debuggers) |
| 353 | Debug | `void glPopDebugGroup(void)` | 3.2+ | Pops the innermost debug group from the stack |
| 354 | Debug | `void glObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar *label)` | 3.2+ | Assigns a human-readable label to any GL object for GPU debugger tools |
| 355 | Debug | `void glObjectPtrLabel(const void *ptr, GLsizei length, const GLchar *label)` | 3.2+ | Assigns a label to a sync object (identified by pointer) |
| 356 | Debug | `void glGetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label)` | 3.2+ | Returns the label previously assigned to a GL object |
| 357 | Debug | `void glGetObjectPtrLabel(const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label)` | 3.2+ | Returns the label previously assigned to a sync object |
| 358 | Robustness | `GLenum glGetGraphicsResetStatus(void)` | 3.2+ | Returns the graphics reset status for robustness/error recovery |
