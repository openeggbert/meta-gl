# Changelog

All notable changes to meta-gl will be documented here.

## [0.2.0] — 2026-06-27

### Breaking changes
- `ContextListener::on_context_lost()` renamed to `OnContextLost()`.
- `ContextListener::on_context_restored()` renamed to `OnContextRestored()`.
- `ContextInfo` no longer contains `vendor`, `renderer`, `gles20`–`gles32`, `webgl`/`webgl1`/`webgl2` fields.
  Use `GetCapabilities()` for feature detection. `ContextInfo` now holds only `api`, `major`, `minor`, `generation`, `status`.

### Added
- **Typed handle types** (`ShaderId`, `ProgramId`, `TextureId`, `BufferId`, `FramebufferId`, `RenderbufferId`,
  `SamplerId`, `VertexArrayId`, `QueryId`, `TransformFeedbackId`, `ProgramPipelineId`,
  `UniformLocation`, `AttribLocation`, `ImageUnit`) replacing raw `GLuint`/`GLint` parameters.
- **`EnumNames.hpp`** — `to_string()` overloads for all 89 enum classes and handle types.
- **`Debug.hpp`** / **`src/Debug.cpp`** — optional GL call logging controlled by `METAGLDEBUG` define.
- **`Context.hpp`** / **`Capabilities.hpp`** — context lifecycle state and feature-detection structs.
- **`ContextEvents.hpp`** — `ContextListener` interface with `AddContextListener` / `RemoveContextListener`
  / `NotifyContextLost` / `NotifyContextRestored`.
- **`Emscripten.hpp`** — `InstallEmscriptenContextLossCallbacks()` for WebGL context loss/restore.
- **`SamplerParameter`** enum for `glSamplerParameter*` / `glGetSamplerParameter*` (replaces `TextureParameter`).
- **`SampleMaskValue`** bitfield enum for `glSampleMaski`.
- **`ColorAttachment`** enum (Color0–Color31) with `to_framebuffer_attachment`, `to_draw_buffer`,
  `to_read_buffer` conversion helpers; `DrawBuffer` and `ReadBuffer` reduced to `None`/`Back`.
- **`GlHandle`** concept (requires `.value` of type `GLuint`).
- **`GlEnum`** concept (enum class with `GLenum` underlying type).
- **`GlBitfield`** concept with generic `operator|`, `operator&`, `operator~` for all bitfield enums.
- **`SpanCompatible`** concept constraining `std::span<const T>` buffer upload templates.
- **`std::span`** overloads for all `glGen*` / `glDelete*` function families.
- **`std::span<const T>`** template overloads for `glBufferData` and `glBufferSubData`.
- **`std::span<const DrawBuffer>`** overload for `glDrawBuffers`.
- **`std::span<const FramebufferAttachment>`** overloads for `glInvalidateFramebuffer` and `glInvalidateSubFramebuffer`.
- **`std::span<const GLuint>`** overload for `glDebugMessageControl` ids parameter.
- **`std::span<const ProgramResourceProperty>`** overload for `glGetProgramResourceiv`.
- **`std::string_view`** convenience overload for `glShaderSource` (single source string).
- Template dispatch helpers: `glGetUniform<T>`, `glGetnUniform<T>`, `glTexParameter<T>`,
  `glSamplerParameter<T>`, `glClearBuffer<T>`, `glGetVertexAttrib<T>`.
- `glIs*` functions now return `bool` instead of `GLboolean`.
- **Doxygen documentation** for all 11 public headers: `@file`, `@brief`, `@param`, `@return`, `@note`
  annotations on every enum class, concept, handle type, function, and macro.
- **`#ifdef __EMSCRIPTEN__` loader selection example** in `Loader.hpp` clarifying
  `emscripten_webgl_get_proc_address` vs. `eglGetProcAddress` for WebGL builds.
- `AllFunctionsLoaded()` public API in `Loader.hpp`.
- `IsFunctionAvailable(std::string_view)` public API in `Loader.hpp`.
- `Debug.hpp` and `EnumNames.hpp` included by umbrella `metagl.hpp` (opt-out via
  `METAGL_NO_DEBUG` / `METAGL_NO_ENUM_NAMES`).
- `Emscripten.hpp` included by umbrella `metagl.hpp` when `__EMSCRIPTEN__` is defined.

### Changed
- C++ baseline raised from C++20 to **C++23**.
- CMake: `target_compile_features(PUBLIC cxx_std_23)` propagates standard to consumers.
- CMake: added `-Wall -Wextra -Wpedantic` (GCC/Clang) and `/W4` (MSVC) warning flags.
- CMake: `find_package(meta-gl CONFIG)` support via `CMakePackageConfigHelpers`.
- CMake: `BUILD_TESTING` option (default `OFF`) with `enable_testing()` guard.
- CMake: `BUILD_SHARED_LIBS` option (default `OFF`).
- CMake: `SANITIZE` option enabling ASan + UBSan for GCC/Clang.
- `g_function_availability` map is now cleared at the start of each `Initialize()` call.
- `detail::IsUniformMatrixShape` bool trait promoted to `detail::UniformMatrixShape` concept.
- `BlendMode` enum removed (duplicated `BlendEquation`).
- `TextureFilter` renamed to `BlitFilter` (used only by `glBlitFramebuffer`).
- `TextureWrap` removed (duplicate of `TextureWrapMode`).
- `ContextInfo` gles/webgl flags and string fields moved to `Capabilities` (single source of truth).

### Fixed
- README.md examples corrected from `metagl::GlClear` etc. to `metagl::glClear` (lowercase).

## [0.1.0] — initial

### Added
- Initial extraction from easy-gl as a standalone low-level GL layer.
- `metagl::Initialize(GlGetProcAddressFn)` / `metagl::IsInitialized()` loader API.
- Type-safe `enum class` wrappers: `BufferTarget`, `BufferUsage`, `ShaderType`, `TextureTarget`,
  `TextureParameter`, `PixelFormat`, `PixelType`, `PrimitiveType`, `DataType`, `Capability`,
  `CompareFunc`, `CullFace`, `FrontFace`, `BlendFactor`, `StringName`, `ClearBufferBit`.
- Bitwise `operator|` for `ClearBufferBit` mask composition.
- Full set of `metagl::gl*` wrapper functions covering buffers, shaders, programs, textures,
  vertex arrays, draw calls, and render state.
- CMake target `meta-gl` with alias `meta-gl::meta-gl`, static library.
