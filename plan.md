# meta-gl Improvement Plan

This document lists all identified improvement tasks across the codebase.
Tasks are grouped by theme; within each group they are roughly ordered by priority.

---

## A — Typed Handle Types

Every GL object is currently passed as bare `GLuint`. Adding strong-typedef handle structs
(as recommended in CLAUDE.md) will catch accidental cross-domain mixing at compile time
and is the single highest-impact safety improvement.

| # | Task |
|---|------|
| A1 | ✅ Add `struct ShaderId { GLuint value{}; };` to `Types.hpp` and replace all `GLuint` shader parameters in `Functions.hpp` / `Functions.cpp` |
| A2 | ✅ Add `struct ProgramId { GLuint value{}; };` and replace all program `GLuint` parameters (20+ functions including `glCreateProgram`, `glDeleteProgram`, `glUseProgram`, `glLinkProgram`, `glGetProgramiv`, `glGetProgramInfoLog`, `glAttachShader`, `glDetachShader`, `glGetAttachedShaders`, `glValidateProgram`, `glGetProgramBinary`, `glProgramBinary`, all `glProgramUniform*`) |
| A3 | ✅ Add `struct TextureId { GLuint value{}; };` and replace all texture `GLuint` parameters (`glGenTextures`, `glDeleteTextures`, `glBindTexture`, `glIsTexture`, all `glTexImage*`, `glTexSubImage*`, `glTexStorage*`, `glTexParameter*`, `glBindImageTexture`, `glTexBuffer`, `glTexBufferRange`, `glFramebufferTexture*`, `glCopyImageSubData srcName/dstName`) |
| A4 | ✅ Add `struct BufferId { GLuint value{}; };` and replace all buffer `GLuint` parameters (`glGenBuffers`, `glDeleteBuffers`, `glBindBuffer`, `glBindBufferBase`, `glBindBufferRange`, `glIsBuffer`, `glGetBufferParameteriv`, `glGetBufferParameteri64v`, `glGetBufferPointerv`, `glTexBuffer`, `glTexBufferRange`) |
| A5 | ✅ Add `struct FramebufferId { GLuint value{}; };` and replace all framebuffer `GLuint` parameters (`glGenFramebuffers`, `glDeleteFramebuffers`, `glBindFramebuffer`, `glIsFramebuffer`, `glFramebufferTexture*`, `glFramebufferRenderbuffer`, `glCheckFramebufferStatus`) |
| A6 | ✅ Add `struct RenderbufferId { GLuint value{}; };` and replace all renderbuffer `GLuint` parameters (`glGenRenderbuffers`, `glDeleteRenderbuffers`, `glBindRenderbuffer`, `glIsRenderbuffer`, `glRenderbufferStorage`, `glRenderbufferStorageMultisample`, `glGetRenderbufferParameteriv`, `glFramebufferRenderbuffer`) |
| A7 | ✅ Add `struct SamplerId { GLuint value{}; };` and replace all sampler `GLuint` parameters (`glGenSamplers`, `glDeleteSamplers`, `glBindSampler`, `glIsSampler`, all `glSamplerParameter*`, all `glGetSamplerParameter*`) |
| A8 | ✅ Add `struct VertexArrayId { GLuint value{}; };` and replace all VAO `GLuint` parameters (`glGenVertexArrays`, `glDeleteVertexArrays`, `glBindVertexArray`, `glIsVertexArray`) |
| A9 | ✅ Add `struct QueryId { GLuint value{}; };` and replace all query `GLuint` parameters (`glGenQueries`, `glDeleteQueries`, `glIsQuery`, `glBeginQuery`, `glGetQueryObjectuiv`, `glGetQueryObjectiv`, `glGetQueryObjecti64v`, `glGetQueryObjectui64v`) |
| A10 | ✅ Add `struct TransformFeedbackId { GLuint value{}; };` and replace all transform-feedback `GLuint` parameters (`glGenTransformFeedbacks`, `glDeleteTransformFeedbacks`, `glBindTransformFeedback`, `glIsTransformFeedback`) |
| A11 | ✅ Add `struct ProgramPipelineId { GLuint value{}; };` and replace all pipeline `GLuint` parameters (`glGenProgramPipelines`, `glDeleteProgramPipelines`, `glBindProgramPipeline`, `glIsProgramPipeline`, `glUseProgramStages`, `glActiveShaderProgram`, `glValidateProgramPipeline`, `glGetProgramPipelineiv`, `glGetProgramPipelineInfoLog`) |
| A12 | ✅ Add `struct UniformLocation { GLint value{-1}; };` and replace the bare `GLint location` parameter in all 66+ `glUniform*` and `glProgramUniform*` functions, and the return type of `glGetUniformLocation` |
| A13 | ✅ Add `struct AttribLocation { GLuint value{}; };` and replace `GLuint index` in vertex-attrib functions (`glBindAttribLocation`, `glGetAttribLocation`, `glEnableVertexAttribArray`, `glDisableVertexAttribArray`, `glVertexAttribPointer`, `glGetActiveAttrib`, `glGetVertexAttrib*`) |
| A14 | ✅ Update `EnumNames.hpp` `to_string()` overloads to accept the new handle types and print their `.value` fields with a type prefix (e.g., `"TextureId(3)"`) |
| A15 | ✅ Add `struct ImageUnit { GLuint value{}; };` and replace `GLuint unit` in `glBindImageTexture` — `TextureUnit` enum cannot be reused because it holds `GL_TEXTURE0`-style enum values, not zero-based unit indices |

---

## B — Typed Enum Cleanup

| # | Task |
|---|------|
| B1 | ✅ Remove dead `BlendMode` enum (`Enums.hpp:97-114`) — it duplicates `BlendEquation` values and is never used in any function signature |
| B2 | ✅ Resolve the `TextureMinFilter` / `TextureMagFilter` / `TextureFilter` overlap — renamed `TextureFilter` → `BlitFilter`: keep the first two, document or remove `TextureFilter` (used only for `glBlitFramebuffer`), add a comment explaining the distinction |
| B3 | ✅ Resolve the `TextureWrapMode` / `TextureWrap` duplicate — removed `TextureWrap` — pick one name, remove the other, update all usages |
| B4 | ~~ignore~~ `IntegerName` — duplicates `GetParameter` values but může být využit uživateli knihovny; ponechat |
| B5 | ✅ Add a dedicated `BufferPointerParameter` enum with a single value `MapPointer` and use it in `glGetBufferPointerv` instead of the generic `BufferParameter` |
| B6 | ✅ Add a dedicated `SamplerParameter` enum (currently callers must reuse `TextureParameter`) for all `glSamplerParameter*` and `glGetSamplerParameter*` functions |
| B7 | ~~ignore~~ `TextureUnit` nelze použít pro `glBindImageTexture` — `GL_TEXTURE0` ≠ index 0; místo toho implementováno jako A15 (`ImageUnit` handle) |
| B8 | ~~ignore~~ ColorAttachment enum + to_draw_buffer()/to_read_buffer()/to_framebuffer_attachment() converters already address the duplication cleanly; full deduplication would require breaking API changes without meaningful benefit |
| B9 | ✅ Make `glIs*` return types `bool` instead of `GLboolean` (`unsigned char`) throughout `Functions.hpp` |
| B10 | ✅ Generic `GlBitfield` template operators replace all per-enum `operator&` / `operator~` (covered by E2) |
| B11 | ✅ `ContextFlagMask` gets `operator|` / `&` / `~` via the generic `GlBitfield` template (covered by E2) |
| B12 | ✅ ContextInfo gles* fields removed (H6); Capabilities is the single source of truth with `gles20`/`gles30`/`gles31`/`gles32` |
| B13 | ✅ `glSampleMaski` uses `SampleMaskValue` bitfield enum instead of raw `GLbitfield` |
| B14 | ~~ignore~~ `IntegerName` je záměrná přehledná podmnožina `GetParameter`; duplicita je čistě konceptuální, žádný compile/runtime problém (stejný důvod jako B4) |

---

## C — `std::span` Adoption

All gen/delete and data-upload functions currently use raw pointer + size pairs.

| # | Task |
|---|------|
| C1 | Wrap all `glGen*` functions with `std::span<GLuint>` overloads (or span of handle type after A-tasks): `glGenBuffers`, `glGenTextures`, `glGenFramebuffers`, `glGenRenderbuffers`, `glGenSamplers`, `glGenVertexArrays`, `glGenQueries`, `glGenTransformFeedbacks`, `glGenProgramPipelines` |
| C2 | Wrap all `glDelete*` functions with `std::span<const GLuint>` overloads (same list as C1) |
| C3 | Replace `(GLsizeiptr size, const void* data)` in `glBufferData` with a template `std::span<const T>` overload (keep raw overload for compatibility) |
| C4 | Replace `(GLsizeiptr size, const void* data)` in `glBufferSubData` with `std::span<const T>` template overload |
| C5 | Replace `const void* pixels` in `glTexImage2D` / `glTexImage3D` / `glTexSubImage2D` / `glTexSubImage3D` with `std::span<const std::byte>` overloads |
| C6 | Replace `(GLsizei imageSize, const void* data)` in all `glCompressedTexImage*` and `glCompressedTexSubImage*` with `std::span<const std::byte>` |
| C7 | ✅ Add `std::span<const DrawBuffer>` overload for `glDrawBuffers` |
| C8 | ✅ Add `std::span<const FramebufferAttachment>` overload for `glInvalidateFramebuffer` and `glInvalidateSubFramebuffer` |
| C9 | ✅ Add `std::span<const GLuint>` overload for `glDebugMessageControl` `ids` parameter |
| C10 | ✅ Add `std::span<const ProgramResourceProperty>` overload for `glGetProgramResourceiv` `props` parameter |
| C11 | ✅ Add a `std::string_view` convenience overload for `glShaderSource` (single source string; raw multi-pointer version preserved) |

---

## D — Template Dispatch Additions

| # | Task |
|---|------|
| D1 | ✅ Add `glGetUniform<T>(ProgramId program, UniformLocation location, T* params)` template dispatch for `glGetUniformfv` / `glGetUniformiv` / `glGetUniformuiv` |
| D2 | ✅ Add `glGetnUniform<T>` template dispatch for `glGetnUniformfv` / `glGetnUniformiv` / `glGetnUniformuiv` |
| D3 | ✅ Add `glTexParameter<T>(TextureTarget, TextureParameter, T)` template dispatch to unify `glTexParameterf` and `glTexParameteri` |
| D4 | ✅ Add `glSamplerParameter<T>(SamplerId, SamplerParameter, T)` template dispatch for `glSamplerParameterf` and `glSamplerParameteri` |
| D5 | ✅ Add `glClearBuffer<T>(ClearBuffer buffer, GLint drawbuffer, T* value)` template dispatch for `glClearBufferfv` / `glClearBufferiv` / `glClearBufferuiv` |
| D6 | ✅ Add `glGetVertexAttrib<T>(AttribLocation, VertexAttribParameter, T* params)` template dispatch for `glGetVertexAttribfv` / `glGetVertexAttribiv` / `glGetVertexAttribIiv` / `glGetVertexAttribIuiv` |

---

## E — Concepts

| # | Task |
|---|------|
| E1 | ✅ Add `GlHandle` concept (requires `.value` of type `GLuint`) to constrain future template helpers that accept any handle type |
| E2 | ✅ Add `GlBitfield` concept (enum class whose underlying type is `GLbitfield`) to enable a generic `operator|` / `operator&` / `operator~` implementation via one template and eliminate per-enum repetition |
| E3 | ✅ Add `GlEnum` concept (enum class whose underlying type is `GLenum`) for documentation and potential generic `to_gl_enum` constraint |
| E4 | ✅ Add `SpanCompatible` concept (trivially copyable, standard layout) to constrain the buffer/texture `std::span<const T>` templates |
| E5 | ✅ Promote `detail::IsUniformMatrixShape` (currently a bool trait) to a proper `UniformMatrixShape` concept for cleaner compiler diagnostics |

---

## F — Build System

| # | Task |
|---|------|
| F1 | ~~cancelled~~ C++23 is the intended baseline (CLAUDE.md updated accordingly) |
| F2 | ✅ Add compiler warning flags: `-Wall -Wextra -Wpedantic` for GCC/Clang, `/W4` for MSVC, using `target_compile_options` with a generator expression |
| F3 | ✅ Add CMake package install support: add `CMakePackageConfigHelpers`, write `meta-glConfig.cmake.in`, call `install(EXPORT ...)`, generate a version file — enables `find_package(meta-gl CONFIG)` |
| F4 | ✅ Add `enable_testing()` and a `BUILD_TESTING` option guard to `CMakeLists.txt` in preparation for a test executable |
| F5 | ✅ Add optional ASan/UBSan build presets or a `SANITIZE` CMake option |
| F6 | ✅ Use `target_compile_features(meta-gl PUBLIC cxx_std_23)` instead of setting `CXX_STANDARD` property directly — this propagates the requirement to consumers |
| F7 | ✅ Add an explicit `BUILD_SHARED_LIBS` option with a clear default and document it in README.md |

---

## G — Debug & Error Handling

| # | Task |
|---|------|
| G1 | Add `assert(detail::g_gl.FunctionName != nullptr)` guards inside each wrapper function so a call to an unloaded ES 3.x function on an ES 2.0 device fails with a clear assertion rather than a segfault |
| G2 | Add an optional `glGetError()` check injected after each wrapper when `METAGLDEBUG` is defined — record or assert on non-`GL_NO_ERROR` results |
| G3 | Add a flush-on-exit mechanism to the debug logger: register an `atexit` handler (or add a destructor to `CallLogger`) so buffered calls are not lost on normal exit |
| G4 | Flush the debug buffer immediately on every call when a `METAGLDEBUG_IMMEDIATE` define is set (trade throughput for crash-safety during development) |
| G5 | ✅ Expose `detail::all_loaded()` (currently `[[maybe_unused]]` dead code at `Functions.cpp:573`) through `Loader.hpp` as `bool AllFunctionsLoaded()` so callers can verify a full load |
| G6 | ✅ Reset `detail::g_function_availability` map at the start of each `Initialize()` call to avoid stale entries when re-initializing |
| G7 | ✅ Document thread-safety contract in `Loader.hpp` / README.md: state that `Initialize()` must complete before any render thread calls wrapper functions, and that concurrent `Initialize()` is not supported |
| G8 | ✅ Document the required call order after context restore (`LoadCurrentContext` → `NotifyContextRestored`) in `ContextEvents.hpp` |

---

## H — Code Quality & Naming

| # | Task |
|---|------|
| H1 | ✅ Fix README.md API examples: replace `metagl::GlClearColor`, `metagl::GlClear`, etc. with the actual lowercase names `metagl::glClearColor`, `metagl::glClear` throughout (the capital-`Gl` prefix never existed in the code) |
| H2 | ✅ Rename `ContextListener` virtual methods `on_context_lost()` / `on_context_restored()` to `OnContextLost()` / `OnContextRestored()` to match the PascalCase convention used by every other method in the file |
| H3 | ✅ Fix `EnumNames.hpp` file header comment: "Auto-generated" was not present — header already correctly describes the file as manually maintained |
| H4 | ✅ Add `Emscripten.hpp` behind `#ifdef __EMSCRIPTEN__` to the `metagl.hpp` umbrella header so Emscripten users get it automatically |
| H5 | ✅ Add `Debug.hpp` and `EnumNames.hpp` to the `metagl.hpp` umbrella header (behind `METAGL_NO_DEBUG` / `METAGL_NO_ENUM_NAMES` opt-out defines) |
| H6 | ✅ Resolve the `ContextInfo` vs `Capabilities` dual source-of-truth: removed duplicate fields (vendor, renderer, gles20-32, webgl flags) from `ContextInfo`; `Capabilities` is now the single source of truth for feature detection |
| H7 | ✅ Verify the claim in `OpenGL_ES.md` that 358 functions are wrapped — confirmed correct, last declaration is #358 |
| H8 | ✅ Update `CHANGELOG.md` with version-tagged entries covering the debug logging, `EnumNames.hpp`, context events, and Emscripten additions that are currently only in the `[Unreleased]` section |
| H9 | ✅ Add documentation of `Debug.hpp`, `Capabilities.hpp`, `ContextEvents.hpp`, and `Emscripten.hpp` to the header table in README.md |
| H10 | ✅ Add Emscripten/WASM build instructions to README.md (which `emcmake`/`emmake` invocation, how to link, when to call `InstallEmscriptenContextLossCallbacks`) |
| H11 | ✅ Document in `glObjectLabel` / `glGetObjectLabel` that `name` is a raw `GLuint` because the API targets named objects of mixed types and typed overloads would be unwieldy |
| H12 | ✅ Clarify `glCopyImageSubData` usage: changed `srcName`/`dstName` from `TextureId` to raw `GLuint` with an explanatory comment — they can refer to textures or renderbuffers depending on the target parameter |

---

## I — Tests

| # | Task |
|---|------|
| I1 | ✅ Add a `tests/` directory and a basic `CMakeLists.txt` under it, wired into the root via `add_subdirectory(tests)` guarded by `BUILD_TESTING` |
| I2 | ✅ Add compile-time tests (`static_assert`) verifying that template dispatch (`glGetUniform<T>`, `glGetnUniform<T>`, `glTexParameter<T>`, `glSamplerParameter<T>`, `glClearBuffer<T>`, `glGetVertexAttrib<T>`) resolves without ambiguity for float/int/uint |
| I3 | ✅ Add compile-time tests verifying that bitfield `operator|` / `&` / `~` compile and preserve the enum type for all bitfield enums |
| I4 | ✅ Add compile-time tests verifying that mixing handle types (`ShaderId` vs `ProgramId`) does not compile (`static_assert(!std::is_convertible_v<...>)` / `!std::is_constructible_v`) |
| I5 | Add unit tests for `Context.cpp` lifecycle: `MarkContextLost`, `MarkContextRestored`, `LoadCurrentContext`, `GetContextStatus` transitions |
| I6 | Add unit tests for `ContextEvents.cpp`: `AddContextListener`, `RemoveContextListener`, `NotifyContextLost`, `NotifyContextRestored` — use a mock listener |
| I7 | Add unit tests for `HasExtension` and `GetCapabilities` with a fake extension string |
| I8 | Add unit tests for all 89 `to_string()` overloads in `EnumNames.hpp` (just verify non-empty and no crash) |
| I9 | Add a mock-loader integration test for `Initialize()`: provide a stub `GetProcAddress` that returns dummy function pointers and verify all wrappers dispatch through them without crashing |
| I10 | Add a minimal example program under `examples/` (a no-op render loop using `eglCreateContext` or an SDL2 hidden window) to verify the library links and initializes correctly on the CI platform |

---

## J — Emscripten / Platform

| # | Task |
|---|------|
| J1 | Add `#ifdef __EMSCRIPTEN__` guards in `Loader.hpp` to select the correct function-pointer loading strategy (WebGL2 does not use `eglGetProcAddress`) |
| J2 | Add documentation (and optionally a helper) for calling `LoadCurrentContext()` inside the Emscripten `EMSCRIPTEN_WEBGL_CONTEXT_RESTORED_CALLBACK` after `InstallEmscriptenContextLossCallbacks` |
| J3 | Add a CMake toolchain preset or a `cmake --preset emscripten` configuration that sets `CMAKE_TOOLCHAIN_FILE` and disables EGL-specific options |

---

## Summary counts

| Theme | Tasks |
|-------|-------|
| A — Typed handle types | 14 |
| B — Enum cleanup | 14 |
| C — std::span adoption | 11 |
| D — Template dispatch | 6 |
| E — Concepts | 5 |
| F — Build system | 7 |
| G — Debug & error handling | 8 |
| H — Code quality & naming | 12 |
| I — Tests | 10 |
| J — Emscripten / platform | 3 |
| **Total** | **90** |
