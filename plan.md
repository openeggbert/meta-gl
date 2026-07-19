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
| A13 | ✅ Add signed `struct AttribLocation { GLint value{-1}; };`, preserving explicit construction from `GLint`/`GLuint`; use separate `ActiveAttribIndex` for `glGetActiveAttrib` enumeration |
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
| C1 | ✅ Wrap all `glGen*` functions with `std::span<HandleType>` overloads (`glGenBuffers`, `glGenTextures`, `glGenFramebuffers`, `glGenRenderbuffers`, `glGenSamplers`, `glGenVertexArrays`, `glGenQueries`, `glGenTransformFeedbacks`, `glGenProgramPipelines`) |
| C2 | ✅ Wrap all `glDelete*` functions with `std::span<const HandleType>` overloads (same list as C1) |
| C3 | ✅ Add `std::span<const T>` (`SpanCompatible T`) overload for `glBufferData` |
| C4 | ✅ Add `std::span<const T>` (`SpanCompatible T`) overload for `glBufferSubData` |
| C5 | ✅ Add `std::span<const T>` (`SpanCompatible T`) overloads for `glTexImage2D`, `glTexImage3D`, `glTexSubImage2D`, `glTexSubImage3D` (raw void* overloads preserved for nullptr/mutable storage) |
| C6 | ✅ Add `std::span<const T>` (`SpanCompatible T`) overloads for `glCompressedTexImage2D/3D` and `glCompressedTexSubImage2D/3D`; `imageSize` derived from `pixels.size_bytes()` |
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
| D5 | ✅ Add typed `glClearBuffer<T>` dispatch overloads for `glClearBufferfv` / `glClearBufferiv` / `glClearBufferuiv`, using the exact float, signed-integer, and unsigned-integer target domains |
| D6 | ✅ Add `glGetVertexAttrib<T>(AttribLocation, VertexAttribParameter, T* params)` template dispatch for `glGetVertexAttribfv` / `glGetVertexAttribiv` / `glGetVertexAttribIiv` / `glGetVertexAttribIuiv` |

---

## E — Concepts

| # | Task |
|---|------|
| E1 | ✅ Add `GlHandle` concept (requires `.value` of type `GLuint`) to constrain future template helpers that accept any handle type |
| E2 | ✅ Add explicit `GlBitfieldTraits` opt-in because `GLenum` and `GLbitfield` alias the same type; generic operators are limited to real masks and `~` is clamped to valid bits |
| E3 | ✅ Add `GlEnum` concept for non-bitfield `GLenum` domains |
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
| G1 | ✅ Add `assert(detail::g_gl.FunctionName != nullptr)` guards inside all 358 wrapper functions via sed; added `<cassert>` include; no-op in NDEBUG builds |
| G2 | ✅ Add `check_gl_error()` called after each wrapper via `METAGL_DEBUG_LOG*` macros when `METAGLDEBUG` is defined; errors printed immediately to stderr with enum name; `set_get_error_fn()` registered in `Initialize()` |
| G3 | ✅ Add `FlushOnExit` RAII guard (static destructor) in `Debug.cpp` so buffered GL calls are flushed to stderr on normal program exit |
| G4 | ✅ Flush the debug buffer immediately on every call when `METAGLDEBUG_IMMEDIATE` is defined (alongside `METAGLDEBUG`); documented in `Debug.hpp` header comment |
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
| H12 | ✅ Preserve the raw-name `glCopyImageSubData` compatibility overload and document its limitations; L2 adds typed texture/renderbuffer overloads without removing this downstream-compatible path |

---

## I — Tests

| # | Task |
|---|------|
| I1 | ✅ Add a `tests/` directory and a basic `CMakeLists.txt` under it, wired into the root via `add_subdirectory(tests)` guarded by `BUILD_TESTING` |
| I2 | ✅ Add compile-time tests (`static_assert`) verifying that template dispatch (`glGetUniform<T>`, `glGetnUniform<T>`, `glTexParameter<T>`, `glSamplerParameter<T>`, `glClearBuffer<T>`, `glGetVertexAttrib<T>`) resolves without ambiguity for float/int/uint |
| I3 | ✅ Add compile-time tests verifying that bitfield `operator|` / `&` / `~` compile and preserve the enum type for all bitfield enums |
| I4 | ✅ Add compile-time tests verifying that mixing handle types (`ShaderId` vs `ProgramId`) does not compile (`static_assert(!std::is_convertible_v<...>)` / `!std::is_constructible_v`) |
| I5 | ✅ Context lifecycle tests in `test_mock_loader.cpp`: verifies Lost/Restored/Current transitions, `IsContextLost()`, generation counter increment after `LoadCurrentContext()` |
| I6 | ✅ ContextEvents tests with MockListener: single/multiple listeners, NotifyContextLost/Restored dispatch, removed listener receives no further notifications |
| I7 | ✅ HasExtension/GetCapabilities tests: verifies empty extension list from default stub, re-initializes with stub advertising `GL_EXT_texture_filter_anisotropic`, checks HasExtension true/false, SupportsGLES20/30/31/32 |
| I8 | ✅ Runtime tests for all 89+ `to_string()` overloads in `EnumNames.hpp` — verify non-empty, non-"?" for one representative value per enum and all 14 handle types; run via CTest |
| I9 | ✅ Mock-loader integration test (`test_mock_loader.cpp`): stub GetProcAddress returns stub_GetString/GetIntegerv/GetStringi + no-ops; verifies Initialize, IsInitialized, AllFunctionsLoaded, ContextStatus::Current, version parsing (ES 3.0), capabilities |
| I10 | ✅ Added `examples/hello_metagl.cpp` with stub GetProcAddress; prints version/vendor/renderer/API/capabilities/enum names; `BUILD_EXAMPLES=ON` CMake option; no GPU required |

---

## J — Emscripten / Platform

| # | Task |
|---|------|
| J1 | ✅ Document and use `emscripten_webgl_get_proc_address`; Emscripten callback now calls atomic `RestoreCurrentContext` rather than relying on caller reload |
| J2 | ✅ Expanded `Emscripten.hpp` lifecycle documentation and enforced reload-before-listener order in the implementation |
| J3 | ✅ Add `CMakePresets.json` with `default`, `release`, `sanitize`, and `emscripten` presets; `emscripten` sets toolchain via `$env{EMSDK}`; documented in README.md |
| J4 | ✅ Detect ANGLE in version/vendor/renderer strings, expose `Capabilities::angle` / `IsAngle()`, document backend-dependent availability, and cover detection with a mock context |
| J5 | ✅ Support host-provided WGL/GLX/SDL/GLFW loaders, detect and parse desktop GL 3.3+/4.x strings, keep GLES flags separate, adapt `glDepthRange`/`glClearDepth`, relax only GLES-specific shader entry points for desktop, and cover the path with a GL 4.6 mock |

---

## K — 2026 Comprehensive Audit

| # | Task |
|---|------|
| K1 | ✅ Add atomic `RestoreCurrentContext`, reload Emscripten entry points before callbacks, and finish restored dispatch in `Current` |
| K2 | ✅ Clear stale status/capabilities after loader failure; deduplicate listeners and snapshot dispatch to support self-removal |
| K3 | ✅ Replace underlying-type bitfield detection with explicit traits and clamp `operator~` to each mask's valid bits |
| K4 | ✅ Remove invalid draw/pixel enum values; add `IndexType`, signed `AttribLocation`, and `ActiveAttribIndex` compatibility APIs |
| K5 | ✅ Add precise texture binding and typed filter/wrap/compare/swizzle parameter overloads while preserving low-level signatures |
| K6 | ✅ Add checked span/range conversions and reject incomplete uniform vectors/matrices instead of truncating |
| K7 | ✅ Make `IsFunctionAvailable` use non-allocating heterogeneous lookup and canonicalize duplicate query-token names |
| K8 | ✅ Install GLES/KHR headers and licenses; complete `khrplatform.h` so installed headers coexist with EGL |
| K9 | ✅ Scope CMake options, preserve standalone aliases, export Windows shared symbols, and use same-minor `0.x` package compatibility |
| K10 | ✅ Add a real debug-logging option and type-correct mock functions; compile tests/examples with warnings and standard C++ mode |
| K11 | ✅ Add CI plus an API verifier covering 358 wrappers, 360 loader names (including desktop fallbacks), and 142 GLES 2.0 minimum functions |
| K12 | ✅ Add installed-package and optional real headless EGL/Mesa smoke tests |
| K13 | ✅ Correct README/changelog claims and add a buildable Doxygen target |
| K14 | ✅ Compile all of easy-gl against the audit branch and compare its existing resource-test failure against the baseline |
| K15 | ✅ Flatten the `GetParameter` name lookup so MSVC does not exceed its nested-block compiler limit |
| K16 | ✅ Enable MSVC's conforming preprocessor for the C++23 `__VA_OPT__` debug macros |
| K17 | ✅ Remove the extension mock loader's incompatible `glGetError` function-pointer call |
| K18 | ✅ Add explicit debug-log flushing and avoid Windows DLL teardown I/O under the loader lock |
| K19 | ✅ Stage the Windows shared-library runtime beside in-tree tests and examples |
| K20 | ✅ Prepare the 0.3.0 release metadata and replace the stale NEXT.md handoff |

---

## L — 2026 Follow-up Deep Analysis — Implemented Findings

The complete supporting analysis is recorded in [`analysis.md`](analysis.md).
These changes exist only in the isolated `feature/followup-audit` worktree
until the remaining release and downstream-compatibility tasks below are
resolved. No item in this section authorizes a merge by itself.

| # | Implemented item | Decision |
|---|------------------|----------|
| L1 | ✅ Replace `glClearBufferfi` with a safe depth/stencil-only wrapper, split the other clear-buffer calls into exact value-specific target domains, and cover forwarding plus type isolation with tests. See [analysis finding 1](analysis.md#finding-1). | Implemented; merge blocked by R01–R03 |
| L2 | ✅ Add an exact `ImageCopyTextureTarget` plus typed overloads for all four texture/renderbuffer endpoint combinations, retain the existing raw overload for downstream compatibility, and verify forwarding plus the legacy call shape used by `easy-gl`. See [analysis finding 2](analysis.md#finding-2). | Implemented in the feature worktree |
| L3 | ✅ Clear current context identity/capabilities and function availability on context loss, gate loader queries on initialization, add initialized-context Debug assertions to all wrappers, and verify loss/reload state transitions. See [analysis finding 3](analysis.md#finding-3). | Implemented in the feature worktree |
| L4 | ✅ Add bootstrap loading, strict version/API detection, exact cumulative native GLES 2.0/3.0/3.1/3.2 mandatory-entry validation, WebGL-subset and desktop 3.3+ validation, staged publication, and boundary/failure tests. See [analysis finding 4](analysis.md#finding-4). | Implemented in the feature worktree |

---

## R — Remaining Work — Individual Tasks

Every remaining action found in `analysis.md` and `NEXT.md` is represented
below by one stable task ID. A decision task must be completed before its
dependent implementation tasks. A conditional task may be closed as
`not applicable` only by recording the decision that made it unnecessary.

Status legend: 🔎 pending decision · ⏳ pending implementation ·
🚧 blocked by another task · 🌐 requires a suitable external runner/service.

### R01–R20 — 0.3.0 release gates and release actions

| # | Individual task | Completion condition | Source | Status |
|---|-----------------|----------------------|--------|--------|
| R01 | Choose the L1 downstream strategy: compatibility overloads in `meta-gl` or a coordinated `easy-gl` migration. | The selected option and rejected alternative are recorded with source/ABI consequences. | [Finding 1](analysis.md#finding-1) | 🔎 Pending decision |
| R02 | Implement the selected L1 compatibility or migration strategy only in isolated feature worktrees. | Both repositories use one agreed clear-buffer API without unsafe casts. | [Finding 1](analysis.md#finding-1) | 🚧 Blocked by R01 |
| R03 | Build and test the complete `easy-gl` tree against the final L1 API. | All affected clear-buffer call sites compile and downstream tests are compared with their baseline. | [Finding 1](analysis.md#finding-1) | 🚧 Blocked by R02 |
| R04 | Define the pre-1.0 ABI numbering and `SOVERSION` policy. | The policy explicitly covers incompatible `0.x` minor releases. | [Finding 5](analysis.md#finding-5) | 🔎 Pending decision |
| R05 | Implement the selected ABI/`SOVERSION` policy in CMake. | Produced shared-library filenames and package metadata match R04. | [Finding 5](analysis.md#finding-5) | 🚧 Blocked by R04 |
| R06 | Add an automated Linux SONAME assertion. | A shared-build test fails when the emitted SONAME differs from R04. | [Finding 5](analysis.md#finding-5) | 🚧 Blocked by R05 |
| R07 | Choose the Release-build failure contract for invalid sizes, incomplete vectors/matrices, and non-false transpose. | Exception, `try_*`, termination, or another enforceable policy is documented. | [Finding 6](analysis.md#finding-6) | 🔎 Pending decision |
| R08 | Enforce checked `size_t`/range-to-`GLsizei` conversion in Release builds. | Overflow cannot reach a GL call and follows the R07 policy. | [Finding 6](analysis.md#finding-6) | 🚧 Blocked by R07 |
| R09 | Enforce vector/matrix divisibility and transpose preconditions in Release builds. | Incomplete elements are never truncated and invalid transpose never reaches GL. | [Finding 6](analysis.md#finding-6) | 🚧 Blocked by R07 |
| R10 | Add negative Release tests for every checked precondition. | Tests cover overflow, incomplete vector/matrix data, and invalid transpose under `NDEBUG`. | [Finding 6](analysis.md#finding-6) | 🚧 Blocked by R08–R09 |
| R11 | Synchronize public documentation and `noexcept` declarations with the selected invalid-input contract. | Headers, README, Doxygen, and behavior state the same contract. | [Finding 6](analysis.md#finding-6) | 🚧 Blocked by R07–R10 |
| R12 | Make the installed-package consumer call an out-of-line `meta-gl` symbol and execute it. | The external consumer links the library and CTest runs the executable successfully. | [Finding 7](analysis.md#finding-7) | ⏳ Pending |
| R13 | Exercise the installed-package consumer with a static library. | A clean external static consumer configures, links, and runs. | [Finding 7](analysis.md#finding-7) | 🚧 Blocked by R12 |
| R14 | Exercise the installed-package consumer with a shared library on Unix. | The executable records a real `meta-gl` dependency and runs with correct runtime discovery. | [Finding 7](analysis.md#finding-7) | 🚧 Blocked by R12 |
| R15 | Exercise an installed shared-package consumer on Windows. | The installed DLL is discovered without relying on an in-tree staging shortcut. | [Finding 7](analysis.md#finding-7) | 🌐 Requires Windows runner; blocked by R12 |
| R16 | Record the 0.3.0 release disposition and accepted residual risks. | Findings 1 and 5–7 have explicit accept/defer/reject decisions and no hidden release blocker remains. | [Finding 21](analysis.md#finding-21) | 🚧 Blocked by R01–R15 |
| R17 | Update 0.3.0 release notes and handoff metadata after the release decision. | Changelog, README, `NEXT.md`, version claims, and risk statements agree. | [Finding 21](analysis.md#finding-21) | 🚧 Blocked by R16 |
| R18 | Run the final clean supported build/test matrix. | Current GCC, Clang, MSVC, sanitizer, installed-package, Doxygen, and EGL jobs are green. | [Finding 21](analysis.md#finding-21) | 🚧 Blocked by R17 |
| R19 | Create and push the annotated `v0.3.0` tag. | The tag points to the approved, green release commit and the existing `v0.2.0` tag is unchanged. | Previous `NEXT.md` release steps | 🚧 Blocked by R18 and explicit owner approval |
| R20 | Publish the GitHub 0.3.0 release. | Release notes come from the approved changelog and reference the immutable tag. | Previous `NEXT.md` release steps | 🌐 Blocked by R19 |

### R21–R35 — Exact public API domains

| # | Individual task | Completion condition | Source | Status |
|---|-----------------|----------------------|--------|--------|
| R21 | Choose the compatibility/deprecation policy for an exact `glMemoryBarrierByRegion` mask domain. | The legal bit set and treatment of the old broad call shape are recorded. | [Finding 8](analysis.md#finding-8) | 🔎 Pending decision |
| R22 | Implement, test, and document the exact `glMemoryBarrierByRegion` mask domain. | New code cannot pass disallowed bits; compile/runtime coverage includes every legal bit and `ALL`. | [Finding 8](analysis.md#finding-8) | 🚧 Blocked by R21 |
| R23 | Add every legal object identifier to `DebugObjectLabel`. | Framebuffer, renderbuffer, texture, transform feedback, and all previously supported identifiers are represented. | [Finding 9](analysis.md#finding-9) | ⏳ Pending |
| R24 | Test and document the complete object-label domain. | Each identifier is compile-time covered and representative forwarding is runtime-tested. | [Finding 9](analysis.md#finding-9) | 🚧 Blocked by R23 |
| R25 | Choose the typed API model for default-framebuffer invalidation. | Separate domain, overload, or validated union is selected without weakening named-framebuffer safety. | [Finding 10](analysis.md#finding-10) | 🔎 Pending decision |
| R26 | Implement default-framebuffer invalidation with a compatible migration path. | `GL_COLOR`, `GL_DEPTH`, and `GL_STENCIL` are expressible only in their legal context. | [Finding 10](analysis.md#finding-10) | 🚧 Blocked by R25 |
| R27 | Add compile/runtime tests and documentation for both default and named framebuffer invalidation. | Legal tokens forward correctly and cross-domain misuse is rejected. | [Finding 10](analysis.md#finding-10) | 🚧 Blocked by R26 |
| R28 | Choose setter/query texture-parameter domains and the legacy-overload deprecation policy. | Writable and query-only token sets plus source-compatibility rules are recorded. | [Finding 11](analysis.md#finding-11) | 🔎 Pending decision |
| R29 | Implement the exact writable texture-parameter API. | Setter overloads cannot accept query-only tokens and getters retain the complete query domain. | [Finding 11](analysis.md#finding-11) | 🚧 Blocked by R28 |
| R30 | Add rejection, forwarding, compatibility, and documentation coverage for texture parameters. | Tests prove the setter/query separation and any retained legacy path. | [Finding 11](analysis.md#finding-11) | 🚧 Blocked by R29 |
| R31 | Choose the exact immutable-storage internal-format representation. | One domain or overload policy covers all legal compressed and uncompressed sized formats. | [Finding 12](analysis.md#finding-12) | 🔎 Pending decision |
| R32 | Implement compressed-format support in `glTexStorage2D/3D`. | All selected legal format families compile without raw casts. | [Finding 12](analysis.md#finding-12) | 🚧 Blocked by R31 |
| R33 | Test and document immutable-storage format coverage. | Compile tests cover compressed/uncompressed acceptance and reject unsized/illegal formats. | [Finding 12](analysis.md#finding-12) | 🚧 Blocked by R32 |
| R34 | Add a transform-feedback primitive domain and compatible overload limited to points, lines, and triangles. | Invalid general primitive modes cannot enter the exact overload. | [Finding 13](analysis.md#finding-13) | ⏳ Pending |
| R35 | Test and document transform-feedback primitive isolation and forwarding. | All three legal modes forward and representative illegal modes fail at compile time. | [Finding 13](analysis.md#finding-13) | 🚧 Blocked by R34 |

### R36–R59 — Loader portability, ABI, context, listeners, and debug behavior

| # | Individual task | Completion condition | Source | Status |
|---|-----------------|----------------------|--------|--------|
| R36 | Decide which loader adapters are library-owned versus host-owned. | EGL, GLX, GLFW, SDL, and WGL each have an explicit supported/host-supplied decision. | [Finding 14](analysis.md#finding-14) | 🔎 Pending decision |
| R37 | Formalize the generic loader callback contract. | Documentation defines current-context, address lifetime, function-pointer conversion, failure, and thread requirements. | [Finding 14](analysis.md#finding-14) | ⏳ Pending |
| R38 | Implement a WGL adapter with `opengl32.dll` core fallback and sentinel rejection. | `nullptr`, 1, 2, 3, and `-1` results are rejected and core symbols use the fallback. | [Finding 14](analysis.md#finding-14) | 🚧 Conditional on R36 |
| R39 | Add automated WGL adapter tests. | Windows tests cover extension lookup, core fallback, missing symbols, and every sentinel. | [Finding 14](analysis.md#finding-14) | 🌐 Conditional on R38; requires Windows runner |
| R40 | Add and test a library-owned EGL adapter if selected. | The adapter loads core and extension entry points according to R37. | [Finding 14](analysis.md#finding-14) | 🚧 Conditional on R36 |
| R41 | Add and test a library-owned GLFW adapter if selected. | The adapter compiles without unsafe user-side callback casts. | [Finding 14](analysis.md#finding-14) | 🚧 Conditional on R36 |
| R42 | Add and test a library-owned SDL adapter if selected. | The adapter compiles without unsafe user-side callback casts. | [Finding 14](analysis.md#finding-14) | 🚧 Conditional on R36 |
| R43 | Add and test a library-owned GLX adapter if selected. | The adapter handles the platform function-pointer contract documented by R37. | [Finding 14](analysis.md#finding-14) | 🚧 Conditional on R36 |
| R44 | Define the supported public binary ABI symbol list. | Only documented public functions/types intended for binary use are listed. | [Finding 15](analysis.md#finding-15) | 🔎 Pending decision |
| R45 | Introduce and apply a central `METAGL_API` export/import macro. | Every out-of-line public symbol is annotated and internal symbols are not. | [Finding 15](analysis.md#finding-15) | 🚧 Blocked by R44 |
| R46 | Enable hidden visibility and remove `WINDOWS_EXPORT_ALL_SYMBOLS`. | Static/shared Linux and Windows builds export only the R44 surface. | [Finding 15](analysis.md#finding-15) | 🚧 Blocked by R45 |
| R47 | Add a Unix exported-symbol allowlist test. | CI fails on missing public or newly leaked internal symbols. | [Finding 15](analysis.md#finding-15) | 🚧 Blocked by R46 |
| R48 | Add a Windows exported-symbol allowlist test. | MSVC shared CI fails on missing public or newly leaked internal symbols. | [Finding 15](analysis.md#finding-15) | 🌐 Blocked by R46; requires Windows runner |
| R49 | Establish an ABI baseline and compatibility check. | An approved tool compares releases using the R44 public surface. | [Finding 5](analysis.md#finding-5) and [finding 15](analysis.md#finding-15) | 🚧 Blocked by R44–R48 |
| R50 | Decide the supported single-context, multi-context, and threading model. | Ownership and synchronization guarantees are explicit for loader, context, listeners, and debug state. | [Finding 16](analysis.md#finding-16) | 🔎 Pending decision |
| R51 | Implement and document the selected context-state model. | Global, thread-local, or explicit state matches R50 everywhere without mixed semantics. | [Finding 16](analysis.md#finding-16) | 🚧 Blocked by R50 |
| R52 | Add tests for every context/thread scenario promised by R50. | Supported transitions pass and unsupported concurrent use is explicitly guarded or documented. | [Finding 16](analysis.md#finding-16) | 🚧 Blocked by R51 |
| R53 | Define listener ownership, lifetime, removal, reentrancy, and exception rules. | The contract covers self-removal, destruction of another listener, and exceptions during partial restore. | [Finding 17](analysis.md#finding-17) | 🔎 Pending decision |
| R54 | Make dispatch safe when a queued listener is removed or destroyed. | No callback is made through an invalid snapshot pointer. | [Finding 17](analysis.md#finding-17) | 🚧 Blocked by R53 |
| R55 | Implement the selected restore-listener exception semantics. | Published status and partially restored resources follow the R53 rule after an exception. | [Finding 17](analysis.md#finding-17) | 🚧 Blocked by R53 |
| R56 | Add listener lifetime, removal, reentrancy, and exception tests. | Tests reproduce the original hazards and verify R54–R55. | [Finding 17](analysis.md#finding-17) | 🚧 Blocked by R54–R55 |
| R57 | Decide whether debug logging may consume application `glGetError` state. | Default/opt-in behavior, reporting, and queue-draining limits are recorded. | [Finding 18](analysis.md#finding-18) | 🔎 Pending decision |
| R58 | Implement and document the selected debug-error policy. | Debug checks follow R57 and expose no undocumented error-state mutation. | [Finding 18](analysis.md#finding-18) | 🚧 Blocked by R57 |
| R59 | Add tests for debug error ownership, multiple queued errors, and reporting. | Tests verify both configured modes and the documented drain limit. | [Finding 18](analysis.md#finding-18) | 🚧 Blocked by R58 |

### R60–R75 — Generation, runtime coverage, release automation, and shutdown

| # | Individual task | Completion condition | Source | Status |
|---|-----------------|----------------------|--------|--------|
| R60 | Define the generator scope and authoritative Khronos inputs. | Generated versus hand-maintained files and policy data have explicit ownership. | [Finding 19](analysis.md#finding-19) | 🔎 Pending decision |
| R61 | Pin `gl.xml` and make generator output reproducible. | The registry revision/license are recorded and two clean runs produce identical output. | [Finding 19](analysis.md#finding-19) | 🚧 Blocked by R60 |
| R62 | Generate function declarations, loader slots/calls, and version-required sets. | Generated output preserves all supported 358 wrappers and exact version metadata. | [Finding 19](analysis.md#finding-19) | 🚧 Blocked by R61 |
| R63 | Generate or verify exact signatures, enum names, and enum coverage. | CI detects signature drift, missing names, and unexpected registry differences. | [Finding 19](analysis.md#finding-19) | 🚧 Blocked by R61 |
| R64 | Add a small typed-policy layer for strong domains and compatibility overloads. | Custom safety decisions survive regeneration without editing generated files. | [Finding 19](analysis.md#finding-19) | 🚧 Blocked by R62–R63 |
| R65 | Add a CI regeneration/no-diff guard. | CI fails whenever committed generated output is stale. | [Finding 19](analysis.md#finding-19) | 🚧 Blocked by R64 |
| R66 | Add a real-browser WebGL 2 loss/restore test using `WEBGL_lose_context`. | It verifies initialization, invalidation, reload, generation, status, and listener ordering. | [Finding 20](analysis.md#finding-20) | 🌐 Requires Emscripten/browser runner |
| R67 | Add a Windows WGL runtime smoke test. | A real context covers loader core fallback and at least one rendered/queried operation. | [Finding 20](analysis.md#finding-20) | 🌐 Requires Windows OpenGL runner |
| R68 | Add a Windows ANGLE runtime smoke test. | A real ANGLE context verifies backend detection and GLES loading. | [Finding 20](analysis.md#finding-20) | 🌐 Requires ANGLE-enabled runner |
| R69 | Add a Linux desktop GL/GLX runtime smoke test. | A real desktop context exercises version validation and depth adapters. | [Finding 20](analysis.md#finding-20) | 🌐 Requires GLX-capable runner |
| R70 | Add macOS OpenGL compile/runtime coverage. | The supported macOS compiler and context path configure, build, and run. | [Finding 20](analysis.md#finding-20) | 🌐 Requires macOS runner |
| R71 | Add at least one non-Mesa vendor-driver runtime job. | The selected NVIDIA/AMD/Intel vendor path and maintenance expectation are documented. | [Finding 20](analysis.md#finding-20) | 🌐 Requires managed GPU runner |
| R72 | Add a tag-triggered release workflow. | Only approved version tags start the workflow and untrusted/manual tags cannot overwrite a release. | Previous `NEXT.md` release automation | ⏳ Pending |
| R73 | Build release archives and validate their installed CMake packages. | Each supported archive installs and an external consumer links and runs against it. | Previous `NEXT.md` release automation | 🚧 Blocked by R72 |
| R74 | Attach validated artifacts and changelog-derived notes to the GitHub release. | Workflow output is checksummed, immutable, and associated with the matching tag. | Previous `NEXT.md` release automation | 🌐 Blocked by R73 |
| R75 | Decide and verify the Windows buffered-debug-log shutdown policy. | Explicit pre-teardown flush remains a tested contract, or a safe automatic lifecycle replaces it; MSVC shared tests cover the selected behavior. | Previous `NEXT.md` known limitation | 🌐 Requires Windows runner |

---

## Summary counts

| Theme | Completed | Remaining | Total |
|-------|----------:|----------:|------:|
| A–K — Original plan and comprehensive audit | 113 | 0 | 113 |
| L — Implemented follow-up findings | 4 | 0 | 4 |
| R — Remaining individual tasks | 0 | 75 | 75 |
| **Total** | **117** | **75** | **192** |
