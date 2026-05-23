#include "metagl/metagl.hpp"

#include <cstddef>

// ============================================================
// Internal raw GL types and function pointer typedefs
// ============================================================
namespace metagl::detail
{
    // Raw GL function pointer typedefs (kept private to this TU)
    using PFNGLGENBUFFERSPROC        = void (*)(GLsizei n, GLuint* buffers);
    using PFNGLDELETEBUFFERSPROC     = void (*)(GLsizei n, const GLuint* buffers);
    using PFNGLBINDBUFFERPROC        = void (*)(GLenum target, GLuint buffer);
    using PFNGLBUFFERDATAPROC        = void (*)(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
    using PFNGLBUFFERSUBDATAPROC     = void (*)(GLenum target, GLintptr offset, GLsizeiptr size, const void* data);
    using PFNGLBINDBUFFERBASEPROC    = void (*)(GLenum target, GLuint index, GLuint buffer);

    using PFNGLGETSTRINGPROC         = const unsigned char* (*)(GLenum name);
    using PFNGLGETSTRINGIPROC        = const unsigned char* (*)(GLenum name, GLuint index);
    using PFNGLGETINTEGERVPROC       = void (*)(GLenum pname, GLint* data);

    using PFNGLCREATESHADERPROC      = GLuint (*)(GLenum type);
    using PFNGLSHADERSOURCEPROC      = void (*)(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
    using PFNGLCOMPILESHADERPROC     = void (*)(GLuint shader);
    using PFNGLGETSHADERIVPROC       = void (*)(GLuint shader, GLenum pname, GLint* params);
    using PFNGLGETSHADERINFOLOGPROC  = void (*)(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
    using PFNGLDELETESHADERPROC      = void (*)(GLuint shader);

    using PFNGLCREATEPROGRAMPROC     = GLuint (*)(void);
    using PFNGLATTACHSHADERPROC      = void (*)(GLuint program, GLuint shader);
    using PFNGLDETACHSHADERPROC      = void (*)(GLuint program, GLuint shader);
    using PFNGLLINKPROGRAMPROC       = void (*)(GLuint program);
    using PFNGLGETPROGRAMIVPROC      = void (*)(GLuint program, GLenum pname, GLint* params);
    using PFNGLGETPROGRAMINFOLOGPROC = void (*)(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
    using PFNGLUSEPROGRAMPROC        = void (*)(GLuint program);
    using PFNGLDELETEPROGRAMPROC     = void (*)(GLuint program);

    using PFNGLGETUNIFORMLOCATIONPROC = GLint (*)(GLuint program, const GLchar* name);
    using PFNGLUNIFORM1IPROC         = void (*)(GLint location, GLint v0);
    using PFNGLUNIFORM1FPROC         = void (*)(GLint location, GLfloat v0);
    using PFNGLUNIFORM3FPROC         = void (*)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
    using PFNGLUNIFORM4FPROC         = void (*)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
    using PFNGLUNIFORMMATRIX4FVPROC  = void (*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

    using PFNGLGENVERTEXARRAYSPROC     = void (*)(GLsizei n, GLuint* arrays);
    using PFNGLDELETEVERTEXARRAYSPROC  = void (*)(GLsizei n, const GLuint* arrays);
    using PFNGLBINDVERTEXARRAYPROC     = void (*)(GLuint array);
    using PFNGLENABLEATTRIBARRAYPROC   = void (*)(GLuint index);
    using PFNGLVERTEXATTRIBPOINTERPROC = void (*)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

    using PFNGLCLEARPROC      = void (*)(GLbitfield mask);
    using PFNGLCLEARCOLORPROC = void (*)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    using PFNGLVIEWPORTPROC   = void (*)(GLint x, GLint y, GLsizei width, GLsizei height);
    using PFNGLDRAWARRAYSPROC  = void (*)(GLenum mode, GLint first, GLsizei count);
    using PFNGLDRAWELEMENTSPROC = void (*)(GLenum mode, GLsizei count, GLenum type, const void* indices);

    using PFNGLGENTEXTURESPROC   = void (*)(GLsizei n, GLuint* textures);
    using PFNGLDELETETEXTURESPROC = void (*)(GLsizei n, const GLuint* textures);
    using PFNGLBINDTEXTUREPROC   = void (*)(GLenum target, GLuint texture);
    using PFNGLACTIVETEXTUREPROC = void (*)(GLenum texture);
    using PFNGLPIXELSTOREIPROC   = void (*)(GLenum pname, GLint param);
    using PFNGLTEXIMAGE2DPROC    = void (*)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels);
    using PFNGLTEXPARAMETERIPROC = void (*)(GLenum target, GLenum pname, GLint param);

    using PFNGLENABLEPROC     = void (*)(GLenum cap);
    using PFNGLDISABLEPROC    = void (*)(GLenum cap);
    using PFNGLBLENDFUNCPROC  = void (*)(GLenum sfactor, GLenum dfactor);
    using PFNGLDEPTHFUNCPROC  = void (*)(GLenum func);
    using PFNGLDEPTHMASKPROC  = void (*)(GLboolean flag);
    using PFNGLCLEARDEPTHPROC = void (*)(GLdouble depth);
    using PFNGLCLEARDEPTHFPROC = void (*)(GLfloat depth);
    using PFNGLCULLFACEPROC   = void (*)(GLenum mode);
    using PFNGLFRONTFACEPROC  = void (*)(GLenum mode);

    // ============================================================
    // Raw GL constants (hidden inside detail)
    // ============================================================

    // String names
    constexpr GLenum GL_VENDOR                    = 0x1F00;
    constexpr GLenum GL_RENDERER                  = 0x1F01;
    constexpr GLenum GL_VERSION                   = 0x1F02;
    constexpr GLenum GL_EXTENSIONS                = 0x1F03;
    constexpr GLenum GL_SHADING_LANGUAGE_VERSION  = 0x8B8C;

    // Integer names
    constexpr GLenum GL_MAJOR_VERSION    = 0x821B;
    constexpr GLenum GL_MINOR_VERSION    = 0x821C;
    constexpr GLenum GL_NUM_EXTENSIONS   = 0x821D;
    constexpr GLenum GL_MAX_TEXTURE_SIZE = 0x0D33;
    constexpr GLenum GL_VIEWPORT         = 0x0BA2;

    // Texture targets / params / filters / wrap
    constexpr GLenum GL_TEXTURE_2D         = 0x0DE1;
    constexpr GLenum GL_TEXTURE_MAG_FILTER = 0x2800;
    constexpr GLenum GL_TEXTURE_MIN_FILTER = 0x2801;
    constexpr GLenum GL_TEXTURE_WRAP_S     = 0x2802;
    constexpr GLenum GL_TEXTURE_WRAP_T     = 0x2803;
    constexpr GLenum GL_NEAREST            = 0x2600;
    constexpr GLenum GL_LINEAR             = 0x2601;
    constexpr GLenum GL_CLAMP_TO_EDGE      = 0x812F;
    constexpr GLenum GL_RGBA               = 0x1908;
    constexpr GLenum GL_BGRA               = 0x80E1;
    constexpr GLenum GL_TEXTURE0           = 0x84C0;
    constexpr GLenum GL_UNPACK_ALIGNMENT   = 0x0CF5;

    // Blend / state
    constexpr GLenum GL_BLEND             = 0x0BE2;
    constexpr GLenum GL_SCISSOR_TEST      = 0x0C11;
    constexpr GLenum GL_SRC_ALPHA         = 0x0302;
    constexpr GLenum GL_ONE_MINUS_SRC_ALPHA = 0x0303;
    constexpr GLenum GL_DST_ALPHA         = 0x0304;
    constexpr GLenum GL_ONE_MINUS_DST_ALPHA = 0x0305;

    // Depth
    constexpr GLenum GL_DEPTH_TEST = 0x0B71;
    constexpr GLenum GL_NEVER      = 0x0200;
    constexpr GLenum GL_LESS       = 0x0201;
    constexpr GLenum GL_EQUAL      = 0x0202;
    constexpr GLenum GL_LEQUAL     = 0x0203;
    constexpr GLenum GL_GREATER    = 0x0204;
    constexpr GLenum GL_NOTEQUAL   = 0x0205;
    constexpr GLenum GL_GEQUAL     = 0x0206;
    constexpr GLenum GL_ALWAYS     = 0x0207;

    // Culling
    constexpr GLenum GL_CULL_FACE = 0x0B44;
    constexpr GLenum GL_FRONT     = 0x0404;
    constexpr GLenum GL_BACK      = 0x0405;
    constexpr GLenum GL_CW        = 0x0900;
    constexpr GLenum GL_CCW       = 0x0901;
    constexpr GLenum GL_FRONT_AND_BACK = 0x0408;

    // Buffer targets
    constexpr GLenum GL_ARRAY_BUFFER         = 0x8892;
    constexpr GLenum GL_ELEMENT_ARRAY_BUFFER = 0x8893;
    constexpr GLenum GL_UNIFORM_BUFFER       = 0x8A11;
    constexpr GLenum GL_COPY_READ_BUFFER     = 0x8F36;
    constexpr GLenum GL_COPY_WRITE_BUFFER    = 0x8F37;
    constexpr GLenum GL_STATIC_DRAW          = 0x88E4;
    constexpr GLenum GL_DYNAMIC_DRAW         = 0x88E8;

    // Shader types
    constexpr GLenum GL_VERTEX_SHADER          = 0x8B31;
    constexpr GLenum GL_FRAGMENT_SHADER        = 0x8B30;
    constexpr GLenum GL_GEOMETRY_SHADER        = 0x8DD9;
    constexpr GLenum GL_TESS_CONTROL_SHADER    = 0x8E88;
    constexpr GLenum GL_TESS_EVALUATION_SHADER = 0x8E87;
    constexpr GLenum GL_COMPUTE_SHADER         = 0x91B9;
    constexpr GLenum GL_COMPILE_STATUS         = 0x8B81;
    constexpr GLenum GL_LINK_STATUS            = 0x8B82;
    constexpr GLenum GL_INFO_LOG_LENGTH        = 0x8B84;

    // Primitive types
    constexpr GLenum GL_POINTS         = 0x0000;
    constexpr GLenum GL_LINES          = 0x0001;
    constexpr GLenum GL_LINE_LOOP      = 0x0002;
    constexpr GLenum GL_LINE_STRIP     = 0x0003;
    constexpr GLenum GL_TRIANGLES      = 0x0004;
    constexpr GLenum GL_TRIANGLE_STRIP = 0x0005;
    constexpr GLenum GL_TRIANGLE_FAN   = 0x0006;

    // Data types
    constexpr GLenum GL_FLOAT          = 0x1406;
    constexpr GLenum GL_BYTE           = 0x1400;
    constexpr GLenum GL_UNSIGNED_BYTE  = 0x1401;
    constexpr GLenum GL_SHORT          = 0x1402;
    constexpr GLenum GL_UNSIGNED_SHORT = 0x1403;
    constexpr GLenum GL_INT            = 0x1404;
    constexpr GLenum GL_UNSIGNED_INT   = 0x1405;

    // ============================================================
    // Function pointer table
    // ============================================================
    struct GlTable
    {
        bool initialized = false;

        PFNGLGENBUFFERSPROC        GenBuffers        = nullptr;
        PFNGLDELETEBUFFERSPROC     DeleteBuffers     = nullptr;
        PFNGLBINDBUFFERPROC        BindBuffer        = nullptr;
        PFNGLBUFFERDATAPROC        BufferData        = nullptr;
        PFNGLBUFFERSUBDATAPROC     BufferSubData     = nullptr;
        PFNGLBINDBUFFERBASEPROC    BindBufferBase    = nullptr;

        PFNGLGETSTRINGPROC         GetString         = nullptr;
        PFNGLGETSTRINGIPROC        GetStringi        = nullptr;
        PFNGLGETINTEGERVPROC       GetIntegerv       = nullptr;

        PFNGLCREATESHADERPROC      CreateShader      = nullptr;
        PFNGLSHADERSOURCEPROC      ShaderSource      = nullptr;
        PFNGLCOMPILESHADERPROC     CompileShader     = nullptr;
        PFNGLGETSHADERIVPROC       GetShaderiv       = nullptr;
        PFNGLGETSHADERINFOLOGPROC  GetShaderInfoLog  = nullptr;
        PFNGLDELETESHADERPROC      DeleteShader      = nullptr;

        PFNGLCREATEPROGRAMPROC     CreateProgram     = nullptr;
        PFNGLATTACHSHADERPROC      AttachShader      = nullptr;
        PFNGLDETACHSHADERPROC      DetachShader      = nullptr;
        PFNGLLINKPROGRAMPROC       LinkProgram       = nullptr;
        PFNGLGETPROGRAMIVPROC      GetProgramiv      = nullptr;
        PFNGLGETPROGRAMINFOLOGPROC GetProgramInfoLog = nullptr;
        PFNGLUSEPROGRAMPROC        UseProgram        = nullptr;
        PFNGLDELETEPROGRAMPROC     DeleteProgram     = nullptr;

        PFNGLGETUNIFORMLOCATIONPROC GetUniformLocation = nullptr;
        PFNGLUNIFORM1IPROC          Uniform1i          = nullptr;
        PFNGLUNIFORM1FPROC          Uniform1f          = nullptr;
        PFNGLUNIFORM3FPROC          Uniform3f          = nullptr;
        PFNGLUNIFORM4FPROC          Uniform4f          = nullptr;
        PFNGLUNIFORMMATRIX4FVPROC   UniformMatrix4fv   = nullptr;

        PFNGLGENVERTEXARRAYSPROC     GenVertexArrays     = nullptr;
        PFNGLDELETEVERTEXARRAYSPROC  DeleteVertexArrays  = nullptr;
        PFNGLBINDVERTEXARRAYPROC     BindVertexArray     = nullptr;
        PFNGLENABLEATTRIBARRAYPROC   EnableVertexAttribArray = nullptr;
        PFNGLVERTEXATTRIBPOINTERPROC VertexAttribPointer = nullptr;

        PFNGLCLEARPROC      Clear      = nullptr;
        PFNGLCLEARCOLORPROC ClearColor = nullptr;
        PFNGLVIEWPORTPROC   Viewport   = nullptr;
        PFNGLDRAWARRAYSPROC  DrawArrays  = nullptr;
        PFNGLDRAWELEMENTSPROC DrawElements = nullptr;

        PFNGLGENTEXTURESPROC    GenTextures    = nullptr;
        PFNGLDELETETEXTURESPROC DeleteTextures = nullptr;
        PFNGLBINDTEXTUREPROC    BindTexture    = nullptr;
        PFNGLACTIVETEXTUREPROC  ActiveTexture  = nullptr;
        PFNGLPIXELSTOREIPROC    PixelStorei    = nullptr;
        PFNGLTEXIMAGE2DPROC     TexImage2D     = nullptr;
        PFNGLTEXPARAMETERIPROC  TexParameteri  = nullptr;

        PFNGLENABLEPROC      Enable      = nullptr;
        PFNGLDISABLEPROC     Disable     = nullptr;
        PFNGLBLENDFUNCPROC   BlendFunc   = nullptr;
        PFNGLDEPTHFUNCPROC   DepthFunc   = nullptr;
        PFNGLDEPTHMASKPROC   DepthMask   = nullptr;
        PFNGLCLEARDEPTHPROC  ClearDepth  = nullptr;
        PFNGLCLEARDEPTHFPROC ClearDepthf = nullptr;
        PFNGLCULLFACEPROC    CullFace    = nullptr;
        PFNGLFRONTFACEPROC   FrontFace   = nullptr;
    };

    static GlTable g_gl;

    template<typename T>
    static T load(GlGetProcAddressFn loader, const char* name)
    {
        return reinterpret_cast<T>(loader(name));
    }

    // ============================================================
    // Enum -> raw GL value converters
    // ============================================================

    static GLenum to_raw(BufferTarget t)
    {
        switch (t)
        {
            case BufferTarget::Array:        return GL_ARRAY_BUFFER;
            case BufferTarget::ElementArray: return GL_ELEMENT_ARRAY_BUFFER;
            case BufferTarget::Uniform:      return GL_UNIFORM_BUFFER;
            case BufferTarget::CopyRead:     return GL_COPY_READ_BUFFER;
            case BufferTarget::CopyWrite:    return GL_COPY_WRITE_BUFFER;
        }
        return 0;
    }

    static GLenum to_raw(BufferUsage u)
    {
        switch (u)
        {
            case BufferUsage::StaticDraw:  return GL_STATIC_DRAW;
            case BufferUsage::DynamicDraw: return GL_DYNAMIC_DRAW;
        }
        return GL_STATIC_DRAW;
    }

    static GLenum to_raw(ShaderType t)
    {
        switch (t)
        {
            case ShaderType::Vertex:         return GL_VERTEX_SHADER;
            case ShaderType::Fragment:       return GL_FRAGMENT_SHADER;
            case ShaderType::Geometry:       return GL_GEOMETRY_SHADER;
            case ShaderType::TessControl:    return GL_TESS_CONTROL_SHADER;
            case ShaderType::TessEvaluation: return GL_TESS_EVALUATION_SHADER;
            case ShaderType::Compute:        return GL_COMPUTE_SHADER;
        }
        return 0;
    }

    static GLenum to_raw(ShaderParameter p)
    {
        switch (p)
        {
            case ShaderParameter::CompileStatus: return GL_COMPILE_STATUS;
            case ShaderParameter::InfoLogLength: return GL_INFO_LOG_LENGTH;
        }
        return 0;
    }

    static GLenum to_raw(ProgramParameter p)
    {
        switch (p)
        {
            case ProgramParameter::LinkStatus:   return GL_LINK_STATUS;
            case ProgramParameter::InfoLogLength: return GL_INFO_LOG_LENGTH;
        }
        return 0;
    }

    static GLenum to_raw(TextureTarget t)
    {
        switch (t)
        {
            case TextureTarget::Texture2D: return GL_TEXTURE_2D;
        }
        return 0;
    }

    static GLenum to_raw(TextureParameter p)
    {
        switch (p)
        {
            case TextureParameter::MinFilter: return GL_TEXTURE_MIN_FILTER;
            case TextureParameter::MagFilter: return GL_TEXTURE_MAG_FILTER;
            case TextureParameter::WrapS:     return GL_TEXTURE_WRAP_S;
            case TextureParameter::WrapT:     return GL_TEXTURE_WRAP_T;
        }
        return 0;
    }

    static GLint to_raw(TextureFilter f)
    {
        switch (f)
        {
            case TextureFilter::Nearest: return static_cast<GLint>(GL_NEAREST);
            case TextureFilter::Linear:  return static_cast<GLint>(GL_LINEAR);
        }
        return static_cast<GLint>(GL_LINEAR);
    }

    static GLint to_raw(TextureWrap w)
    {
        switch (w)
        {
            case TextureWrap::ClampToEdge: return static_cast<GLint>(GL_CLAMP_TO_EDGE);
        }
        return static_cast<GLint>(GL_CLAMP_TO_EDGE);
    }

    static GLenum to_raw(PixelFormat f)
    {
        switch (f)
        {
            case PixelFormat::Rgba: return GL_RGBA;
            case PixelFormat::Bgra: return GL_BGRA;
        }
        return GL_RGBA;
    }

    static GLenum to_raw(PixelType t)
    {
        switch (t)
        {
            case PixelType::UnsignedByte: return GL_UNSIGNED_BYTE;
        }
        return GL_UNSIGNED_BYTE;
    }

    static GLenum to_raw(PrimitiveType t)
    {
        switch (t)
        {
            case PrimitiveType::Points:        return GL_POINTS;
            case PrimitiveType::Lines:         return GL_LINES;
            case PrimitiveType::LineLoop:      return GL_LINE_LOOP;
            case PrimitiveType::LineStrip:     return GL_LINE_STRIP;
            case PrimitiveType::Triangles:     return GL_TRIANGLES;
            case PrimitiveType::TriangleStrip: return GL_TRIANGLE_STRIP;
            case PrimitiveType::TriangleFan:   return GL_TRIANGLE_FAN;
        }
        return GL_TRIANGLES;
    }

    static GLenum to_raw(DataType t)
    {
        switch (t)
        {
            case DataType::Float:         return GL_FLOAT;
            case DataType::Byte:          return GL_BYTE;
            case DataType::UnsignedByte:  return GL_UNSIGNED_BYTE;
            case DataType::Short:         return GL_SHORT;
            case DataType::UnsignedShort: return GL_UNSIGNED_SHORT;
            case DataType::Int:           return GL_INT;
            case DataType::UnsignedInt:   return GL_UNSIGNED_INT;
        }
        return GL_FLOAT;
    }

    static GLenum to_raw(Capability c)
    {
        switch (c)
        {
            case Capability::Blend:       return GL_BLEND;
            case Capability::DepthTest:   return GL_DEPTH_TEST;
            case Capability::ScissorTest: return GL_SCISSOR_TEST;
            case Capability::CullFace:    return GL_CULL_FACE;
        }
        return 0;
    }

    static GLenum to_raw(CompareFunc f)
    {
        switch (f)
        {
            case CompareFunc::Never:        return GL_NEVER;
            case CompareFunc::Less:         return GL_LESS;
            case CompareFunc::Equal:        return GL_EQUAL;
            case CompareFunc::LessEqual:    return GL_LEQUAL;
            case CompareFunc::Greater:      return GL_GREATER;
            case CompareFunc::NotEqual:     return GL_NOTEQUAL;
            case CompareFunc::GreaterEqual: return GL_GEQUAL;
            case CompareFunc::Always:       return GL_ALWAYS;
        }
        return GL_LESS;
    }

    static GLenum to_raw(CullFace f)
    {
        switch (f)
        {
            case CullFace::Front:        return GL_FRONT;
            case CullFace::Back:         return GL_BACK;
            case CullFace::FrontAndBack: return GL_FRONT_AND_BACK;
        }
        return GL_BACK;
    }

    static GLenum to_raw(FrontFace f)
    {
        switch (f)
        {
            case FrontFace::CW:  return GL_CW;
            case FrontFace::CCW: return GL_CCW;
        }
        return GL_CCW;
    }

    static GLenum to_raw(StringName n)
    {
        switch (n)
        {
            case StringName::Vendor:                  return GL_VENDOR;
            case StringName::Renderer:                return GL_RENDERER;
            case StringName::Version:                 return GL_VERSION;
            case StringName::Extensions:              return GL_EXTENSIONS;
            case StringName::ShadingLanguageVersion:  return GL_SHADING_LANGUAGE_VERSION;
        }
        return 0;
    }

    static GLenum to_raw(IntegerName n)
    {
        switch (n)
        {
            case IntegerName::MajorVersion:   return GL_MAJOR_VERSION;
            case IntegerName::MinorVersion:   return GL_MINOR_VERSION;
            case IntegerName::NumExtensions:  return GL_NUM_EXTENSIONS;
            case IntegerName::MaxTextureSize: return GL_MAX_TEXTURE_SIZE;
            case IntegerName::Viewport:       return GL_VIEWPORT;
        }
        return 0;
    }

    static GLenum to_raw(BlendFactor f)
    {
        switch (f)
        {
            case BlendFactor::Zero:             return 0;
            case BlendFactor::One:              return 1;
            case BlendFactor::SrcAlpha:         return GL_SRC_ALPHA;
            case BlendFactor::OneMinusSrcAlpha: return GL_ONE_MINUS_SRC_ALPHA;
            case BlendFactor::DstAlpha:         return GL_DST_ALPHA;
            case BlendFactor::OneMinusDstAlpha: return GL_ONE_MINUS_DST_ALPHA;
        }
        return 0;
    }

} // namespace metagl::detail

// ============================================================
// Public API implementation
// ============================================================

namespace metagl
{
    bool Initialize(GlGetProcAddressFn loader)
    {
        if (loader == nullptr) return false;

        auto& gl = detail::g_gl;
        using namespace detail;

        gl.GenBuffers     = load<PFNGLGENBUFFERSPROC>(loader, "glGenBuffers");
        gl.DeleteBuffers  = load<PFNGLDELETEBUFFERSPROC>(loader, "glDeleteBuffers");
        gl.BindBuffer     = load<PFNGLBINDBUFFERPROC>(loader, "glBindBuffer");
        gl.BufferData     = load<PFNGLBUFFERDATAPROC>(loader, "glBufferData");
        gl.BufferSubData  = load<PFNGLBUFFERSUBDATAPROC>(loader, "glBufferSubData");
        gl.BindBufferBase = load<PFNGLBINDBUFFERBASEPROC>(loader, "glBindBufferBase");

        gl.GetString  = load<PFNGLGETSTRINGPROC>(loader, "glGetString");
        gl.GetStringi = load<PFNGLGETSTRINGIPROC>(loader, "glGetStringi");
        gl.GetIntegerv = load<PFNGLGETINTEGERVPROC>(loader, "glGetIntegerv");

        if (!gl.GetString || !gl.GetIntegerv) return false;

        gl.CreateShader     = load<PFNGLCREATESHADERPROC>(loader, "glCreateShader");
        gl.ShaderSource     = load<PFNGLSHADERSOURCEPROC>(loader, "glShaderSource");
        gl.CompileShader    = load<PFNGLCOMPILESHADERPROC>(loader, "glCompileShader");
        gl.GetShaderiv      = load<PFNGLGETSHADERIVPROC>(loader, "glGetShaderiv");
        gl.GetShaderInfoLog = load<PFNGLGETSHADERINFOLOGPROC>(loader, "glGetShaderInfoLog");
        gl.DeleteShader     = load<PFNGLDELETESHADERPROC>(loader, "glDeleteShader");

        gl.CreateProgram     = load<PFNGLCREATEPROGRAMPROC>(loader, "glCreateProgram");
        gl.AttachShader      = load<PFNGLATTACHSHADERPROC>(loader, "glAttachShader");
        gl.DetachShader      = load<PFNGLDETACHSHADERPROC>(loader, "glDetachShader");
        gl.LinkProgram       = load<PFNGLLINKPROGRAMPROC>(loader, "glLinkProgram");
        gl.GetProgramiv      = load<PFNGLGETPROGRAMIVPROC>(loader, "glGetProgramiv");
        gl.GetProgramInfoLog = load<PFNGLGETPROGRAMINFOLOGPROC>(loader, "glGetProgramInfoLog");
        gl.UseProgram        = load<PFNGLUSEPROGRAMPROC>(loader, "glUseProgram");
        gl.DeleteProgram     = load<PFNGLDELETEPROGRAMPROC>(loader, "glDeleteProgram");

        gl.GetUniformLocation = load<PFNGLGETUNIFORMLOCATIONPROC>(loader, "glGetUniformLocation");
        gl.Uniform1i          = load<PFNGLUNIFORM1IPROC>(loader, "glUniform1i");
        gl.Uniform1f          = load<PFNGLUNIFORM1FPROC>(loader, "glUniform1f");
        gl.Uniform3f          = load<PFNGLUNIFORM3FPROC>(loader, "glUniform3f");
        gl.Uniform4f          = load<PFNGLUNIFORM4FPROC>(loader, "glUniform4f");
        gl.UniformMatrix4fv   = load<PFNGLUNIFORMMATRIX4FVPROC>(loader, "glUniformMatrix4fv");

        gl.GenVertexArrays        = load<PFNGLGENVERTEXARRAYSPROC>(loader, "glGenVertexArrays");
        gl.DeleteVertexArrays     = load<PFNGLDELETEVERTEXARRAYSPROC>(loader, "glDeleteVertexArrays");
        gl.BindVertexArray        = load<PFNGLBINDVERTEXARRAYPROC>(loader, "glBindVertexArray");
        gl.EnableVertexAttribArray = load<PFNGLENABLEATTRIBARRAYPROC>(loader, "glEnableVertexAttribArray");
        gl.VertexAttribPointer    = load<PFNGLVERTEXATTRIBPOINTERPROC>(loader, "glVertexAttribPointer");

        gl.Clear      = load<PFNGLCLEARPROC>(loader, "glClear");
        gl.ClearColor = load<PFNGLCLEARCOLORPROC>(loader, "glClearColor");
        gl.Viewport   = load<PFNGLVIEWPORTPROC>(loader, "glViewport");
        gl.DrawArrays  = load<PFNGLDRAWARRAYSPROC>(loader, "glDrawArrays");
        gl.DrawElements = load<PFNGLDRAWELEMENTSPROC>(loader, "glDrawElements");

        gl.GenTextures    = load<PFNGLGENTEXTURESPROC>(loader, "glGenTextures");
        gl.DeleteTextures = load<PFNGLDELETETEXTURESPROC>(loader, "glDeleteTextures");
        gl.BindTexture    = load<PFNGLBINDTEXTUREPROC>(loader, "glBindTexture");
        gl.ActiveTexture  = load<PFNGLACTIVETEXTUREPROC>(loader, "glActiveTexture");
        gl.PixelStorei    = load<PFNGLPIXELSTOREIPROC>(loader, "glPixelStorei");
        gl.TexImage2D     = load<PFNGLTEXIMAGE2DPROC>(loader, "glTexImage2D");
        gl.TexParameteri  = load<PFNGLTEXPARAMETERIPROC>(loader, "glTexParameteri");

        gl.Enable      = load<PFNGLENABLEPROC>(loader, "glEnable");
        gl.Disable     = load<PFNGLDISABLEPROC>(loader, "glDisable");
        gl.BlendFunc   = load<PFNGLBLENDFUNCPROC>(loader, "glBlendFunc");
        gl.DepthFunc   = load<PFNGLDEPTHFUNCPROC>(loader, "glDepthFunc");
        gl.DepthMask   = load<PFNGLDEPTHMASKPROC>(loader, "glDepthMask");
        gl.ClearDepth  = load<PFNGLCLEARDEPTHPROC>(loader, "glClearDepth");
        gl.ClearDepthf = load<PFNGLCLEARDEPTHFPROC>(loader, "glClearDepthf");
        gl.CullFace    = load<PFNGLCULLFACEPROC>(loader, "glCullFace");
        gl.FrontFace   = load<PFNGLFRONTFACEPROC>(loader, "glFrontFace");

        // Minimal validation
        bool ok = true;
        ok &= (gl.GenBuffers  != nullptr);
        ok &= (gl.BindBuffer  != nullptr);
        ok &= (gl.BufferData  != nullptr);
        ok &= (gl.CreateShader != nullptr);
        ok &= (gl.CreateProgram != nullptr);
        ok &= (gl.GenVertexArrays != nullptr);
        ok &= (gl.Clear     != nullptr);
        ok &= (gl.ClearColor != nullptr);
        ok &= (gl.Viewport   != nullptr);
        ok &= (gl.DrawArrays  != nullptr);
        if (!ok) return false;

        gl.initialized = true;
        return true;
    }

    bool IsInitialized()
    {
        return detail::g_gl.initialized;
    }

    // ---- Buffers ----

    void glGenBuffers(GLsizei n, GLuint* buffers)
    {
        detail::g_gl.GenBuffers(n, buffers);
    }

    void glDeleteBuffers(GLsizei n, const GLuint* buffers)
    {
        detail::g_gl.DeleteBuffers(n, buffers);
    }

    void glBindBuffer(BufferTarget target, GLuint buffer)
    {
        detail::g_gl.BindBuffer(detail::to_raw(target), buffer);
    }

    void glBufferData(BufferTarget target, GLsizeiptr size, const void* data, BufferUsage usage)
    {
        detail::g_gl.BufferData(detail::to_raw(target), size, data, detail::to_raw(usage));
    }

    void glBufferSubData(BufferTarget target, GLintptr offset, GLsizeiptr size, const void* data)
    {
        detail::g_gl.BufferSubData(detail::to_raw(target), offset, size, data);
    }

    void glBindBufferBase(BufferTarget target, GLuint index, GLuint buffer)
    {
        detail::g_gl.BindBufferBase(detail::to_raw(target), index, buffer);
    }

    // ---- Context info ----

    const GLchar* glGetString(StringName name)
    {
        return reinterpret_cast<const GLchar*>(detail::g_gl.GetString(detail::to_raw(name)));
    }

    const GLchar* glGetStringi(StringName name, GLuint index)
    {
        if (!detail::g_gl.GetStringi) return nullptr;
        return reinterpret_cast<const GLchar*>(detail::g_gl.GetStringi(detail::to_raw(name), index));
    }

    void glGetIntegerv(IntegerName pname, GLint* data)
    {
        detail::g_gl.GetIntegerv(detail::to_raw(pname), data);
    }

    void glGetIntegervRaw(GLenum pname, GLint* data)
    {
        detail::g_gl.GetIntegerv(pname, data);
    }

    // ---- Shaders ----

    GLuint glCreateShader(ShaderType type)
    {
        return detail::g_gl.CreateShader(detail::to_raw(type));
    }

    void glShaderSource(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length)
    {
        detail::g_gl.ShaderSource(shader, count, string, length);
    }

    void glCompileShader(GLuint shader)
    {
        detail::g_gl.CompileShader(shader);
    }

    void glGetShaderiv(GLuint shader, ShaderParameter pname, GLint* params)
    {
        detail::g_gl.GetShaderiv(shader, detail::to_raw(pname), params);
    }

    void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
    {
        detail::g_gl.GetShaderInfoLog(shader, bufSize, length, infoLog);
    }

    void glDeleteShader(GLuint shader)
    {
        detail::g_gl.DeleteShader(shader);
    }

    // ---- Programs ----

    GLuint glCreateProgram()
    {
        return detail::g_gl.CreateProgram();
    }

    void glAttachShader(GLuint program, GLuint shader)
    {
        detail::g_gl.AttachShader(program, shader);
    }

    void glDetachShader(GLuint program, GLuint shader)
    {
        detail::g_gl.DetachShader(program, shader);
    }

    void glLinkProgram(GLuint program)
    {
        detail::g_gl.LinkProgram(program);
    }

    void glGetProgramiv(GLuint program, ProgramParameter pname, GLint* params)
    {
        detail::g_gl.GetProgramiv(program, detail::to_raw(pname), params);
    }

    void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
    {
        detail::g_gl.GetProgramInfoLog(program, bufSize, length, infoLog);
    }

    void glUseProgram(GLuint program)
    {
        detail::g_gl.UseProgram(program);
    }

    void glDeleteProgram(GLuint program)
    {
        detail::g_gl.DeleteProgram(program);
    }

    // ---- Uniforms ----

    GLint glGetUniformLocation(GLuint program, const GLchar* name)
    {
        return detail::g_gl.GetUniformLocation(program, name);
    }

    void glUniform1i(GLint location, GLint v0)
    {
        detail::g_gl.Uniform1i(location, v0);
    }

    void glUniform1f(GLint location, GLfloat v0)
    {
        detail::g_gl.Uniform1f(location, v0);
    }

    void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
    {
        detail::g_gl.Uniform3f(location, v0, v1, v2);
    }

    void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
    {
        detail::g_gl.Uniform4f(location, v0, v1, v2, v3);
    }

    void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
    {
        detail::g_gl.UniformMatrix4fv(location, count, transpose, value);
    }

    // ---- Vertex arrays ----

    void glGenVertexArrays(GLsizei n, GLuint* arrays)
    {
        detail::g_gl.GenVertexArrays(n, arrays);
    }

    void glDeleteVertexArrays(GLsizei n, const GLuint* arrays)
    {
        detail::g_gl.DeleteVertexArrays(n, arrays);
    }

    void glBindVertexArray(GLuint array)
    {
        detail::g_gl.BindVertexArray(array);
    }

    void glEnableVertexAttribArray(GLuint index)
    {
        detail::g_gl.EnableVertexAttribArray(index);
    }

    void glVertexAttribPointer(GLuint index, GLint size, DataType type, GLboolean normalized, GLsizei stride, const void* pointer)
    {
        detail::g_gl.VertexAttribPointer(index, size, detail::to_raw(type), normalized, stride, pointer);
    }

    // ---- Commands ----

    void glClear(ClearBufferBit mask)
    {
        detail::g_gl.Clear(static_cast<GLbitfield>(mask));
    }

    void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
    {
        detail::g_gl.ClearColor(red, green, blue, alpha);
    }

    void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
    {
        detail::g_gl.Viewport(x, y, width, height);
    }

    void glDrawArrays(PrimitiveType mode, GLint first, GLsizei count)
    {
        detail::g_gl.DrawArrays(detail::to_raw(mode), first, count);
    }

    void glDrawElements(PrimitiveType mode, GLsizei count, DataType type, const void* indices)
    {
        detail::g_gl.DrawElements(detail::to_raw(mode), count, detail::to_raw(type), indices);
    }

    // ---- Textures ----

    void glGenTextures(GLsizei n, GLuint* textures)
    {
        detail::g_gl.GenTextures(n, textures);
    }

    void glDeleteTextures(GLsizei n, const GLuint* textures)
    {
        detail::g_gl.DeleteTextures(n, textures);
    }

    void glBindTexture(TextureTarget target, GLuint texture)
    {
        detail::g_gl.BindTexture(detail::to_raw(target), texture);
    }

    void glActiveTexture(GLuint textureUnit)
    {
        if (detail::g_gl.ActiveTexture)
            detail::g_gl.ActiveTexture(detail::GL_TEXTURE0 + textureUnit);
    }

    void glPixelStorei(GLenum pname, GLint param)
    {
        if (detail::g_gl.PixelStorei)
            detail::g_gl.PixelStorei(pname, param);
    }

    void glTexImage2D(TextureTarget target, GLint level, GLint internalformat,
                      GLsizei width, GLsizei height, GLint border,
                      PixelFormat format, PixelType type, const void* pixels)
    {
        detail::g_gl.TexImage2D(
            detail::to_raw(target), level, internalformat,
            width, height, border,
            detail::to_raw(format), detail::to_raw(type), pixels);
    }

    void glTexParameteri(TextureTarget target, TextureParameter pname, GLint param)
    {
        detail::g_gl.TexParameteri(detail::to_raw(target), detail::to_raw(pname), param);
    }

    void glTexParameteriFilter(TextureTarget target, TextureParameter pname, TextureFilter filter)
    {
        detail::g_gl.TexParameteri(detail::to_raw(target), detail::to_raw(pname), detail::to_raw(filter));
    }

    void glTexParameteriWrap(TextureTarget target, TextureParameter pname, TextureWrap wrap)
    {
        detail::g_gl.TexParameteri(detail::to_raw(target), detail::to_raw(pname), detail::to_raw(wrap));
    }

    // ---- State ----

    void glEnable(Capability cap)
    {
        if (detail::g_gl.Enable)
            detail::g_gl.Enable(detail::to_raw(cap));
    }

    void glDisable(Capability cap)
    {
        if (detail::g_gl.Disable)
            detail::g_gl.Disable(detail::to_raw(cap));
    }

    void glBlendFunc(BlendFactor sfactor, BlendFactor dfactor)
    {
        detail::g_gl.BlendFunc(detail::to_raw(sfactor), detail::to_raw(dfactor));
    }

    void glBlendFuncRaw(GLenum sfactor, GLenum dfactor)
    {
        detail::g_gl.BlendFunc(sfactor, dfactor);
    }

    void glDepthFunc(CompareFunc func)
    {
        if (detail::g_gl.DepthFunc)
            detail::g_gl.DepthFunc(detail::to_raw(func));
    }

    void glDepthMask(GLboolean flag)
    {
        if (detail::g_gl.DepthMask)
            detail::g_gl.DepthMask(flag);
    }

    void glClearDepth(GLdouble depth)
    {
        if (detail::g_gl.ClearDepth)
            detail::g_gl.ClearDepth(depth);
    }

    void glClearDepthf(GLfloat depth)
    {
        if (detail::g_gl.ClearDepthf)
            detail::g_gl.ClearDepthf(depth);
    }

    void glCullFace(CullFace mode)
    {
        if (detail::g_gl.CullFace)
            detail::g_gl.CullFace(detail::to_raw(mode));
    }

    void glFrontFace(FrontFace mode)
    {
        if (detail::g_gl.FrontFace)
            detail::g_gl.FrontFace(detail::to_raw(mode));
    }

} // namespace metagl
