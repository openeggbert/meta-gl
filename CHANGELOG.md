# Changelog

All notable changes to meta-gl will be documented here.

## [Unreleased]

### Added
- Initial extraction from easy-gl as a standalone low-level GL layer.
- `metagl::Initialize(GlGetProcAddressFn)` / `metagl::IsInitialized()` loader API.
- Type-safe `enum class` wrappers: `BufferTarget`, `BufferUsage`, `ShaderType`, `TextureTarget`, `TextureParameter`, `TextureFilter`, `TextureWrap`, `PixelFormat`, `PixelType`, `PrimitiveType`, `DataType`, `Capability`, `CompareFunc`, `CullFace`, `FrontFace`, `BlendFactor`, `StringName`, `IntegerName`, `ShaderParameter`, `ProgramParameter`, `ClearBufferBit`.
- Bitwise `operator|` for `ClearBufferBit` mask composition.
- Full set of `metagl::Gl*` wrapper functions covering buffers, shaders, programs, textures, vertex arrays, draw calls, and render state.
- CMake target `meta-gl` with alias `meta-gl::meta-gl`, C++20, static library.
