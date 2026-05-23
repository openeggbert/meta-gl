#pragma once

#include "Types.hpp"

namespace metagl
{
    enum class BufferTarget
    {
        Array,
        ElementArray,
        Uniform,
        CopyRead,
        CopyWrite
    };

    enum class BufferUsage
    {
        StaticDraw,
        DynamicDraw
    };

    enum class ShaderType
    {
        Vertex,
        Fragment,
        Geometry,
        TessControl,
        TessEvaluation,
        Compute
    };

    enum class TextureTarget
    {
        Texture2D
    };

    enum class TextureParameter
    {
        MinFilter,
        MagFilter,
        WrapS,
        WrapT
    };

    enum class TextureFilter
    {
        Nearest,
        Linear
    };

    enum class TextureWrap
    {
        ClampToEdge
    };

    enum class PixelFormat
    {
        Rgba,
        Bgra
    };

    enum class PixelType
    {
        UnsignedByte
    };

    enum class PrimitiveType
    {
        Points,
        Lines,
        LineLoop,
        LineStrip,
        Triangles,
        TriangleStrip,
        TriangleFan
    };

    enum class DataType
    {
        Float,
        Byte,
        UnsignedByte,
        Short,
        UnsignedShort,
        Int,
        UnsignedInt
    };

    enum class Capability
    {
        Blend,
        DepthTest,
        ScissorTest,
        CullFace
    };

    enum class CompareFunc
    {
        Never,
        Less,
        Equal,
        LessEqual,
        Greater,
        NotEqual,
        GreaterEqual,
        Always
    };

    enum class CullFace
    {
        Front,
        Back,
        FrontAndBack
    };

    enum class FrontFace
    {
        CW,
        CCW
    };

    enum class StringName
    {
        Vendor,
        Renderer,
        Version,
        Extensions,
        ShadingLanguageVersion
    };

    enum class IntegerName
    {
        MajorVersion,
        MinorVersion,
        NumExtensions,
        MaxTextureSize,
        Viewport
    };

    enum class ShaderParameter
    {
        CompileStatus,
        InfoLogLength
    };

    enum class ProgramParameter
    {
        LinkStatus,
        InfoLogLength
    };

    enum class BlendFactor
    {
        Zero,
        One,
        SrcAlpha,
        OneMinusSrcAlpha,
        DstAlpha,
        OneMinusDstAlpha
    };

    enum class ClearBufferBit : GLbitfield
    {
        Color   = 0x00004000,
        Depth   = 0x00000100,
        Stencil = 0x00000400
    };

    inline ClearBufferBit operator|(ClearBufferBit a, ClearBufferBit b)
    {
        return static_cast<ClearBufferBit>(
            static_cast<GLbitfield>(a) | static_cast<GLbitfield>(b));
    }
}
