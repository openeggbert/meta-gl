#pragma once
// Auto-generated: enum-to-string helpers for metagl enum classes.
#include "metagl/Enums.hpp"
#include "metagl/Context.hpp"
#include <string_view>

namespace metagl
{
    inline std::string_view to_string(ClearBufferBit v)
    {
        if (v == ClearBufferBit::Color) return "Color";
        else if (v == ClearBufferBit::Depth) return "Depth";
        else if (v == ClearBufferBit::Stencil) return "Stencil";
        return "?";
    }

    inline std::string_view to_string(PrimitiveType v)
    {
        if (v == PrimitiveType::Points) return "Points";
        else if (v == PrimitiveType::Lines) return "Lines";
        else if (v == PrimitiveType::LineLoop) return "LineLoop";
        else if (v == PrimitiveType::LineStrip) return "LineStrip";
        else if (v == PrimitiveType::Triangles) return "Triangles";
        else if (v == PrimitiveType::TriangleStrip) return "TriangleStrip";
        else if (v == PrimitiveType::TriangleFan) return "TriangleFan";
        else if (v == PrimitiveType::LinesAdjacency) return "LinesAdjacency";
        else if (v == PrimitiveType::LineStripAdjacency) return "LineStripAdjacency";
        else if (v == PrimitiveType::TrianglesAdjacency) return "TrianglesAdjacency";
        else if (v == PrimitiveType::TriangleStripAdjacency) return "TriangleStripAdjacency";
        else if (v == PrimitiveType::Patches) return "Patches";
        else if (v == PrimitiveType::Quads) return "Quads";
        return "?";
    }

    inline std::string_view to_string(BlendFactor v)
    {
        if (v == BlendFactor::Zero) return "Zero";
        else if (v == BlendFactor::One) return "One";
        else if (v == BlendFactor::SrcColor) return "SrcColor";
        else if (v == BlendFactor::OneMinusSrcColor) return "OneMinusSrcColor";
        else if (v == BlendFactor::SrcAlpha) return "SrcAlpha";
        else if (v == BlendFactor::OneMinusSrcAlpha) return "OneMinusSrcAlpha";
        else if (v == BlendFactor::DstAlpha) return "DstAlpha";
        else if (v == BlendFactor::OneMinusDstAlpha) return "OneMinusDstAlpha";
        else if (v == BlendFactor::DstColor) return "DstColor";
        else if (v == BlendFactor::OneMinusDstColor) return "OneMinusDstColor";
        else if (v == BlendFactor::SrcAlphaSaturate) return "SrcAlphaSaturate";
        else if (v == BlendFactor::ConstantColor) return "ConstantColor";
        else if (v == BlendFactor::OneMinusConstantColor) return "OneMinusConstantColor";
        else if (v == BlendFactor::ConstantAlpha) return "ConstantAlpha";
        else if (v == BlendFactor::OneMinusConstantAlpha) return "OneMinusConstantAlpha";
        return "?";
    }

    inline std::string_view to_string(BlendEquation v)
    {
        if (v == BlendEquation::FuncAdd) return "FuncAdd";
        else if (v == BlendEquation::FuncSubtract) return "FuncSubtract";
        else if (v == BlendEquation::FuncReverseSubtract) return "FuncReverseSubtract";
        else if (v == BlendEquation::Min) return "Min";
        else if (v == BlendEquation::Max) return "Max";
        else if (v == BlendEquation::Multiply) return "Multiply";
        else if (v == BlendEquation::Screen) return "Screen";
        else if (v == BlendEquation::Overlay) return "Overlay";
        else if (v == BlendEquation::Darken) return "Darken";
        else if (v == BlendEquation::Lighten) return "Lighten";
        else if (v == BlendEquation::ColorDodge) return "ColorDodge";
        else if (v == BlendEquation::ColorBurn) return "ColorBurn";
        else if (v == BlendEquation::HardLight) return "HardLight";
        else if (v == BlendEquation::SoftLight) return "SoftLight";
        else if (v == BlendEquation::Difference) return "Difference";
        else if (v == BlendEquation::Exclusion) return "Exclusion";
        else if (v == BlendEquation::HslHue) return "HslHue";
        else if (v == BlendEquation::HslSaturation) return "HslSaturation";
        else if (v == BlendEquation::HslColor) return "HslColor";
        else if (v == BlendEquation::HslLuminosity) return "HslLuminosity";
        return "?";
    }

    inline std::string_view to_string(BlendMode v)
    {
        if (v == BlendMode::Multiply) return "Multiply";
        else if (v == BlendMode::Screen) return "Screen";
        else if (v == BlendMode::Overlay) return "Overlay";
        else if (v == BlendMode::Darken) return "Darken";
        else if (v == BlendMode::Lighten) return "Lighten";
        else if (v == BlendMode::ColorDodge) return "ColorDodge";
        else if (v == BlendMode::ColorBurn) return "ColorBurn";
        else if (v == BlendMode::HardLight) return "HardLight";
        else if (v == BlendMode::SoftLight) return "SoftLight";
        else if (v == BlendMode::Difference) return "Difference";
        else if (v == BlendMode::Exclusion) return "Exclusion";
        else if (v == BlendMode::HslHue) return "HslHue";
        else if (v == BlendMode::HslSaturation) return "HslSaturation";
        else if (v == BlendMode::HslColor) return "HslColor";
        else if (v == BlendMode::HslLuminosity) return "HslLuminosity";
        return "?";
    }

    inline std::string_view to_string(BufferTarget v)
    {
        if (v == BufferTarget::Array) return "Array";
        else if (v == BufferTarget::ElementArray) return "ElementArray";
        else if (v == BufferTarget::CopyRead) return "CopyRead";
        else if (v == BufferTarget::CopyWrite) return "CopyWrite";
        else if (v == BufferTarget::PixelPack) return "PixelPack";
        else if (v == BufferTarget::PixelUnpack) return "PixelUnpack";
        else if (v == BufferTarget::Uniform) return "Uniform";
        else if (v == BufferTarget::TransformFeedback) return "TransformFeedback";
        else if (v == BufferTarget::DrawIndirect) return "DrawIndirect";
        else if (v == BufferTarget::DispatchIndirect) return "DispatchIndirect";
        else if (v == BufferTarget::ShaderStorage) return "ShaderStorage";
        else if (v == BufferTarget::AtomicCounter) return "AtomicCounter";
        return "?";
    }

    inline std::string_view to_string(BufferUsage v)
    {
        if (v == BufferUsage::StreamDraw) return "StreamDraw";
        else if (v == BufferUsage::StreamRead) return "StreamRead";
        else if (v == BufferUsage::StreamCopy) return "StreamCopy";
        else if (v == BufferUsage::StaticDraw) return "StaticDraw";
        else if (v == BufferUsage::StaticRead) return "StaticRead";
        else if (v == BufferUsage::StaticCopy) return "StaticCopy";
        else if (v == BufferUsage::DynamicDraw) return "DynamicDraw";
        else if (v == BufferUsage::DynamicRead) return "DynamicRead";
        else if (v == BufferUsage::DynamicCopy) return "DynamicCopy";
        return "?";
    }

    inline std::string_view to_string(BufferParameter v)
    {
        if (v == BufferParameter::Size) return "Size";
        else if (v == BufferParameter::Usage) return "Usage";
        else if (v == BufferParameter::Mapped) return "Mapped";
        else if (v == BufferParameter::MapPointer) return "MapPointer";
        else if (v == BufferParameter::AccessFlags) return "AccessFlags";
        else if (v == BufferParameter::MapLength) return "MapLength";
        else if (v == BufferParameter::MapOffset) return "MapOffset";
        return "?";
    }

    inline std::string_view to_string(MapBufferAccessMask v)
    {
        if (v == MapBufferAccessMask::Read) return "Read";
        else if (v == MapBufferAccessMask::Write) return "Write";
        else if (v == MapBufferAccessMask::InvalidateRange) return "InvalidateRange";
        else if (v == MapBufferAccessMask::InvalidateBuffer) return "InvalidateBuffer";
        else if (v == MapBufferAccessMask::FlushExplicit) return "FlushExplicit";
        else if (v == MapBufferAccessMask::Unsynchronized) return "Unsynchronized";
        return "?";
    }

    inline std::string_view to_string(Capability v)
    {
        if (v == Capability::Blend) return "Blend";
        else if (v == Capability::CullFace) return "CullFace";
        else if (v == Capability::DepthTest) return "DepthTest";
        else if (v == Capability::Dither) return "Dither";
        else if (v == Capability::PolygonOffsetFill) return "PolygonOffsetFill";
        else if (v == Capability::SampleAlphaToCoverage) return "SampleAlphaToCoverage";
        else if (v == Capability::SampleCoverage) return "SampleCoverage";
        else if (v == Capability::ScissorTest) return "ScissorTest";
        else if (v == Capability::StencilTest) return "StencilTest";
        else if (v == Capability::RasterizerDiscard) return "RasterizerDiscard";
        else if (v == Capability::PrimitiveRestartFixedIndex) return "PrimitiveRestartFixedIndex";
        else if (v == Capability::SampleMask) return "SampleMask";
        else if (v == Capability::DebugOutput) return "DebugOutput";
        else if (v == Capability::DebugOutputSynchronous) return "DebugOutputSynchronous";
        else if (v == Capability::SampleShading) return "SampleShading";
        return "?";
    }

    inline std::string_view to_string(ErrorCode v)
    {
        if (v == ErrorCode::NoError) return "NoError";
        else if (v == ErrorCode::InvalidEnum) return "InvalidEnum";
        else if (v == ErrorCode::InvalidValue) return "InvalidValue";
        else if (v == ErrorCode::InvalidOperation) return "InvalidOperation";
        else if (v == ErrorCode::OutOfMemory) return "OutOfMemory";
        else if (v == ErrorCode::InvalidFramebufferOperation) return "InvalidFramebufferOperation";
        else if (v == ErrorCode::StackOverflow) return "StackOverflow";
        else if (v == ErrorCode::StackUnderflow) return "StackUnderflow";
        else if (v == ErrorCode::ContextLost) return "ContextLost";
        return "?";
    }

    inline std::string_view to_string(FrontFace v)
    {
        if (v == FrontFace::CW) return "CW";
        else if (v == FrontFace::CCW) return "CCW";
        return "?";
    }

    inline std::string_view to_string(CullFace v)
    {
        if (v == CullFace::Front) return "Front";
        else if (v == CullFace::Back) return "Back";
        else if (v == CullFace::FrontAndBack) return "FrontAndBack";
        return "?";
    }

    inline std::string_view to_string(HintTarget v)
    {
        if (v == HintTarget::GenerateMipmap) return "GenerateMipmap";
        else if (v == HintTarget::FragmentShaderDerivative) return "FragmentShaderDerivative";
        return "?";
    }

    inline std::string_view to_string(HintMode v)
    {
        if (v == HintMode::DontCare) return "DontCare";
        else if (v == HintMode::Fastest) return "Fastest";
        else if (v == HintMode::Nicest) return "Nicest";
        return "?";
    }

    inline std::string_view to_string(DataType v)
    {
        if (v == DataType::Byte) return "Byte";
        else if (v == DataType::UnsignedByte) return "UnsignedByte";
        else if (v == DataType::Short) return "Short";
        else if (v == DataType::UnsignedShort) return "UnsignedShort";
        else if (v == DataType::Int) return "Int";
        else if (v == DataType::UnsignedInt) return "UnsignedInt";
        else if (v == DataType::Float) return "Float";
        else if (v == DataType::Fixed) return "Fixed";
        else if (v == DataType::HalfFloat) return "HalfFloat";
        else if (v == DataType::Int2101010Rev) return "Int2101010Rev";
        else if (v == DataType::UnsignedInt2101010Rev) return "UnsignedInt2101010Rev";
        else if (v == DataType::UnsignedInt10F11F11FRev) return "UnsignedInt10F11F11FRev";
        return "?";
    }

    inline std::string_view to_string(PixelFormat v)
    {
        if (v == PixelFormat::DepthComponent) return "DepthComponent";
        else if (v == PixelFormat::Alpha) return "Alpha";
        else if (v == PixelFormat::Rgb) return "Rgb";
        else if (v == PixelFormat::Rgba) return "Rgba";
        else if (v == PixelFormat::Luminance) return "Luminance";
        else if (v == PixelFormat::LuminanceAlpha) return "LuminanceAlpha";
        else if (v == PixelFormat::Red) return "Red";
        else if (v == PixelFormat::Rg) return "Rg";
        else if (v == PixelFormat::RedInteger) return "RedInteger";
        else if (v == PixelFormat::RgInteger) return "RgInteger";
        else if (v == PixelFormat::RgbInteger) return "RgbInteger";
        else if (v == PixelFormat::RgbaInteger) return "RgbaInteger";
        else if (v == PixelFormat::DepthStencil) return "DepthStencil";
        else if (v == PixelFormat::StencilIndex) return "StencilIndex";
        else if (v == PixelFormat::Green) return "Green";
        else if (v == PixelFormat::Blue) return "Blue";
        else if (v == PixelFormat::Bgra) return "Bgra";
        return "?";
    }

    inline std::string_view to_string(PixelType v)
    {
        if (v == PixelType::UnsignedByte) return "UnsignedByte";
        else if (v == PixelType::UnsignedShort4444) return "UnsignedShort4444";
        else if (v == PixelType::UnsignedShort5551) return "UnsignedShort5551";
        else if (v == PixelType::UnsignedShort565) return "UnsignedShort565";
        else if (v == PixelType::Byte) return "Byte";
        else if (v == PixelType::Short) return "Short";
        else if (v == PixelType::UnsignedShort) return "UnsignedShort";
        else if (v == PixelType::Int) return "Int";
        else if (v == PixelType::UnsignedInt) return "UnsignedInt";
        else if (v == PixelType::HalfFloat) return "HalfFloat";
        else if (v == PixelType::Float) return "Float";
        else if (v == PixelType::UnsignedInt2101010Rev) return "UnsignedInt2101010Rev";
        else if (v == PixelType::UnsignedInt10F11F11FRev) return "UnsignedInt10F11F11FRev";
        else if (v == PixelType::UnsignedInt5999Rev) return "UnsignedInt5999Rev";
        else if (v == PixelType::UnsignedInt248) return "UnsignedInt248";
        else if (v == PixelType::Float32UnsignedInt248Rev) return "Float32UnsignedInt248Rev";
        return "?";
    }

    inline std::string_view to_string(InternalFormat v)
    {
        if (v == InternalFormat::DepthComponent) return "DepthComponent";
        else if (v == InternalFormat::Alpha) return "Alpha";
        else if (v == InternalFormat::Rgb) return "Rgb";
        else if (v == InternalFormat::Rgba) return "Rgba";
        else if (v == InternalFormat::Luminance) return "Luminance";
        else if (v == InternalFormat::LuminanceAlpha) return "LuminanceAlpha";
        else if (v == InternalFormat::Rgba4) return "Rgba4";
        else if (v == InternalFormat::Rgb5A1) return "Rgb5A1";
        else if (v == InternalFormat::Rgb565) return "Rgb565";
        else if (v == InternalFormat::DepthComponent16) return "DepthComponent16";
        else if (v == InternalFormat::StencilIndex8) return "StencilIndex8";
        else if (v == InternalFormat::R8) return "R8";
        else if (v == InternalFormat::R8Snorm) return "R8Snorm";
        else if (v == InternalFormat::R16F) return "R16F";
        else if (v == InternalFormat::R32F) return "R32F";
        else if (v == InternalFormat::R8UI) return "R8UI";
        else if (v == InternalFormat::R8I) return "R8I";
        else if (v == InternalFormat::R16UI) return "R16UI";
        else if (v == InternalFormat::R16I) return "R16I";
        else if (v == InternalFormat::R32UI) return "R32UI";
        else if (v == InternalFormat::R32I) return "R32I";
        else if (v == InternalFormat::Rg8) return "Rg8";
        else if (v == InternalFormat::Rg8Snorm) return "Rg8Snorm";
        else if (v == InternalFormat::Rg16F) return "Rg16F";
        else if (v == InternalFormat::Rg32F) return "Rg32F";
        else if (v == InternalFormat::Rg8UI) return "Rg8UI";
        else if (v == InternalFormat::Rg8I) return "Rg8I";
        else if (v == InternalFormat::Rg16UI) return "Rg16UI";
        else if (v == InternalFormat::Rg16I) return "Rg16I";
        else if (v == InternalFormat::Rg32UI) return "Rg32UI";
        else if (v == InternalFormat::Rg32I) return "Rg32I";
        else if (v == InternalFormat::Rgb8) return "Rgb8";
        else if (v == InternalFormat::Srgb8) return "Srgb8";
        else if (v == InternalFormat::Rgb8Snorm) return "Rgb8Snorm";
        else if (v == InternalFormat::R11FG11FB10F) return "R11FG11FB10F";
        else if (v == InternalFormat::Rgb9E5) return "Rgb9E5";
        else if (v == InternalFormat::Rgb16F) return "Rgb16F";
        else if (v == InternalFormat::Rgb32F) return "Rgb32F";
        else if (v == InternalFormat::Rgb8UI) return "Rgb8UI";
        else if (v == InternalFormat::Rgb8I) return "Rgb8I";
        else if (v == InternalFormat::Rgb16UI) return "Rgb16UI";
        else if (v == InternalFormat::Rgb16I) return "Rgb16I";
        else if (v == InternalFormat::Rgb32UI) return "Rgb32UI";
        else if (v == InternalFormat::Rgb32I) return "Rgb32I";
        else if (v == InternalFormat::Rgba8) return "Rgba8";
        else if (v == InternalFormat::Srgb8Alpha8) return "Srgb8Alpha8";
        else if (v == InternalFormat::Rgba8Snorm) return "Rgba8Snorm";
        else if (v == InternalFormat::Rgb10A2) return "Rgb10A2";
        else if (v == InternalFormat::Rgb10A2UI) return "Rgb10A2UI";
        else if (v == InternalFormat::Rgba16F) return "Rgba16F";
        else if (v == InternalFormat::Rgba32F) return "Rgba32F";
        else if (v == InternalFormat::Rgba8UI) return "Rgba8UI";
        else if (v == InternalFormat::Rgba8I) return "Rgba8I";
        else if (v == InternalFormat::Rgba16UI) return "Rgba16UI";
        else if (v == InternalFormat::Rgba16I) return "Rgba16I";
        else if (v == InternalFormat::Rgba32UI) return "Rgba32UI";
        else if (v == InternalFormat::Rgba32I) return "Rgba32I";
        else if (v == InternalFormat::DepthComponent24) return "DepthComponent24";
        else if (v == InternalFormat::DepthComponent32F) return "DepthComponent32F";
        else if (v == InternalFormat::Depth24Stencil8) return "Depth24Stencil8";
        else if (v == InternalFormat::Depth32FStencil8) return "Depth32FStencil8";
        return "?";
    }

    inline std::string_view to_string(CompressedInternalFormat v)
    {
        if (v == CompressedInternalFormat::R11Eac) return "R11Eac";
        else if (v == CompressedInternalFormat::SignedR11Eac) return "SignedR11Eac";
        else if (v == CompressedInternalFormat::Rg11Eac) return "Rg11Eac";
        else if (v == CompressedInternalFormat::SignedRg11Eac) return "SignedRg11Eac";
        else if (v == CompressedInternalFormat::Rgb8Etc2) return "Rgb8Etc2";
        else if (v == CompressedInternalFormat::Srgb8Etc2) return "Srgb8Etc2";
        else if (v == CompressedInternalFormat::Rgb8PunchthroughAlpha1Etc2) return "Rgb8PunchthroughAlpha1Etc2";
        else if (v == CompressedInternalFormat::Srgb8PunchthroughAlpha1Etc2) return "Srgb8PunchthroughAlpha1Etc2";
        else if (v == CompressedInternalFormat::Rgba8Etc2Eac) return "Rgba8Etc2Eac";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Etc2Eac) return "Srgb8Alpha8Etc2Eac";
        else if (v == CompressedInternalFormat::RgbaAstc4x4) return "RgbaAstc4x4";
        else if (v == CompressedInternalFormat::RgbaAstc5x4) return "RgbaAstc5x4";
        else if (v == CompressedInternalFormat::RgbaAstc5x5) return "RgbaAstc5x5";
        else if (v == CompressedInternalFormat::RgbaAstc6x5) return "RgbaAstc6x5";
        else if (v == CompressedInternalFormat::RgbaAstc6x6) return "RgbaAstc6x6";
        else if (v == CompressedInternalFormat::RgbaAstc8x5) return "RgbaAstc8x5";
        else if (v == CompressedInternalFormat::RgbaAstc8x6) return "RgbaAstc8x6";
        else if (v == CompressedInternalFormat::RgbaAstc8x8) return "RgbaAstc8x8";
        else if (v == CompressedInternalFormat::RgbaAstc10x5) return "RgbaAstc10x5";
        else if (v == CompressedInternalFormat::RgbaAstc10x6) return "RgbaAstc10x6";
        else if (v == CompressedInternalFormat::RgbaAstc10x8) return "RgbaAstc10x8";
        else if (v == CompressedInternalFormat::RgbaAstc10x10) return "RgbaAstc10x10";
        else if (v == CompressedInternalFormat::RgbaAstc12x10) return "RgbaAstc12x10";
        else if (v == CompressedInternalFormat::RgbaAstc12x12) return "RgbaAstc12x12";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc4x4) return "Srgb8Alpha8Astc4x4";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc5x4) return "Srgb8Alpha8Astc5x4";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc5x5) return "Srgb8Alpha8Astc5x5";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc6x5) return "Srgb8Alpha8Astc6x5";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc6x6) return "Srgb8Alpha8Astc6x6";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc8x5) return "Srgb8Alpha8Astc8x5";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc8x6) return "Srgb8Alpha8Astc8x6";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc8x8) return "Srgb8Alpha8Astc8x8";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc10x5) return "Srgb8Alpha8Astc10x5";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc10x6) return "Srgb8Alpha8Astc10x6";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc10x8) return "Srgb8Alpha8Astc10x8";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc10x10) return "Srgb8Alpha8Astc10x10";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc12x10) return "Srgb8Alpha8Astc12x10";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc12x12) return "Srgb8Alpha8Astc12x12";
        return "?";
    }

    inline std::string_view to_string(StringName v)
    {
        if (v == StringName::Vendor) return "Vendor";
        else if (v == StringName::Renderer) return "Renderer";
        else if (v == StringName::Version) return "Version";
        else if (v == StringName::Extensions) return "Extensions";
        else if (v == StringName::ShadingLanguageVersion) return "ShadingLanguageVersion";
        return "?";
    }

    inline std::string_view to_string(IntegerName v)
    {
        if (v == IntegerName::MajorVersion) return "MajorVersion";
        else if (v == IntegerName::MinorVersion) return "MinorVersion";
        else if (v == IntegerName::NumExtensions) return "NumExtensions";
        else if (v == IntegerName::MaxTextureSize) return "MaxTextureSize";
        else if (v == IntegerName::Viewport) return "Viewport";
        return "?";
    }

    inline std::string_view to_string(ShaderType v)
    {
        if (v == ShaderType::Vertex) return "Vertex";
        else if (v == ShaderType::Fragment) return "Fragment";
        else if (v == ShaderType::Geometry) return "Geometry";
        else if (v == ShaderType::TessControl) return "TessControl";
        else if (v == ShaderType::TessEvaluation) return "TessEvaluation";
        else if (v == ShaderType::Compute) return "Compute";
        return "?";
    }

    inline std::string_view to_string(ShaderStageMask v)
    {
        if (v == ShaderStageMask::Vertex) return "Vertex";
        else if (v == ShaderStageMask::Fragment) return "Fragment";
        else if (v == ShaderStageMask::Geometry) return "Geometry";
        else if (v == ShaderStageMask::TessControl) return "TessControl";
        else if (v == ShaderStageMask::TessEvaluation) return "TessEvaluation";
        else if (v == ShaderStageMask::Compute) return "Compute";
        else if (v == ShaderStageMask::AllShaderBits) return "AllShaderBits";
        return "?";
    }

    inline std::string_view to_string(ShaderParameter v)
    {
        if (v == ShaderParameter::ShaderType) return "ShaderType";
        else if (v == ShaderParameter::DeleteStatus) return "DeleteStatus";
        else if (v == ShaderParameter::CompileStatus) return "CompileStatus";
        else if (v == ShaderParameter::InfoLogLength) return "InfoLogLength";
        else if (v == ShaderParameter::SourceLength) return "SourceLength";
        return "?";
    }

    inline std::string_view to_string(PrecisionType v)
    {
        if (v == PrecisionType::LowFloat) return "LowFloat";
        else if (v == PrecisionType::MediumFloat) return "MediumFloat";
        else if (v == PrecisionType::HighFloat) return "HighFloat";
        else if (v == PrecisionType::LowInt) return "LowInt";
        else if (v == PrecisionType::MediumInt) return "MediumInt";
        else if (v == PrecisionType::HighInt) return "HighInt";
        return "?";
    }

    inline std::string_view to_string(ProgramParameter v)
    {
        if (v == ProgramParameter::DeleteStatus) return "DeleteStatus";
        else if (v == ProgramParameter::LinkStatus) return "LinkStatus";
        else if (v == ProgramParameter::ValidateStatus) return "ValidateStatus";
        else if (v == ProgramParameter::InfoLogLength) return "InfoLogLength";
        else if (v == ProgramParameter::AttachedShaders) return "AttachedShaders";
        else if (v == ProgramParameter::ActiveUniforms) return "ActiveUniforms";
        else if (v == ProgramParameter::ActiveUniformMaxLength) return "ActiveUniformMaxLength";
        else if (v == ProgramParameter::ActiveAttributes) return "ActiveAttributes";
        else if (v == ProgramParameter::ActiveAttributeMaxLength) return "ActiveAttributeMaxLength";
        else if (v == ProgramParameter::ActiveUniformBlocks) return "ActiveUniformBlocks";
        else if (v == ProgramParameter::ActiveUniformBlockMaxLength) return "ActiveUniformBlockMaxLength";
        else if (v == ProgramParameter::TransformFeedbackVaryings) return "TransformFeedbackVaryings";
        else if (v == ProgramParameter::TransformFeedbackVaryingMaxLength) return "TransformFeedbackVaryingMaxLength";
        else if (v == ProgramParameter::TransformFeedbackBufferMode) return "TransformFeedbackBufferMode";
        else if (v == ProgramParameter::BinaryLength) return "BinaryLength";
        else if (v == ProgramParameter::BinaryRetrievableHint) return "BinaryRetrievableHint";
        else if (v == ProgramParameter::Separable) return "Separable";
        else if (v == ProgramParameter::ActiveAtomicCounterBuffers) return "ActiveAtomicCounterBuffers";
        else if (v == ProgramParameter::ComputeWorkGroupSize) return "ComputeWorkGroupSize";
        else if (v == ProgramParameter::GeometryVerticesOut) return "GeometryVerticesOut";
        else if (v == ProgramParameter::GeometryInputType) return "GeometryInputType";
        else if (v == ProgramParameter::GeometryOutputType) return "GeometryOutputType";
        else if (v == ProgramParameter::GeometryShaderInvocations) return "GeometryShaderInvocations";
        else if (v == ProgramParameter::TessControlOutputVertices) return "TessControlOutputVertices";
        else if (v == ProgramParameter::TessGenMode) return "TessGenMode";
        else if (v == ProgramParameter::TessGenSpacing) return "TessGenSpacing";
        else if (v == ProgramParameter::TessGenVertexOrder) return "TessGenVertexOrder";
        else if (v == ProgramParameter::TessGenPointMode) return "TessGenPointMode";
        return "?";
    }

    inline std::string_view to_string(ProgramInterface v)
    {
        if (v == ProgramInterface::Uniform) return "Uniform";
        else if (v == ProgramInterface::UniformBlock) return "UniformBlock";
        else if (v == ProgramInterface::ProgramInput) return "ProgramInput";
        else if (v == ProgramInterface::ProgramOutput) return "ProgramOutput";
        else if (v == ProgramInterface::BufferVariable) return "BufferVariable";
        else if (v == ProgramInterface::ShaderStorageBlock) return "ShaderStorageBlock";
        else if (v == ProgramInterface::AtomicCounterBuffer) return "AtomicCounterBuffer";
        else if (v == ProgramInterface::TransformFeedbackVarying) return "TransformFeedbackVarying";
        return "?";
    }

    inline std::string_view to_string(ProgramInterfaceParameter v)
    {
        if (v == ProgramInterfaceParameter::ActiveResources) return "ActiveResources";
        else if (v == ProgramInterfaceParameter::MaxNameLength) return "MaxNameLength";
        else if (v == ProgramInterfaceParameter::MaxNumActiveVariables) return "MaxNumActiveVariables";
        return "?";
    }

    inline std::string_view to_string(ProgramResourceProperty v)
    {
        if (v == ProgramResourceProperty::NameLength) return "NameLength";
        else if (v == ProgramResourceProperty::Type) return "Type";
        else if (v == ProgramResourceProperty::ArraySize) return "ArraySize";
        else if (v == ProgramResourceProperty::Offset) return "Offset";
        else if (v == ProgramResourceProperty::BlockIndex) return "BlockIndex";
        else if (v == ProgramResourceProperty::ArrayStride) return "ArrayStride";
        else if (v == ProgramResourceProperty::MatrixStride) return "MatrixStride";
        else if (v == ProgramResourceProperty::IsRowMajor) return "IsRowMajor";
        else if (v == ProgramResourceProperty::AtomicCounterBufferIndex) return "AtomicCounterBufferIndex";
        else if (v == ProgramResourceProperty::BufferBinding) return "BufferBinding";
        else if (v == ProgramResourceProperty::BufferDataSize) return "BufferDataSize";
        else if (v == ProgramResourceProperty::NumActiveVariables) return "NumActiveVariables";
        else if (v == ProgramResourceProperty::ActiveVariables) return "ActiveVariables";
        else if (v == ProgramResourceProperty::ReferencedByVertexShader) return "ReferencedByVertexShader";
        else if (v == ProgramResourceProperty::ReferencedByFragmentShader) return "ReferencedByFragmentShader";
        else if (v == ProgramResourceProperty::ReferencedByComputeShader) return "ReferencedByComputeShader";
        else if (v == ProgramResourceProperty::ReferencedByGeometryShader) return "ReferencedByGeometryShader";
        else if (v == ProgramResourceProperty::ReferencedByTessControlShader) return "ReferencedByTessControlShader";
        else if (v == ProgramResourceProperty::ReferencedByTessEvaluationShader) return "ReferencedByTessEvaluationShader";
        else if (v == ProgramResourceProperty::TopLevelArraySize) return "TopLevelArraySize";
        else if (v == ProgramResourceProperty::TopLevelArrayStride) return "TopLevelArrayStride";
        else if (v == ProgramResourceProperty::Location) return "Location";
        else if (v == ProgramResourceProperty::IsPerPatch) return "IsPerPatch";
        return "?";
    }

    inline std::string_view to_string(UniformType v)
    {
        if (v == UniformType::Float) return "Float";
        else if (v == UniformType::FloatVec2) return "FloatVec2";
        else if (v == UniformType::FloatVec3) return "FloatVec3";
        else if (v == UniformType::FloatVec4) return "FloatVec4";
        else if (v == UniformType::Int) return "Int";
        else if (v == UniformType::IntVec2) return "IntVec2";
        else if (v == UniformType::IntVec3) return "IntVec3";
        else if (v == UniformType::IntVec4) return "IntVec4";
        else if (v == UniformType::UnsignedInt) return "UnsignedInt";
        else if (v == UniformType::UnsignedIntVec2) return "UnsignedIntVec2";
        else if (v == UniformType::UnsignedIntVec3) return "UnsignedIntVec3";
        else if (v == UniformType::UnsignedIntVec4) return "UnsignedIntVec4";
        else if (v == UniformType::Bool) return "Bool";
        else if (v == UniformType::BoolVec2) return "BoolVec2";
        else if (v == UniformType::BoolVec3) return "BoolVec3";
        else if (v == UniformType::BoolVec4) return "BoolVec4";
        else if (v == UniformType::FloatMat2) return "FloatMat2";
        else if (v == UniformType::FloatMat3) return "FloatMat3";
        else if (v == UniformType::FloatMat4) return "FloatMat4";
        else if (v == UniformType::FloatMat2x3) return "FloatMat2x3";
        else if (v == UniformType::FloatMat2x4) return "FloatMat2x4";
        else if (v == UniformType::FloatMat3x2) return "FloatMat3x2";
        else if (v == UniformType::FloatMat3x4) return "FloatMat3x4";
        else if (v == UniformType::FloatMat4x2) return "FloatMat4x2";
        else if (v == UniformType::FloatMat4x3) return "FloatMat4x3";
        else if (v == UniformType::Sampler2D) return "Sampler2D";
        else if (v == UniformType::Sampler3D) return "Sampler3D";
        else if (v == UniformType::SamplerCube) return "SamplerCube";
        else if (v == UniformType::Sampler2DShadow) return "Sampler2DShadow";
        else if (v == UniformType::Sampler2DArray) return "Sampler2DArray";
        else if (v == UniformType::Sampler2DArrayShadow) return "Sampler2DArrayShadow";
        else if (v == UniformType::SamplerCubeShadow) return "SamplerCubeShadow";
        else if (v == UniformType::IntSampler2D) return "IntSampler2D";
        else if (v == UniformType::IntSampler3D) return "IntSampler3D";
        else if (v == UniformType::IntSamplerCube) return "IntSamplerCube";
        else if (v == UniformType::IntSampler2DArray) return "IntSampler2DArray";
        else if (v == UniformType::UnsignedIntSampler2D) return "UnsignedIntSampler2D";
        else if (v == UniformType::UnsignedIntSampler3D) return "UnsignedIntSampler3D";
        else if (v == UniformType::UnsignedIntSamplerCube) return "UnsignedIntSamplerCube";
        else if (v == UniformType::UnsignedIntSampler2DArray) return "UnsignedIntSampler2DArray";
        else if (v == UniformType::Sampler2DMultisample) return "Sampler2DMultisample";
        else if (v == UniformType::IntSampler2DMultisample) return "IntSampler2DMultisample";
        else if (v == UniformType::UnsignedIntSampler2DMultisample) return "UnsignedIntSampler2DMultisample";
        else if (v == UniformType::UnsignedIntAtomicCounter) return "UnsignedIntAtomicCounter";
        else if (v == UniformType::Image2D) return "Image2D";
        else if (v == UniformType::Image3D) return "Image3D";
        else if (v == UniformType::ImageCube) return "ImageCube";
        else if (v == UniformType::Image2DArray) return "Image2DArray";
        else if (v == UniformType::IntImage2D) return "IntImage2D";
        else if (v == UniformType::IntImage3D) return "IntImage3D";
        else if (v == UniformType::IntImageCube) return "IntImageCube";
        else if (v == UniformType::IntImage2DArray) return "IntImage2DArray";
        else if (v == UniformType::UnsignedIntImage2D) return "UnsignedIntImage2D";
        else if (v == UniformType::UnsignedIntImage3D) return "UnsignedIntImage3D";
        else if (v == UniformType::UnsignedIntImageCube) return "UnsignedIntImageCube";
        else if (v == UniformType::UnsignedIntImage2DArray) return "UnsignedIntImage2DArray";
        else if (v == UniformType::SamplerBuffer) return "SamplerBuffer";
        else if (v == UniformType::IntSamplerBuffer) return "IntSamplerBuffer";
        else if (v == UniformType::UnsignedIntSamplerBuffer) return "UnsignedIntSamplerBuffer";
        else if (v == UniformType::ImageBuffer) return "ImageBuffer";
        else if (v == UniformType::IntImageBuffer) return "IntImageBuffer";
        else if (v == UniformType::UnsignedIntImageBuffer) return "UnsignedIntImageBuffer";
        else if (v == UniformType::SamplerCubeMapArray) return "SamplerCubeMapArray";
        else if (v == UniformType::SamplerCubeMapArrayShadow) return "SamplerCubeMapArrayShadow";
        else if (v == UniformType::IntSamplerCubeMapArray) return "IntSamplerCubeMapArray";
        else if (v == UniformType::UnsignedIntSamplerCubeMapArray) return "UnsignedIntSamplerCubeMapArray";
        else if (v == UniformType::ImageCubeMapArray) return "ImageCubeMapArray";
        else if (v == UniformType::IntImageCubeMapArray) return "IntImageCubeMapArray";
        else if (v == UniformType::UnsignedIntImageCubeMapArray) return "UnsignedIntImageCubeMapArray";
        else if (v == UniformType::Sampler2DMultisampleArray) return "Sampler2DMultisampleArray";
        else if (v == UniformType::IntSampler2DMultisampleArray) return "IntSampler2DMultisampleArray";
        else if (v == UniformType::UnsignedIntSampler2DMultisampleArray) return "UnsignedIntSampler2DMultisampleArray";
        return "?";
    }

    inline std::string_view to_string(UniformBlockParameter v)
    {
        if (v == UniformBlockParameter::Binding) return "Binding";
        else if (v == UniformBlockParameter::DataSize) return "DataSize";
        else if (v == UniformBlockParameter::NameLength) return "NameLength";
        else if (v == UniformBlockParameter::ActiveUniforms) return "ActiveUniforms";
        else if (v == UniformBlockParameter::ActiveUniformIndices) return "ActiveUniformIndices";
        else if (v == UniformBlockParameter::ReferencedByVertexShader) return "ReferencedByVertexShader";
        else if (v == UniformBlockParameter::ReferencedByFragmentShader) return "ReferencedByFragmentShader";
        return "?";
    }

    inline std::string_view to_string(UniformParameter v)
    {
        if (v == UniformParameter::Type) return "Type";
        else if (v == UniformParameter::Size) return "Size";
        else if (v == UniformParameter::NameLength) return "NameLength";
        else if (v == UniformParameter::BlockIndex) return "BlockIndex";
        else if (v == UniformParameter::Offset) return "Offset";
        else if (v == UniformParameter::ArrayStride) return "ArrayStride";
        else if (v == UniformParameter::MatrixStride) return "MatrixStride";
        else if (v == UniformParameter::IsRowMajor) return "IsRowMajor";
        return "?";
    }

    inline std::string_view to_string(TextureTarget v)
    {
        if (v == TextureTarget::Texture2D) return "Texture2D";
        else if (v == TextureTarget::TextureCubeMap) return "TextureCubeMap";
        else if (v == TextureTarget::TextureCubeMapPositiveX) return "TextureCubeMapPositiveX";
        else if (v == TextureTarget::TextureCubeMapNegativeX) return "TextureCubeMapNegativeX";
        else if (v == TextureTarget::TextureCubeMapPositiveY) return "TextureCubeMapPositiveY";
        else if (v == TextureTarget::TextureCubeMapNegativeY) return "TextureCubeMapNegativeY";
        else if (v == TextureTarget::TextureCubeMapPositiveZ) return "TextureCubeMapPositiveZ";
        else if (v == TextureTarget::TextureCubeMapNegativeZ) return "TextureCubeMapNegativeZ";
        else if (v == TextureTarget::Texture3D) return "Texture3D";
        else if (v == TextureTarget::Texture2DArray) return "Texture2DArray";
        else if (v == TextureTarget::Texture2DMultisample) return "Texture2DMultisample";
        else if (v == TextureTarget::TextureBuffer) return "TextureBuffer";
        else if (v == TextureTarget::TextureCubeMapArray) return "TextureCubeMapArray";
        else if (v == TextureTarget::Texture2DMultisampleArray) return "Texture2DMultisampleArray";
        return "?";
    }

    inline std::string_view to_string(TextureParameter v)
    {
        if (v == TextureParameter::MinFilter) return "MinFilter";
        else if (v == TextureParameter::MagFilter) return "MagFilter";
        else if (v == TextureParameter::WrapS) return "WrapS";
        else if (v == TextureParameter::WrapT) return "WrapT";
        else if (v == TextureParameter::WrapR) return "WrapR";
        else if (v == TextureParameter::MinLod) return "MinLod";
        else if (v == TextureParameter::MaxLod) return "MaxLod";
        else if (v == TextureParameter::BaseLevel) return "BaseLevel";
        else if (v == TextureParameter::MaxLevel) return "MaxLevel";
        else if (v == TextureParameter::CompareMode) return "CompareMode";
        else if (v == TextureParameter::CompareFunc) return "CompareFunc";
        else if (v == TextureParameter::SwizzleR) return "SwizzleR";
        else if (v == TextureParameter::SwizzleG) return "SwizzleG";
        else if (v == TextureParameter::SwizzleB) return "SwizzleB";
        else if (v == TextureParameter::SwizzleA) return "SwizzleA";
        else if (v == TextureParameter::ImmutableFormat) return "ImmutableFormat";
        else if (v == TextureParameter::ImmutableLevels) return "ImmutableLevels";
        else if (v == TextureParameter::Samples) return "Samples";
        else if (v == TextureParameter::FixedSampleLocations) return "FixedSampleLocations";
        else if (v == TextureParameter::DepthStencilTextureMode) return "DepthStencilTextureMode";
        else if (v == TextureParameter::ImageFormatCompatibilityType) return "ImageFormatCompatibilityType";
        else if (v == TextureParameter::BorderColor) return "BorderColor";
        else if (v == TextureParameter::BufferDataStoreBinding) return "BufferDataStoreBinding";
        else if (v == TextureParameter::BufferOffset) return "BufferOffset";
        else if (v == TextureParameter::BufferSize) return "BufferSize";
        return "?";
    }

    inline std::string_view to_string(TextureMinFilter v)
    {
        if (v == TextureMinFilter::Nearest) return "Nearest";
        else if (v == TextureMinFilter::Linear) return "Linear";
        else if (v == TextureMinFilter::NearestMipmapNearest) return "NearestMipmapNearest";
        else if (v == TextureMinFilter::LinearMipmapNearest) return "LinearMipmapNearest";
        else if (v == TextureMinFilter::NearestMipmapLinear) return "NearestMipmapLinear";
        else if (v == TextureMinFilter::LinearMipmapLinear) return "LinearMipmapLinear";
        return "?";
    }

    inline std::string_view to_string(TextureMagFilter v)
    {
        if (v == TextureMagFilter::Nearest) return "Nearest";
        else if (v == TextureMagFilter::Linear) return "Linear";
        return "?";
    }

    inline std::string_view to_string(TextureFilter v)
    {
        if (v == TextureFilter::Nearest) return "Nearest";
        else if (v == TextureFilter::Linear) return "Linear";
        return "?";
    }

    inline std::string_view to_string(TextureWrapMode v)
    {
        if (v == TextureWrapMode::Repeat) return "Repeat";
        else if (v == TextureWrapMode::ClampToEdge) return "ClampToEdge";
        else if (v == TextureWrapMode::MirroredRepeat) return "MirroredRepeat";
        else if (v == TextureWrapMode::ClampToBorder) return "ClampToBorder";
        return "?";
    }

    inline std::string_view to_string(TextureWrap v)
    {
        if (v == TextureWrap::ClampToEdge) return "ClampToEdge";
        else if (v == TextureWrap::Repeat) return "Repeat";
        else if (v == TextureWrap::MirroredRepeat) return "MirroredRepeat";
        else if (v == TextureWrap::ClampToBorder) return "ClampToBorder";
        return "?";
    }

    inline std::string_view to_string(TextureCompareMode v)
    {
        if (v == TextureCompareMode::None) return "None";
        else if (v == TextureCompareMode::CompareRefToTexture) return "CompareRefToTexture";
        return "?";
    }

    inline std::string_view to_string(TextureSwizzle v)
    {
        if (v == TextureSwizzle::Red) return "Red";
        else if (v == TextureSwizzle::Green) return "Green";
        else if (v == TextureSwizzle::Blue) return "Blue";
        else if (v == TextureSwizzle::Alpha) return "Alpha";
        else if (v == TextureSwizzle::Zero) return "Zero";
        else if (v == TextureSwizzle::One) return "One";
        return "?";
    }

    inline std::string_view to_string(TextureLevelParameter v)
    {
        if (v == TextureLevelParameter::Width) return "Width";
        else if (v == TextureLevelParameter::Height) return "Height";
        else if (v == TextureLevelParameter::Depth) return "Depth";
        else if (v == TextureLevelParameter::InternalFormat) return "InternalFormat";
        else if (v == TextureLevelParameter::RedSize) return "RedSize";
        else if (v == TextureLevelParameter::GreenSize) return "GreenSize";
        else if (v == TextureLevelParameter::BlueSize) return "BlueSize";
        else if (v == TextureLevelParameter::AlphaSize) return "AlphaSize";
        else if (v == TextureLevelParameter::DepthSize) return "DepthSize";
        else if (v == TextureLevelParameter::StencilSize) return "StencilSize";
        else if (v == TextureLevelParameter::SharedSize) return "SharedSize";
        else if (v == TextureLevelParameter::RedType) return "RedType";
        else if (v == TextureLevelParameter::GreenType) return "GreenType";
        else if (v == TextureLevelParameter::BlueType) return "BlueType";
        else if (v == TextureLevelParameter::AlphaType) return "AlphaType";
        else if (v == TextureLevelParameter::DepthType) return "DepthType";
        else if (v == TextureLevelParameter::Compressed) return "Compressed";
        return "?";
    }

    inline std::string_view to_string(TextureUnit v)
    {
        if (v == TextureUnit::Texture0) return "Texture0";
        else if (v == TextureUnit::Texture1) return "Texture1";
        else if (v == TextureUnit::Texture2) return "Texture2";
        else if (v == TextureUnit::Texture3) return "Texture3";
        else if (v == TextureUnit::Texture4) return "Texture4";
        else if (v == TextureUnit::Texture5) return "Texture5";
        else if (v == TextureUnit::Texture6) return "Texture6";
        else if (v == TextureUnit::Texture7) return "Texture7";
        else if (v == TextureUnit::Texture8) return "Texture8";
        else if (v == TextureUnit::Texture9) return "Texture9";
        else if (v == TextureUnit::Texture10) return "Texture10";
        else if (v == TextureUnit::Texture11) return "Texture11";
        else if (v == TextureUnit::Texture12) return "Texture12";
        else if (v == TextureUnit::Texture13) return "Texture13";
        else if (v == TextureUnit::Texture14) return "Texture14";
        else if (v == TextureUnit::Texture15) return "Texture15";
        else if (v == TextureUnit::Texture16) return "Texture16";
        else if (v == TextureUnit::Texture17) return "Texture17";
        else if (v == TextureUnit::Texture18) return "Texture18";
        else if (v == TextureUnit::Texture19) return "Texture19";
        else if (v == TextureUnit::Texture20) return "Texture20";
        else if (v == TextureUnit::Texture21) return "Texture21";
        else if (v == TextureUnit::Texture22) return "Texture22";
        else if (v == TextureUnit::Texture23) return "Texture23";
        else if (v == TextureUnit::Texture24) return "Texture24";
        else if (v == TextureUnit::Texture25) return "Texture25";
        else if (v == TextureUnit::Texture26) return "Texture26";
        else if (v == TextureUnit::Texture27) return "Texture27";
        else if (v == TextureUnit::Texture28) return "Texture28";
        else if (v == TextureUnit::Texture29) return "Texture29";
        else if (v == TextureUnit::Texture30) return "Texture30";
        else if (v == TextureUnit::Texture31) return "Texture31";
        return "?";
    }

    inline std::string_view to_string(PixelStoreParam v)
    {
        if (v == PixelStoreParam::PackAlignment) return "PackAlignment";
        else if (v == PixelStoreParam::PackRowLength) return "PackRowLength";
        else if (v == PixelStoreParam::PackSkipRows) return "PackSkipRows";
        else if (v == PixelStoreParam::PackSkipPixels) return "PackSkipPixels";
        else if (v == PixelStoreParam::UnpackAlignment) return "UnpackAlignment";
        else if (v == PixelStoreParam::UnpackRowLength) return "UnpackRowLength";
        else if (v == PixelStoreParam::UnpackSkipRows) return "UnpackSkipRows";
        else if (v == PixelStoreParam::UnpackSkipPixels) return "UnpackSkipPixels";
        else if (v == PixelStoreParam::UnpackSkipImages) return "UnpackSkipImages";
        else if (v == PixelStoreParam::UnpackImageHeight) return "UnpackImageHeight";
        return "?";
    }

    inline std::string_view to_string(CompareFunc v)
    {
        if (v == CompareFunc::Never) return "Never";
        else if (v == CompareFunc::Less) return "Less";
        else if (v == CompareFunc::Equal) return "Equal";
        else if (v == CompareFunc::Lequal) return "Lequal";
        else if (v == CompareFunc::Greater) return "Greater";
        else if (v == CompareFunc::Notequal) return "Notequal";
        else if (v == CompareFunc::Gequal) return "Gequal";
        else if (v == CompareFunc::Always) return "Always";
        return "?";
    }

    inline std::string_view to_string(StencilOp v)
    {
        if (v == StencilOp::Keep) return "Keep";
        else if (v == StencilOp::Zero) return "Zero";
        else if (v == StencilOp::Replace) return "Replace";
        else if (v == StencilOp::Incr) return "Incr";
        else if (v == StencilOp::Decr) return "Decr";
        else if (v == StencilOp::Invert) return "Invert";
        else if (v == StencilOp::IncrWrap) return "IncrWrap";
        else if (v == StencilOp::DecrWrap) return "DecrWrap";
        return "?";
    }

    inline std::string_view to_string(FramebufferTarget v)
    {
        if (v == FramebufferTarget::Framebuffer) return "Framebuffer";
        else if (v == FramebufferTarget::DrawFramebuffer) return "DrawFramebuffer";
        else if (v == FramebufferTarget::ReadFramebuffer) return "ReadFramebuffer";
        return "?";
    }

    inline std::string_view to_string(RenderbufferTarget v)
    {
        if (v == RenderbufferTarget::Renderbuffer) return "Renderbuffer";
        return "?";
    }

    inline std::string_view to_string(FramebufferAttachment v)
    {
        if (v == FramebufferAttachment::None) return "None";
        else if (v == FramebufferAttachment::Color0) return "Color0";
        else if (v == FramebufferAttachment::Color1) return "Color1";
        else if (v == FramebufferAttachment::Color2) return "Color2";
        else if (v == FramebufferAttachment::Color3) return "Color3";
        else if (v == FramebufferAttachment::Color4) return "Color4";
        else if (v == FramebufferAttachment::Color5) return "Color5";
        else if (v == FramebufferAttachment::Color6) return "Color6";
        else if (v == FramebufferAttachment::Color7) return "Color7";
        else if (v == FramebufferAttachment::Color8) return "Color8";
        else if (v == FramebufferAttachment::Color9) return "Color9";
        else if (v == FramebufferAttachment::Color10) return "Color10";
        else if (v == FramebufferAttachment::Color11) return "Color11";
        else if (v == FramebufferAttachment::Color12) return "Color12";
        else if (v == FramebufferAttachment::Color13) return "Color13";
        else if (v == FramebufferAttachment::Color14) return "Color14";
        else if (v == FramebufferAttachment::Color15) return "Color15";
        else if (v == FramebufferAttachment::Color16) return "Color16";
        else if (v == FramebufferAttachment::Color17) return "Color17";
        else if (v == FramebufferAttachment::Color18) return "Color18";
        else if (v == FramebufferAttachment::Color19) return "Color19";
        else if (v == FramebufferAttachment::Color20) return "Color20";
        else if (v == FramebufferAttachment::Color21) return "Color21";
        else if (v == FramebufferAttachment::Color22) return "Color22";
        else if (v == FramebufferAttachment::Color23) return "Color23";
        else if (v == FramebufferAttachment::Color24) return "Color24";
        else if (v == FramebufferAttachment::Color25) return "Color25";
        else if (v == FramebufferAttachment::Color26) return "Color26";
        else if (v == FramebufferAttachment::Color27) return "Color27";
        else if (v == FramebufferAttachment::Color28) return "Color28";
        else if (v == FramebufferAttachment::Color29) return "Color29";
        else if (v == FramebufferAttachment::Color30) return "Color30";
        else if (v == FramebufferAttachment::Color31) return "Color31";
        else if (v == FramebufferAttachment::Depth) return "Depth";
        else if (v == FramebufferAttachment::Stencil) return "Stencil";
        else if (v == FramebufferAttachment::DepthStencil) return "DepthStencil";
        return "?";
    }

    inline std::string_view to_string(FramebufferStatus v)
    {
        if (v == FramebufferStatus::Complete) return "Complete";
        else if (v == FramebufferStatus::Undefined) return "Undefined";
        else if (v == FramebufferStatus::IncompleteAttachment) return "IncompleteAttachment";
        else if (v == FramebufferStatus::IncompleteMissingAttachment) return "IncompleteMissingAttachment";
        else if (v == FramebufferStatus::IncompleteDimensions) return "IncompleteDimensions";
        else if (v == FramebufferStatus::Unsupported) return "Unsupported";
        else if (v == FramebufferStatus::IncompleteMultisample) return "IncompleteMultisample";
        else if (v == FramebufferStatus::IncompleteLayerTargets) return "IncompleteLayerTargets";
        return "?";
    }

    inline std::string_view to_string(FramebufferAttachmentParameter v)
    {
        if (v == FramebufferAttachmentParameter::ObjectType) return "ObjectType";
        else if (v == FramebufferAttachmentParameter::ObjectName) return "ObjectName";
        else if (v == FramebufferAttachmentParameter::TextureLevel) return "TextureLevel";
        else if (v == FramebufferAttachmentParameter::TextureCubeMapFace) return "TextureCubeMapFace";
        else if (v == FramebufferAttachmentParameter::ColorEncoding) return "ColorEncoding";
        else if (v == FramebufferAttachmentParameter::ComponentType) return "ComponentType";
        else if (v == FramebufferAttachmentParameter::RedSize) return "RedSize";
        else if (v == FramebufferAttachmentParameter::GreenSize) return "GreenSize";
        else if (v == FramebufferAttachmentParameter::BlueSize) return "BlueSize";
        else if (v == FramebufferAttachmentParameter::AlphaSize) return "AlphaSize";
        else if (v == FramebufferAttachmentParameter::DepthSize) return "DepthSize";
        else if (v == FramebufferAttachmentParameter::StencilSize) return "StencilSize";
        else if (v == FramebufferAttachmentParameter::TextureLayer) return "TextureLayer";
        else if (v == FramebufferAttachmentParameter::Layered) return "Layered";
        return "?";
    }

    inline std::string_view to_string(FramebufferDefaultParameter v)
    {
        if (v == FramebufferDefaultParameter::Width) return "Width";
        else if (v == FramebufferDefaultParameter::Height) return "Height";
        else if (v == FramebufferDefaultParameter::Samples) return "Samples";
        else if (v == FramebufferDefaultParameter::FixedSampleLocations) return "FixedSampleLocations";
        else if (v == FramebufferDefaultParameter::Layers) return "Layers";
        return "?";
    }

    inline std::string_view to_string(RenderbufferParameter v)
    {
        if (v == RenderbufferParameter::Width) return "Width";
        else if (v == RenderbufferParameter::Height) return "Height";
        else if (v == RenderbufferParameter::InternalFormat) return "InternalFormat";
        else if (v == RenderbufferParameter::RedSize) return "RedSize";
        else if (v == RenderbufferParameter::GreenSize) return "GreenSize";
        else if (v == RenderbufferParameter::BlueSize) return "BlueSize";
        else if (v == RenderbufferParameter::AlphaSize) return "AlphaSize";
        else if (v == RenderbufferParameter::DepthSize) return "DepthSize";
        else if (v == RenderbufferParameter::StencilSize) return "StencilSize";
        else if (v == RenderbufferParameter::Samples) return "Samples";
        return "?";
    }

    inline std::string_view to_string(VertexAttribParameter v)
    {
        if (v == VertexAttribParameter::ArrayEnabled) return "ArrayEnabled";
        else if (v == VertexAttribParameter::ArraySize) return "ArraySize";
        else if (v == VertexAttribParameter::ArrayStride) return "ArrayStride";
        else if (v == VertexAttribParameter::ArrayType) return "ArrayType";
        else if (v == VertexAttribParameter::ArrayNormalized) return "ArrayNormalized";
        else if (v == VertexAttribParameter::ArrayPointer) return "ArrayPointer";
        else if (v == VertexAttribParameter::ArrayBufferBinding) return "ArrayBufferBinding";
        else if (v == VertexAttribParameter::CurrentVertexAttrib) return "CurrentVertexAttrib";
        else if (v == VertexAttribParameter::ArrayInteger) return "ArrayInteger";
        else if (v == VertexAttribParameter::ArrayDivisor) return "ArrayDivisor";
        else if (v == VertexAttribParameter::Binding) return "Binding";
        else if (v == VertexAttribParameter::RelativeOffset) return "RelativeOffset";
        return "?";
    }

    inline std::string_view to_string(TransformFeedbackBufferMode v)
    {
        if (v == TransformFeedbackBufferMode::InterleavedAttribs) return "InterleavedAttribs";
        else if (v == TransformFeedbackBufferMode::SeparateAttribs) return "SeparateAttribs";
        return "?";
    }

    inline std::string_view to_string(TransformFeedbackTarget v)
    {
        if (v == TransformFeedbackTarget::TransformFeedback) return "TransformFeedback";
        return "?";
    }

    inline std::string_view to_string(QueryTarget v)
    {
        if (v == QueryTarget::AnySamplesPassed) return "AnySamplesPassed";
        else if (v == QueryTarget::AnySamplesPassedConservative) return "AnySamplesPassedConservative";
        else if (v == QueryTarget::TransformFeedbackPrimitivesWritten) return "TransformFeedbackPrimitivesWritten";
        else if (v == QueryTarget::PrimitivesGenerated) return "PrimitivesGenerated";
        return "?";
    }

    inline std::string_view to_string(QueryParameter v)
    {
        if (v == QueryParameter::CurrentQuery) return "CurrentQuery";
        return "?";
    }

    inline std::string_view to_string(QueryObjectParameter v)
    {
        if (v == QueryObjectParameter::Result) return "Result";
        else if (v == QueryObjectParameter::ResultAvailable) return "ResultAvailable";
        return "?";
    }

    inline std::string_view to_string(SyncCondition v)
    {
        if (v == SyncCondition::GpuCommandsComplete) return "GpuCommandsComplete";
        return "?";
    }

    inline std::string_view to_string(SyncParameter v)
    {
        if (v == SyncParameter::ObjectType) return "ObjectType";
        else if (v == SyncParameter::Condition) return "Condition";
        else if (v == SyncParameter::Status) return "Status";
        else if (v == SyncParameter::Flags) return "Flags";
        return "?";
    }

    inline std::string_view to_string(SyncWaitResult v)
    {
        if (v == SyncWaitResult::AlreadySignaled) return "AlreadySignaled";
        else if (v == SyncWaitResult::TimeoutExpired) return "TimeoutExpired";
        else if (v == SyncWaitResult::ConditionSatisfied) return "ConditionSatisfied";
        else if (v == SyncWaitResult::WaitFailed) return "WaitFailed";
        return "?";
    }

    inline std::string_view to_string(SyncFlushMask v)
    {
        if (v == SyncFlushMask::None) return "None";
        else if (v == SyncFlushMask::Commands) return "Commands";
        return "?";
    }

    inline std::string_view to_string(ImageAccess v)
    {
        if (v == ImageAccess::ReadOnly) return "ReadOnly";
        else if (v == ImageAccess::WriteOnly) return "WriteOnly";
        else if (v == ImageAccess::ReadWrite) return "ReadWrite";
        return "?";
    }

    inline std::string_view to_string(MemoryBarrierMask v)
    {
        if (v == MemoryBarrierMask::VertexAttribArray) return "VertexAttribArray";
        else if (v == MemoryBarrierMask::ElementArray) return "ElementArray";
        else if (v == MemoryBarrierMask::Uniform) return "Uniform";
        else if (v == MemoryBarrierMask::TextureFetch) return "TextureFetch";
        else if (v == MemoryBarrierMask::ShaderImageAccess) return "ShaderImageAccess";
        else if (v == MemoryBarrierMask::Command) return "Command";
        else if (v == MemoryBarrierMask::PixelBuffer) return "PixelBuffer";
        else if (v == MemoryBarrierMask::TextureUpdate) return "TextureUpdate";
        else if (v == MemoryBarrierMask::BufferUpdate) return "BufferUpdate";
        else if (v == MemoryBarrierMask::Framebuffer) return "Framebuffer";
        else if (v == MemoryBarrierMask::TransformFeedback) return "TransformFeedback";
        else if (v == MemoryBarrierMask::AtomicCounter) return "AtomicCounter";
        else if (v == MemoryBarrierMask::ShaderStorage) return "ShaderStorage";
        else if (v == MemoryBarrierMask::AllBarrierBits) return "AllBarrierBits";
        return "?";
    }

    inline std::string_view to_string(ContextFlagMask v)
    {
        if (v == ContextFlagMask::Debug) return "Debug";
        else if (v == ContextFlagMask::RobustAccess) return "RobustAccess";
        return "?";
    }

    inline std::string_view to_string(GraphicsResetStatus v)
    {
        if (v == GraphicsResetStatus::NoError) return "NoError";
        else if (v == GraphicsResetStatus::Guilty) return "Guilty";
        else if (v == GraphicsResetStatus::Innocent) return "Innocent";
        else if (v == GraphicsResetStatus::Unknown) return "Unknown";
        return "?";
    }

    inline std::string_view to_string(ResetNotificationStrategy v)
    {
        if (v == ResetNotificationStrategy::NoResetNotification) return "NoResetNotification";
        else if (v == ResetNotificationStrategy::LoseContextOnReset) return "LoseContextOnReset";
        return "?";
    }

    inline std::string_view to_string(DebugSource v)
    {
        if (v == DebugSource::DontCare) return "DontCare";
        else if (v == DebugSource::Api) return "Api";
        else if (v == DebugSource::WindowSystem) return "WindowSystem";
        else if (v == DebugSource::ShaderCompiler) return "ShaderCompiler";
        else if (v == DebugSource::ThirdParty) return "ThirdParty";
        else if (v == DebugSource::Application) return "Application";
        else if (v == DebugSource::Other) return "Other";
        return "?";
    }

    inline std::string_view to_string(DebugType v)
    {
        if (v == DebugType::DontCare) return "DontCare";
        else if (v == DebugType::Error) return "Error";
        else if (v == DebugType::DeprecatedBehavior) return "DeprecatedBehavior";
        else if (v == DebugType::UndefinedBehavior) return "UndefinedBehavior";
        else if (v == DebugType::Portability) return "Portability";
        else if (v == DebugType::Performance) return "Performance";
        else if (v == DebugType::Other) return "Other";
        else if (v == DebugType::Marker) return "Marker";
        else if (v == DebugType::PushGroup) return "PushGroup";
        else if (v == DebugType::PopGroup) return "PopGroup";
        return "?";
    }

    inline std::string_view to_string(DebugSeverity v)
    {
        if (v == DebugSeverity::DontCare) return "DontCare";
        else if (v == DebugSeverity::High) return "High";
        else if (v == DebugSeverity::Medium) return "Medium";
        else if (v == DebugSeverity::Low) return "Low";
        else if (v == DebugSeverity::Notification) return "Notification";
        return "?";
    }

    inline std::string_view to_string(DebugObjectLabel v)
    {
        if (v == DebugObjectLabel::Buffer) return "Buffer";
        else if (v == DebugObjectLabel::Shader) return "Shader";
        else if (v == DebugObjectLabel::Program) return "Program";
        else if (v == DebugObjectLabel::VertexArray) return "VertexArray";
        else if (v == DebugObjectLabel::Query) return "Query";
        else if (v == DebugObjectLabel::ProgramPipeline) return "ProgramPipeline";
        else if (v == DebugObjectLabel::Sampler) return "Sampler";
        return "?";
    }

    inline std::string_view to_string(ProvokingVertex v)
    {
        if (v == ProvokingVertex::FirstVertex) return "FirstVertex";
        else if (v == ProvokingVertex::LastVertex) return "LastVertex";
        else if (v == ProvokingVertex::UndefinedVertex) return "UndefinedVertex";
        return "?";
    }

    inline std::string_view to_string(TessGenMode v)
    {
        if (v == TessGenMode::Quads) return "Quads";
        else if (v == TessGenMode::Triangles) return "Triangles";
        else if (v == TessGenMode::Isolines) return "Isolines";
        return "?";
    }

    inline std::string_view to_string(TessGenSpacing v)
    {
        if (v == TessGenSpacing::Equal) return "Equal";
        else if (v == TessGenSpacing::FractionalOdd) return "FractionalOdd";
        else if (v == TessGenSpacing::FractionalEven) return "FractionalEven";
        return "?";
    }

    inline std::string_view to_string(TessellationParameter v)
    {
        if (v == TessellationParameter::PatchVertices) return "PatchVertices";
        return "?";
    }

    inline std::string_view to_string(GetParameter v)
    {
        if (v == GetParameter::Viewport) return "Viewport";
        else if (v == GetParameter::ScissorBox) return "ScissorBox";
        else if (v == GetParameter::MaxViewportDims) return "MaxViewportDims";
        else if (v == GetParameter::LineWidth) return "LineWidth";
        else if (v == GetParameter::AliasedPointSizeRange) return "AliasedPointSizeRange";
        else if (v == GetParameter::AliasedLineWidthRange) return "AliasedLineWidthRange";
        else if (v == GetParameter::CullFaceMode) return "CullFaceMode";
        else if (v == GetParameter::FrontFace) return "FrontFace";
        else if (v == GetParameter::DepthRange) return "DepthRange";
        else if (v == GetParameter::DepthWritemask) return "DepthWritemask";
        else if (v == GetParameter::DepthClearValue) return "DepthClearValue";
        else if (v == GetParameter::DepthFunc) return "DepthFunc";
        else if (v == GetParameter::DepthBits) return "DepthBits";
        else if (v == GetParameter::StencilClearValue) return "StencilClearValue";
        else if (v == GetParameter::StencilFunc) return "StencilFunc";
        else if (v == GetParameter::StencilFail) return "StencilFail";
        else if (v == GetParameter::StencilPassDepthFail) return "StencilPassDepthFail";
        else if (v == GetParameter::StencilPassDepthPass) return "StencilPassDepthPass";
        else if (v == GetParameter::StencilRef) return "StencilRef";
        else if (v == GetParameter::StencilValueMask) return "StencilValueMask";
        else if (v == GetParameter::StencilWritemask) return "StencilWritemask";
        else if (v == GetParameter::StencilBackFunc) return "StencilBackFunc";
        else if (v == GetParameter::StencilBackFail) return "StencilBackFail";
        else if (v == GetParameter::StencilBackPassDepthFail) return "StencilBackPassDepthFail";
        else if (v == GetParameter::StencilBackPassDepthPass) return "StencilBackPassDepthPass";
        else if (v == GetParameter::StencilBackRef) return "StencilBackRef";
        else if (v == GetParameter::StencilBackValueMask) return "StencilBackValueMask";
        else if (v == GetParameter::StencilBackWritemask) return "StencilBackWritemask";
        else if (v == GetParameter::StencilBits) return "StencilBits";
        else if (v == GetParameter::ColorClearValue) return "ColorClearValue";
        else if (v == GetParameter::ColorWritemask) return "ColorWritemask";
        else if (v == GetParameter::RedBits) return "RedBits";
        else if (v == GetParameter::GreenBits) return "GreenBits";
        else if (v == GetParameter::BlueBits) return "BlueBits";
        else if (v == GetParameter::AlphaBits) return "AlphaBits";
        else if (v == GetParameter::PolygonOffsetUnits) return "PolygonOffsetUnits";
        else if (v == GetParameter::PolygonOffsetFactor) return "PolygonOffsetFactor";
        else if (v == GetParameter::SampleBuffers) return "SampleBuffers";
        else if (v == GetParameter::Samples) return "Samples";
        else if (v == GetParameter::SampleCoverageValue) return "SampleCoverageValue";
        else if (v == GetParameter::SampleCoverageInvert) return "SampleCoverageInvert";
        else if (v == GetParameter::SampleMaskValue) return "SampleMaskValue";
        else if (v == GetParameter::SamplePosition) return "SamplePosition";
        else if (v == GetParameter::MaxSampleMaskWords) return "MaxSampleMaskWords";
        else if (v == GetParameter::MaxColorTextureSamples) return "MaxColorTextureSamples";
        else if (v == GetParameter::MaxDepthTextureSamples) return "MaxDepthTextureSamples";
        else if (v == GetParameter::MaxIntegerSamples) return "MaxIntegerSamples";
        else if (v == GetParameter::MaxSamples) return "MaxSamples";
        else if (v == GetParameter::MinSampleShadingValue) return "MinSampleShadingValue";
        else if (v == GetParameter::NumCompressedTextureFormats) return "NumCompressedTextureFormats";
        else if (v == GetParameter::CompressedTextureFormats) return "CompressedTextureFormats";
        else if (v == GetParameter::MaxTextureSize) return "MaxTextureSize";
        else if (v == GetParameter::MaxCubeMapTextureSize) return "MaxCubeMapTextureSize";
        else if (v == GetParameter::Max3DTextureSize) return "Max3DTextureSize";
        else if (v == GetParameter::MaxArrayTextureLayers) return "MaxArrayTextureLayers";
        else if (v == GetParameter::MaxTextureBufferSize) return "MaxTextureBufferSize";
        else if (v == GetParameter::MaxTextureLodBias) return "MaxTextureLodBias";
        else if (v == GetParameter::TextureBinding2D) return "TextureBinding2D";
        else if (v == GetParameter::TextureBindingCubeMap) return "TextureBindingCubeMap";
        else if (v == GetParameter::TextureBinding3D) return "TextureBinding3D";
        else if (v == GetParameter::TextureBinding2DArray) return "TextureBinding2DArray";
        else if (v == GetParameter::TextureBinding2DMultisample) return "TextureBinding2DMultisample";
        else if (v == GetParameter::TextureBindingBuffer) return "TextureBindingBuffer";
        else if (v == GetParameter::TextureBindingCubeMapArray) return "TextureBindingCubeMapArray";
        else if (v == GetParameter::TextureBinding2DMultisampleArray) return "TextureBinding2DMultisampleArray";
        else if (v == GetParameter::SubpixelBits) return "SubpixelBits";
        else if (v == GetParameter::ActiveTexture) return "ActiveTexture";
        else if (v == GetParameter::SamplerBinding) return "SamplerBinding";
        else if (v == GetParameter::ImplementationColorReadType) return "ImplementationColorReadType";
        else if (v == GetParameter::ImplementationColorReadFormat) return "ImplementationColorReadFormat";
        else if (v == GetParameter::BlendColor) return "BlendColor";
        else if (v == GetParameter::BlendEquationRgb) return "BlendEquationRgb";
        else if (v == GetParameter::BlendEquationAlpha) return "BlendEquationAlpha";
        else if (v == GetParameter::BlendDstRgb) return "BlendDstRgb";
        else if (v == GetParameter::BlendSrcRgb) return "BlendSrcRgb";
        else if (v == GetParameter::BlendDstAlpha) return "BlendDstAlpha";
        else if (v == GetParameter::BlendSrcAlpha) return "BlendSrcAlpha";
        else if (v == GetParameter::ArrayBufferBinding) return "ArrayBufferBinding";
        else if (v == GetParameter::ElementArrayBufferBinding) return "ElementArrayBufferBinding";
        else if (v == GetParameter::PixelPackBufferBinding) return "PixelPackBufferBinding";
        else if (v == GetParameter::PixelUnpackBufferBinding) return "PixelUnpackBufferBinding";
        else if (v == GetParameter::UniformBufferBinding) return "UniformBufferBinding";
        else if (v == GetParameter::UniformBufferStart) return "UniformBufferStart";
        else if (v == GetParameter::UniformBufferSize) return "UniformBufferSize";
        else if (v == GetParameter::TransformFeedbackBufferBinding) return "TransformFeedbackBufferBinding";
        else if (v == GetParameter::TransformFeedbackBufferStart) return "TransformFeedbackBufferStart";
        else if (v == GetParameter::TransformFeedbackBufferSize) return "TransformFeedbackBufferSize";
        else if (v == GetParameter::CopyReadBufferBinding) return "CopyReadBufferBinding";
        else if (v == GetParameter::CopyWriteBufferBinding) return "CopyWriteBufferBinding";
        else if (v == GetParameter::DrawIndirectBufferBinding) return "DrawIndirectBufferBinding";
        else if (v == GetParameter::DispatchIndirectBufferBinding) return "DispatchIndirectBufferBinding";
        else if (v == GetParameter::ShaderStorageBufferBinding) return "ShaderStorageBufferBinding";
        else if (v == GetParameter::ShaderStorageBufferStart) return "ShaderStorageBufferStart";
        else if (v == GetParameter::ShaderStorageBufferSize) return "ShaderStorageBufferSize";
        else if (v == GetParameter::AtomicCounterBufferBinding) return "AtomicCounterBufferBinding";
        else if (v == GetParameter::AtomicCounterBufferStart) return "AtomicCounterBufferStart";
        else if (v == GetParameter::AtomicCounterBufferSize) return "AtomicCounterBufferSize";
        else if (v == GetParameter::VertexArrayBinding) return "VertexArrayBinding";
        else if (v == GetParameter::VertexBindingDivisor) return "VertexBindingDivisor";
        else if (v == GetParameter::VertexBindingOffset) return "VertexBindingOffset";
        else if (v == GetParameter::VertexBindingStride) return "VertexBindingStride";
        else if (v == GetParameter::VertexBindingBuffer) return "VertexBindingBuffer";
        else if (v == GetParameter::MaxVertexAttribRelativeOffset) return "MaxVertexAttribRelativeOffset";
        else if (v == GetParameter::MaxVertexAttribBindings) return "MaxVertexAttribBindings";
        else if (v == GetParameter::MaxVertexAttribStride) return "MaxVertexAttribStride";
        else if (v == GetParameter::FramebufferBinding) return "FramebufferBinding";
        else if (v == GetParameter::DrawFramebufferBinding) return "DrawFramebufferBinding";
        else if (v == GetParameter::ReadFramebufferBinding) return "ReadFramebufferBinding";
        else if (v == GetParameter::RenderbufferBinding) return "RenderbufferBinding";
        else if (v == GetParameter::MaxRenderbufferSize) return "MaxRenderbufferSize";
        else if (v == GetParameter::MaxColorAttachments) return "MaxColorAttachments";
        else if (v == GetParameter::MaxFramebufferWidth) return "MaxFramebufferWidth";
        else if (v == GetParameter::MaxFramebufferHeight) return "MaxFramebufferHeight";
        else if (v == GetParameter::MaxFramebufferSamples) return "MaxFramebufferSamples";
        else if (v == GetParameter::MaxFramebufferLayers) return "MaxFramebufferLayers";
        else if (v == GetParameter::ReadBuffer) return "ReadBuffer";
        else if (v == GetParameter::MaxDrawBuffers) return "MaxDrawBuffers";
        else if (v == GetParameter::DrawBuffer0) return "DrawBuffer0";
        else if (v == GetParameter::DrawBuffer1) return "DrawBuffer1";
        else if (v == GetParameter::DrawBuffer2) return "DrawBuffer2";
        else if (v == GetParameter::DrawBuffer3) return "DrawBuffer3";
        else if (v == GetParameter::DrawBuffer4) return "DrawBuffer4";
        else if (v == GetParameter::DrawBuffer5) return "DrawBuffer5";
        else if (v == GetParameter::DrawBuffer6) return "DrawBuffer6";
        else if (v == GetParameter::DrawBuffer7) return "DrawBuffer7";
        else if (v == GetParameter::DrawBuffer8) return "DrawBuffer8";
        else if (v == GetParameter::DrawBuffer9) return "DrawBuffer9";
        else if (v == GetParameter::DrawBuffer10) return "DrawBuffer10";
        else if (v == GetParameter::DrawBuffer11) return "DrawBuffer11";
        else if (v == GetParameter::DrawBuffer12) return "DrawBuffer12";
        else if (v == GetParameter::DrawBuffer13) return "DrawBuffer13";
        else if (v == GetParameter::DrawBuffer14) return "DrawBuffer14";
        else if (v == GetParameter::DrawBuffer15) return "DrawBuffer15";
        else if (v == GetParameter::MaxVertexAttribs) return "MaxVertexAttribs";
        else if (v == GetParameter::MaxVertexUniformVectors) return "MaxVertexUniformVectors";
        else if (v == GetParameter::MaxVaryingVectors) return "MaxVaryingVectors";
        else if (v == GetParameter::MaxCombinedTextureImageUnits) return "MaxCombinedTextureImageUnits";
        else if (v == GetParameter::MaxVertexTextureImageUnits) return "MaxVertexTextureImageUnits";
        else if (v == GetParameter::MaxTextureImageUnits) return "MaxTextureImageUnits";
        else if (v == GetParameter::MaxFragmentUniformVectors) return "MaxFragmentUniformVectors";
        else if (v == GetParameter::MaxVertexUniformComponents) return "MaxVertexUniformComponents";
        else if (v == GetParameter::MaxFragmentUniformComponents) return "MaxFragmentUniformComponents";
        else if (v == GetParameter::MaxVaryingComponents) return "MaxVaryingComponents";
        else if (v == GetParameter::MaxVertexOutputComponents) return "MaxVertexOutputComponents";
        else if (v == GetParameter::MaxFragmentInputComponents) return "MaxFragmentInputComponents";
        else if (v == GetParameter::MaxVertexUniformBlocks) return "MaxVertexUniformBlocks";
        else if (v == GetParameter::MaxFragmentUniformBlocks) return "MaxFragmentUniformBlocks";
        else if (v == GetParameter::MaxCombinedUniformBlocks) return "MaxCombinedUniformBlocks";
        else if (v == GetParameter::MaxUniformBufferBindings) return "MaxUniformBufferBindings";
        else if (v == GetParameter::MaxUniformBlockSize) return "MaxUniformBlockSize";
        else if (v == GetParameter::MaxCombinedVertexUniformComponents) return "MaxCombinedVertexUniformComponents";
        else if (v == GetParameter::MaxCombinedFragmentUniformComponents) return "MaxCombinedFragmentUniformComponents";
        else if (v == GetParameter::UniformBufferOffsetAlignment) return "UniformBufferOffsetAlignment";
        else if (v == GetParameter::MinProgramTexelOffset) return "MinProgramTexelOffset";
        else if (v == GetParameter::MaxProgramTexelOffset) return "MaxProgramTexelOffset";
        else if (v == GetParameter::MaxUniformLocations) return "MaxUniformLocations";
        else if (v == GetParameter::MaxShaderStorageBufferBindings) return "MaxShaderStorageBufferBindings";
        else if (v == GetParameter::MaxShaderStorageBlockSize) return "MaxShaderStorageBlockSize";
        else if (v == GetParameter::ShaderStorageBufferOffsetAlignment) return "ShaderStorageBufferOffsetAlignment";
        else if (v == GetParameter::MaxCombinedShaderStorageBlocks) return "MaxCombinedShaderStorageBlocks";
        else if (v == GetParameter::MaxVertexShaderStorageBlocks) return "MaxVertexShaderStorageBlocks";
        else if (v == GetParameter::MaxFragmentShaderStorageBlocks) return "MaxFragmentShaderStorageBlocks";
        else if (v == GetParameter::MaxComputeShaderStorageBlocks) return "MaxComputeShaderStorageBlocks";
        else if (v == GetParameter::MaxCombinedShaderOutputResources) return "MaxCombinedShaderOutputResources";
        else if (v == GetParameter::MaxImageUnits) return "MaxImageUnits";
        else if (v == GetParameter::MaxVertexImageUniforms) return "MaxVertexImageUniforms";
        else if (v == GetParameter::MaxFragmentImageUniforms) return "MaxFragmentImageUniforms";
        else if (v == GetParameter::MaxCombinedImageUniforms) return "MaxCombinedImageUniforms";
        else if (v == GetParameter::MaxAtomicCounterBufferBindings) return "MaxAtomicCounterBufferBindings";
        else if (v == GetParameter::MaxAtomicCounterBufferSize) return "MaxAtomicCounterBufferSize";
        else if (v == GetParameter::MaxVertexAtomicCounterBuffers) return "MaxVertexAtomicCounterBuffers";
        else if (v == GetParameter::MaxFragmentAtomicCounterBuffers) return "MaxFragmentAtomicCounterBuffers";
        else if (v == GetParameter::MaxCombinedAtomicCounterBuffers) return "MaxCombinedAtomicCounterBuffers";
        else if (v == GetParameter::MaxVertexAtomicCounters) return "MaxVertexAtomicCounters";
        else if (v == GetParameter::MaxFragmentAtomicCounters) return "MaxFragmentAtomicCounters";
        else if (v == GetParameter::MaxCombinedAtomicCounters) return "MaxCombinedAtomicCounters";
        else if (v == GetParameter::MaxComputeUniformBlocks) return "MaxComputeUniformBlocks";
        else if (v == GetParameter::MaxComputeTextureImageUnits) return "MaxComputeTextureImageUnits";
        else if (v == GetParameter::MaxComputeImageUniforms) return "MaxComputeImageUniforms";
        else if (v == GetParameter::MaxComputeSharedMemorySize) return "MaxComputeSharedMemorySize";
        else if (v == GetParameter::MaxComputeUniformComponents) return "MaxComputeUniformComponents";
        else if (v == GetParameter::MaxComputeAtomicCounterBuffers) return "MaxComputeAtomicCounterBuffers";
        else if (v == GetParameter::MaxComputeAtomicCounters) return "MaxComputeAtomicCounters";
        else if (v == GetParameter::MaxCombinedComputeUniformComponents) return "MaxCombinedComputeUniformComponents";
        else if (v == GetParameter::MaxComputeWorkGroupInvocations) return "MaxComputeWorkGroupInvocations";
        else if (v == GetParameter::MaxComputeWorkGroupCount) return "MaxComputeWorkGroupCount";
        else if (v == GetParameter::MaxComputeWorkGroupSize) return "MaxComputeWorkGroupSize";
        else if (v == GetParameter::MaxGeometryUniformComponents) return "MaxGeometryUniformComponents";
        else if (v == GetParameter::MaxGeometryUniformBlocks) return "MaxGeometryUniformBlocks";
        else if (v == GetParameter::MaxCombinedGeometryUniformComponents) return "MaxCombinedGeometryUniformComponents";
        else if (v == GetParameter::MaxGeometryInputComponents) return "MaxGeometryInputComponents";
        else if (v == GetParameter::MaxGeometryOutputComponents) return "MaxGeometryOutputComponents";
        else if (v == GetParameter::MaxGeometryOutputVertices) return "MaxGeometryOutputVertices";
        else if (v == GetParameter::MaxGeometryTotalOutputComponents) return "MaxGeometryTotalOutputComponents";
        else if (v == GetParameter::MaxGeometryShaderInvocations) return "MaxGeometryShaderInvocations";
        else if (v == GetParameter::MaxGeometryTextureImageUnits) return "MaxGeometryTextureImageUnits";
        else if (v == GetParameter::MaxGeometryAtomicCounterBuffers) return "MaxGeometryAtomicCounterBuffers";
        else if (v == GetParameter::MaxGeometryAtomicCounters) return "MaxGeometryAtomicCounters";
        else if (v == GetParameter::MaxGeometryImageUniforms) return "MaxGeometryImageUniforms";
        else if (v == GetParameter::MaxGeometryShaderStorageBlocks) return "MaxGeometryShaderStorageBlocks";
        else if (v == GetParameter::LayerProvokingVertex) return "LayerProvokingVertex";
        else if (v == GetParameter::MaxPatchVertices) return "MaxPatchVertices";
        else if (v == GetParameter::MaxTessGenLevel) return "MaxTessGenLevel";
        else if (v == GetParameter::MaxTessControlUniformComponents) return "MaxTessControlUniformComponents";
        else if (v == GetParameter::MaxTessEvaluationUniformComponents) return "MaxTessEvaluationUniformComponents";
        else if (v == GetParameter::MaxTessControlTextureImageUnits) return "MaxTessControlTextureImageUnits";
        else if (v == GetParameter::MaxTessEvaluationTextureImageUnits) return "MaxTessEvaluationTextureImageUnits";
        else if (v == GetParameter::MaxTessControlOutputComponents) return "MaxTessControlOutputComponents";
        else if (v == GetParameter::MaxTessPatchComponents) return "MaxTessPatchComponents";
        else if (v == GetParameter::MaxTessControlTotalOutputComponents) return "MaxTessControlTotalOutputComponents";
        else if (v == GetParameter::MaxTessEvaluationOutputComponents) return "MaxTessEvaluationOutputComponents";
        else if (v == GetParameter::MaxTessControlUniformBlocks) return "MaxTessControlUniformBlocks";
        else if (v == GetParameter::MaxTessEvaluationUniformBlocks) return "MaxTessEvaluationUniformBlocks";
        else if (v == GetParameter::MaxTessControlInputComponents) return "MaxTessControlInputComponents";
        else if (v == GetParameter::MaxTessEvaluationInputComponents) return "MaxTessEvaluationInputComponents";
        else if (v == GetParameter::MaxCombinedTessControlUniformComponents) return "MaxCombinedTessControlUniformComponents";
        else if (v == GetParameter::MaxCombinedTessEvaluationUniformComponents) return "MaxCombinedTessEvaluationUniformComponents";
        else if (v == GetParameter::MaxTessControlAtomicCounterBuffers) return "MaxTessControlAtomicCounterBuffers";
        else if (v == GetParameter::MaxTessEvaluationAtomicCounterBuffers) return "MaxTessEvaluationAtomicCounterBuffers";
        else if (v == GetParameter::MaxTessControlAtomicCounters) return "MaxTessControlAtomicCounters";
        else if (v == GetParameter::MaxTessEvaluationAtomicCounters) return "MaxTessEvaluationAtomicCounters";
        else if (v == GetParameter::MaxTessControlImageUniforms) return "MaxTessControlImageUniforms";
        else if (v == GetParameter::MaxTessEvaluationImageUniforms) return "MaxTessEvaluationImageUniforms";
        else if (v == GetParameter::MaxTessControlShaderStorageBlocks) return "MaxTessControlShaderStorageBlocks";
        else if (v == GetParameter::MaxTessEvaluationShaderStorageBlocks) return "MaxTessEvaluationShaderStorageBlocks";
        else if (v == GetParameter::PrimitiveRestartForPatchesSupported) return "PrimitiveRestartForPatchesSupported";
        else if (v == GetParameter::MinFragmentInterpolationOffset) return "MinFragmentInterpolationOffset";
        else if (v == GetParameter::MaxFragmentInterpolationOffset) return "MaxFragmentInterpolationOffset";
        else if (v == GetParameter::FragmentInterpolationOffsetBits) return "FragmentInterpolationOffsetBits";
        else if (v == GetParameter::MinProgramTextureGatherOffset) return "MinProgramTextureGatherOffset";
        else if (v == GetParameter::MaxProgramTextureGatherOffset) return "MaxProgramTextureGatherOffset";
        else if (v == GetParameter::TransformFeedbackActive) return "TransformFeedbackActive";
        else if (v == GetParameter::TransformFeedbackPaused) return "TransformFeedbackPaused";
        else if (v == GetParameter::TransformFeedbackBinding) return "TransformFeedbackBinding";
        else if (v == GetParameter::MaxTransformFeedbackSeparateComponents) return "MaxTransformFeedbackSeparateComponents";
        else if (v == GetParameter::MaxTransformFeedbackInterleavedComponents) return "MaxTransformFeedbackInterleavedComponents";
        else if (v == GetParameter::MaxTransformFeedbackSeparateAttribs) return "MaxTransformFeedbackSeparateAttribs";
        else if (v == GetParameter::ProgramPipelineBinding) return "ProgramPipelineBinding";
        else if (v == GetParameter::CurrentProgram) return "CurrentProgram";
        else if (v == GetParameter::NumProgramBinaryFormats) return "NumProgramBinaryFormats";
        else if (v == GetParameter::ProgramBinaryFormats) return "ProgramBinaryFormats";
        else if (v == GetParameter::ShaderCompiler) return "ShaderCompiler";
        else if (v == GetParameter::ShaderBinaryFormats) return "ShaderBinaryFormats";
        else if (v == GetParameter::NumShaderBinaryFormats) return "NumShaderBinaryFormats";
        else if (v == GetParameter::MajorVersion) return "MajorVersion";
        else if (v == GetParameter::MinorVersion) return "MinorVersion";
        else if (v == GetParameter::NumExtensions) return "NumExtensions";
        else if (v == GetParameter::MaxServerWaitTimeout) return "MaxServerWaitTimeout";
        else if (v == GetParameter::MaxDebugMessageLength) return "MaxDebugMessageLength";
        else if (v == GetParameter::MaxDebugLoggedMessages) return "MaxDebugLoggedMessages";
        else if (v == GetParameter::DebugLoggedMessages) return "DebugLoggedMessages";
        else if (v == GetParameter::DebugNextLoggedMessageLength) return "DebugNextLoggedMessageLength";
        else if (v == GetParameter::MaxDebugGroupStackDepth) return "MaxDebugGroupStackDepth";
        else if (v == GetParameter::DebugGroupStackDepth) return "DebugGroupStackDepth";
        else if (v == GetParameter::MaxLabelLength) return "MaxLabelLength";
        else if (v == GetParameter::ContextFlags) return "ContextFlags";
        else if (v == GetParameter::ResetNotificationStrategy) return "ResetNotificationStrategy";
        else if (v == GetParameter::MultisampleLineWidthRange) return "MultisampleLineWidthRange";
        else if (v == GetParameter::MultisampleLineWidthGranularity) return "MultisampleLineWidthGranularity";
        else if (v == GetParameter::MaxElementIndex) return "MaxElementIndex";
        else if (v == GetParameter::MaxElementsVertices) return "MaxElementsVertices";
        else if (v == GetParameter::MaxElementsIndices) return "MaxElementsIndices";
        else if (v == GetParameter::NumSampleCounts) return "NumSampleCounts";
        else if (v == GetParameter::PrimitiveRestartFixedIndex) return "PrimitiveRestartFixedIndex";
        else if (v == GetParameter::ImageBindingName) return "ImageBindingName";
        else if (v == GetParameter::ImageBindingLevel) return "ImageBindingLevel";
        else if (v == GetParameter::ImageBindingLayered) return "ImageBindingLayered";
        else if (v == GetParameter::ImageBindingLayer) return "ImageBindingLayer";
        else if (v == GetParameter::ImageBindingAccess) return "ImageBindingAccess";
        else if (v == GetParameter::ImageBindingFormat) return "ImageBindingFormat";
        else if (v == GetParameter::PrimitiveBoundingBox) return "PrimitiveBoundingBox";
        return "?";
    }

    inline std::string_view to_string(ClearBuffer v)
    {
        if (v == ClearBuffer::Color) return "Color";
        else if (v == ClearBuffer::Depth) return "Depth";
        else if (v == ClearBuffer::Stencil) return "Stencil";
        return "?";
    }

    inline std::string_view to_string(DrawBuffer v)
    {
        if (v == DrawBuffer::None) return "None";
        else if (v == DrawBuffer::Back) return "Back";
        else if (v == DrawBuffer::ColorAttachment0) return "ColorAttachment0";
        else if (v == DrawBuffer::ColorAttachment1) return "ColorAttachment1";
        else if (v == DrawBuffer::ColorAttachment2) return "ColorAttachment2";
        else if (v == DrawBuffer::ColorAttachment3) return "ColorAttachment3";
        else if (v == DrawBuffer::ColorAttachment4) return "ColorAttachment4";
        else if (v == DrawBuffer::ColorAttachment5) return "ColorAttachment5";
        else if (v == DrawBuffer::ColorAttachment6) return "ColorAttachment6";
        else if (v == DrawBuffer::ColorAttachment7) return "ColorAttachment7";
        else if (v == DrawBuffer::ColorAttachment8) return "ColorAttachment8";
        else if (v == DrawBuffer::ColorAttachment9) return "ColorAttachment9";
        else if (v == DrawBuffer::ColorAttachment10) return "ColorAttachment10";
        else if (v == DrawBuffer::ColorAttachment11) return "ColorAttachment11";
        else if (v == DrawBuffer::ColorAttachment12) return "ColorAttachment12";
        else if (v == DrawBuffer::ColorAttachment13) return "ColorAttachment13";
        else if (v == DrawBuffer::ColorAttachment14) return "ColorAttachment14";
        else if (v == DrawBuffer::ColorAttachment15) return "ColorAttachment15";
        else if (v == DrawBuffer::ColorAttachment16) return "ColorAttachment16";
        else if (v == DrawBuffer::ColorAttachment17) return "ColorAttachment17";
        else if (v == DrawBuffer::ColorAttachment18) return "ColorAttachment18";
        else if (v == DrawBuffer::ColorAttachment19) return "ColorAttachment19";
        else if (v == DrawBuffer::ColorAttachment20) return "ColorAttachment20";
        else if (v == DrawBuffer::ColorAttachment21) return "ColorAttachment21";
        else if (v == DrawBuffer::ColorAttachment22) return "ColorAttachment22";
        else if (v == DrawBuffer::ColorAttachment23) return "ColorAttachment23";
        else if (v == DrawBuffer::ColorAttachment24) return "ColorAttachment24";
        else if (v == DrawBuffer::ColorAttachment25) return "ColorAttachment25";
        else if (v == DrawBuffer::ColorAttachment26) return "ColorAttachment26";
        else if (v == DrawBuffer::ColorAttachment27) return "ColorAttachment27";
        else if (v == DrawBuffer::ColorAttachment28) return "ColorAttachment28";
        else if (v == DrawBuffer::ColorAttachment29) return "ColorAttachment29";
        else if (v == DrawBuffer::ColorAttachment30) return "ColorAttachment30";
        else if (v == DrawBuffer::ColorAttachment31) return "ColorAttachment31";
        return "?";
    }

    inline std::string_view to_string(ReadBuffer v)
    {
        if (v == ReadBuffer::None) return "None";
        else if (v == ReadBuffer::Back) return "Back";
        else if (v == ReadBuffer::ColorAttachment0) return "ColorAttachment0";
        else if (v == ReadBuffer::ColorAttachment1) return "ColorAttachment1";
        else if (v == ReadBuffer::ColorAttachment2) return "ColorAttachment2";
        else if (v == ReadBuffer::ColorAttachment3) return "ColorAttachment3";
        else if (v == ReadBuffer::ColorAttachment4) return "ColorAttachment4";
        else if (v == ReadBuffer::ColorAttachment5) return "ColorAttachment5";
        else if (v == ReadBuffer::ColorAttachment6) return "ColorAttachment6";
        else if (v == ReadBuffer::ColorAttachment7) return "ColorAttachment7";
        else if (v == ReadBuffer::ColorAttachment8) return "ColorAttachment8";
        else if (v == ReadBuffer::ColorAttachment9) return "ColorAttachment9";
        else if (v == ReadBuffer::ColorAttachment10) return "ColorAttachment10";
        else if (v == ReadBuffer::ColorAttachment11) return "ColorAttachment11";
        else if (v == ReadBuffer::ColorAttachment12) return "ColorAttachment12";
        else if (v == ReadBuffer::ColorAttachment13) return "ColorAttachment13";
        else if (v == ReadBuffer::ColorAttachment14) return "ColorAttachment14";
        else if (v == ReadBuffer::ColorAttachment15) return "ColorAttachment15";
        else if (v == ReadBuffer::ColorAttachment16) return "ColorAttachment16";
        else if (v == ReadBuffer::ColorAttachment17) return "ColorAttachment17";
        else if (v == ReadBuffer::ColorAttachment18) return "ColorAttachment18";
        else if (v == ReadBuffer::ColorAttachment19) return "ColorAttachment19";
        else if (v == ReadBuffer::ColorAttachment20) return "ColorAttachment20";
        else if (v == ReadBuffer::ColorAttachment21) return "ColorAttachment21";
        else if (v == ReadBuffer::ColorAttachment22) return "ColorAttachment22";
        else if (v == ReadBuffer::ColorAttachment23) return "ColorAttachment23";
        else if (v == ReadBuffer::ColorAttachment24) return "ColorAttachment24";
        else if (v == ReadBuffer::ColorAttachment25) return "ColorAttachment25";
        else if (v == ReadBuffer::ColorAttachment26) return "ColorAttachment26";
        else if (v == ReadBuffer::ColorAttachment27) return "ColorAttachment27";
        else if (v == ReadBuffer::ColorAttachment28) return "ColorAttachment28";
        else if (v == ReadBuffer::ColorAttachment29) return "ColorAttachment29";
        else if (v == ReadBuffer::ColorAttachment30) return "ColorAttachment30";
        else if (v == ReadBuffer::ColorAttachment31) return "ColorAttachment31";
        return "?";
    }

    inline std::string_view to_string(ShaderBinaryFormat) { return "ShaderBinaryFormat"; }

    inline std::string_view to_string(ProgramBinaryFormat) { return "ProgramBinaryFormat"; }

    inline std::string_view to_string(GetPointerParameter v)
    {
        if (v == GetPointerParameter::DebugCallbackFunction) return "DebugCallbackFunction";
        else if (v == GetPointerParameter::DebugCallbackUserParam) return "DebugCallbackUserParam";
        return "?";
    }

    inline std::string_view to_string(MultisampleParameter v)
    {
        if (v == MultisampleParameter::SamplePosition) return "SamplePosition";
        return "?";
    }

    inline std::string_view to_string(InternalFormatTarget v)
    {
        if (v == InternalFormatTarget::Renderbuffer) return "Renderbuffer";
        else if (v == InternalFormatTarget::Texture2DMultisample) return "Texture2DMultisample";
        else if (v == InternalFormatTarget::Texture2DMultisampleArray) return "Texture2DMultisampleArray";
        return "?";
    }

    inline std::string_view to_string(InternalFormatParameter v)
    {
        if (v == InternalFormatParameter::Samples) return "Samples";
        else if (v == InternalFormatParameter::NumSampleCounts) return "NumSampleCounts";
        return "?";
    }

    inline std::string_view to_string(ProgramPipelineParameter v)
    {
        if (v == ProgramPipelineParameter::ActiveProgram) return "ActiveProgram";
        else if (v == ProgramPipelineParameter::ValidateStatus) return "ValidateStatus";
        else if (v == ProgramPipelineParameter::InfoLogLength) return "InfoLogLength";
        else if (v == ProgramPipelineParameter::VertexShader) return "VertexShader";
        else if (v == ProgramPipelineParameter::FragmentShader) return "FragmentShader";
        else if (v == ProgramPipelineParameter::GeometryShader) return "GeometryShader";
        else if (v == ProgramPipelineParameter::TessControlShader) return "TessControlShader";
        else if (v == ProgramPipelineParameter::TessEvaluationShader) return "TessEvaluationShader";
        else if (v == ProgramPipelineParameter::ComputeShader) return "ComputeShader";
        return "?";
    }

    inline std::string_view to_string(SyncFlag v)
    {
        if (v == SyncFlag::None) return "None";
        return "?";
    }

} // namespace metagl
