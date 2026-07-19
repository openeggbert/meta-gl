# Changelog

All notable changes to meta-gl will be documented here.

## [Unreleased]

### Added
- Internal-only desktop OpenGL ES-tier equivalence diagnostic
  (`metagl::detail::GetDesktopEsTier()` in `DesktopEsTier.hpp`, R76–R78):
  checks the same mandatory-function lists used for native OpenGL ES against
  a desktop 3.3+ context, with `GL_ARB_ES3_1_compatibility` /
  `GL_ARB_ES3_2_compatibility` as a fast additional signal. It never affects
  `Capabilities` or `Initialize()`'s success/failure, and is not part of the
  stable public API surface.

## [0.3.0] — 2026-07-19

### Breaking changes
- `AttribLocation` now stores the signed `GLint` returned by
  `glGetAttribLocation`; code that directly depends on its former unsigned
  representation must be updated.
- Invalid `PrimitiveType::Quads` and `PixelFormat::Green/Blue` constants were
  removed. They were not legal values for the wrapped OpenGL ES function
  domains.
- The broad `ClearBuffer` enum was replaced by the exact
  `FloatClearBuffer`, `SignedIntegerClearBuffer`, and
  `UnsignedIntegerClearBuffer` domains. `glClearBufferfi` now accepts only
  `depth` and `stencil`; it supplies the required `GL_DEPTH_STENCIL` and zero
  draw-buffer arguments internally.

### Added
- **Invalid Input Contract**: Enforced `std::terminate()` for invalid inputs even
  in Release builds (R07–R11). This covers `size_t` overflow, incomplete
  vector/matrix data, and invalid transpose flags.
- **ABI/SONAME Verification**: Shared libraries on Linux now carry
  `libmeta-gl.so.0` identity to signal pre-1.0 ABI instability (R04–R06),
  verified by an automated test.
- `metagl-release-contract-tests` and `metagl-soname-test` for reliability and
  binary consistency.
- `ImageCopyTextureTarget` and typed `glCopyImageSubData` overloads for all
  texture/renderbuffer source and destination combinations. The original
  raw-name overload remains available for downstream source compatibility.
- Atomic `RestoreCurrentContext()` lifecycle helper and automatic Emscripten
  entry-point reload before restored callbacks.
- Explicit bitfield traits, safe `IndexType`, `ActiveAttribIndex`, and
  installed-package consumer coverage.
- Desktop OpenGL 3.3+ detection with `glDepthRange`/`glClearDepth` adapters,
  plus `SupportsDesktopOpenGL()` and ANGLE detection via `IsAngle()`.
- Project-scoped CMake options and a supported CMake switch for debug logging.
- Typed texture binding/parameter overloads, checked range-size conversions,
  an API-consistency verifier, optional headless EGL smoke testing, and a
  Doxygen build target.

### Changed
- **Release Contract**: Helper functions for size and matrix checks no longer
  rely on `assert()`; they now use enforced termination to prevent undefined
  behavior from reaching the driver.
- Initialization now bootstraps API detection and validates the exact
  mandatory entry-point set for the reported GLES 2.0/3.0/3.1/3.2 version;
  desktop contexts must report OpenGL 3.3 or newer and provide the common
  subset plus `glGetStringi`, while WebGL retains its browser-compatible
  GLES subset.
- `AttribLocation` stores the signed `GLint` returned by
  `glGetAttribLocation`; explicit signed and unsigned constructors preserve
  existing call sites.
- Package compatibility for `0.x` releases is limited to the same minor
  version.
- Khronos GLES/KHR headers and license files are installed with the package.
- Query/create results are marked `[[nodiscard]]`; lightweight GL wrappers
  support same-type equality comparisons.

### Fixed
- Loader candidates and capabilities are published only after version parsing
  and mandatory-entry validation succeed; invalid, unsupported, and partial
  contexts no longer pass initialization.
- Context loss now clears current API identity and capabilities, hides all
  function availability, makes `AllFunctionsLoaded()` false, and adds an
  initialized-context precondition to every Debug wrapper assertion.
- `glCopyImageSubData` can now represent renderbuffer endpoints without casts,
  while typed texture endpoints exclude cube-map faces and texture buffers
  that are not legal targets for this function.
- Clear-buffer wrappers no longer expose impossible or cross-function buffer
  targets, and `glClearBufferfi` can now express its only legal OpenGL call
  without an unsafe enum cast.
- Failed reloads no longer expose stale context status or capabilities.
- Context listener registration ignores duplicates and event dispatch remains
  stable when a listener removes itself.
- `GlBitfield` no longer accepts every `GLenum`-backed enum, and `operator~`
  no longer creates bits outside the selected mask domain.
- Removed `PrimitiveType::Quads` and `PixelFormat::Green/Blue`, which are not
  valid values for their advertised function domains.
- Mock loaders use a correctly typed `glGetError` stub under function-type
  sanitizers.
- Installed packages no longer depend on uninstalled Khronos headers.
- The vendored `KHR/khrplatform.h` now provides the public Khronos platform
  contract required when system EGL headers are included beside meta-gl.
- Uniform vector/matrix helpers reject incomplete ranges instead of silently
  truncating them, and all span length conversions check the GL target type.
- `IsFunctionAvailable()` no longer allocates inside its `noexcept` lookup.
- The canonical name is used for aliased framebuffer-binding query tokens.
- `GetParameter` name lookup no longer exceeds MSVC's nested-block compiler
  limit.
- MSVC builds use the conforming preprocessor required by the C++23
  `__VA_OPT__` debug macros.
- The extension mock loader now returns a correctly typed `glGetError`
  function instead of invoking a `void()` stub through an incompatible
  function pointer.
- Added `FlushDebugLog()` and avoided iostream flushing from Windows DLL
  static teardown, where the loader lock can deadlock the process.
- Windows shared-library tests and examples now stage `meta-gl` beside their
  executables, so the runtime loader can find the DLL.
- README support claims, context-restore sequence, and handle example now match
  the implementation.

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
