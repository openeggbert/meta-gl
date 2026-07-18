# NEXT.md — meta-gl 0.3.0 handoff

Updated on 2026-07-18 from the `develop` branch after the comprehensive
correctness, portability, packaging, and CI audit.

---

## 1. Project role

`meta-gl` is the low-level, procedural, type-safe C++23 layer over OpenGL,
OpenGL ES, and WebGL function pointers. It is designed to sit below `easy-gl`.

The dependency direction is:

```text
OpenGL / OpenGL ES / WebGL
              ↓
           meta-gl
              ↓
           easy-gl
```

`meta-gl` deliberately does not provide RAII resource ownership, engine
abstractions, or an object-oriented rendering API. Typed handles are lightweight
identifiers only; ownership belongs in `easy-gl`.

---

## 2. Release status

The source tree is prepared for version **0.3.0**:

- `project(meta-gl VERSION 0.3.0)` drives the CMake package version and library
  `VERSION`/`SOVERSION` metadata.
- `CHANGELOG.md` contains a dated `0.3.0` section.
- All 113 tasks in `plan.md` are resolved.
- The API verifier reports 358 wrappers, 360 loader names, and all 142 required
  OpenGL ES 2.0 entry points.
- The test suite covers GCC, Clang, MSVC, ASan/UBSan, static/shared builds,
  installation, package consumption, mock contexts, and headless EGL/Mesa.

The version is prepared but not published. Before release, require the current
`develop` CI run to be green, then create and push the annotated `v0.3.0` tag
and publish release notes from `CHANGELOG.md`.

---

## 3. Supported surface

- C++23, CMake 3.23 or newer.
- OpenGL ES 2.0 through 3.2 wrapper surface.
- Desktop OpenGL 3.3+ loading, including `glDepthRange` and `glClearDepth`
  adapters for the GLES-style public functions.
- WebGL/Emscripten loader and context-loss/context-restore integration.
- ANGLE detection through version, vendor, and renderer strings.
- 358 typed `metagl::gl*` wrappers.
- 98 enum classes and 15 lightweight handle/location/index types.
- Checked `std::span` and range-size conversions.
- Typed template dispatch for uniforms, vertex attributes, texture parameters,
  sampler parameters, and clear-buffer calls.
- Context status, generation tracking, capabilities, extension queries, and
  listener notifications.
- Optional buffered or immediate debug logging with `glGetError` checking.
- Static or shared builds, CMake package export, installed Khronos headers, and
  Doxygen generation.

---

## 4. Tests and CI

CTest currently defines five tests:

1. `metagl-compile-tests` — concepts, enum domains, bitfields, template
   dispatch, handle isolation, and enum-name coverage.
2. `metagl-mock-loader-test` — loading, availability, failure recovery,
   context lifecycle/listeners, extensions, desktop GL, ANGLE, and debug flush.
3. `metagl-api-consistency-test` — declaration, definition, loader-name, and
   GLES 2.0 minimum-function consistency.
4. `metagl-installed-package-test` — install plus an external
   `find_package(meta-gl CONFIG)` consumer build.
5. `metagl-egl-smoke-test` — real headless EGL/Mesa context on Linux.

GitHub Actions runs:

- Linux GCC static;
- Linux Clang shared;
- Windows MSVC shared;
- Linux Clang ASan and UBSan.

The Windows build stages the shared `meta-gl` runtime beside in-tree tests and
examples, so their executables can find the DLL.

Useful local verification:

```bash
cmake -S . -B build/release-check -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=ON \
  -DMETAGL_BUILD_TESTS=ON \
  -DMETAGL_BUILD_EXAMPLES=ON \
  -DMETAGL_BUILD_GPU_TESTS=ON
cmake --build build/release-check --parallel
ctest --test-dir build/release-check --output-on-failure

python3 tools/verify_api.py

cmake -S . -B build/docs -G Ninja -DMETAGL_BUILD_DOCS=ON
cmake --build build/docs --target metagl-docs
```

---

## 5. Compatibility with easy-gl

The audited `meta-gl` branch was compiled against the complete `easy-gl`
source tree. The audit did not introduce a new `easy-gl` compile failure. A
pre-existing `easy-gl` resource-test failure was reproduced on both its
baseline and the audited dependency, so it was not caused by `meta-gl`.

Version 0.3.0 does include deliberate source/API corrections:

- `AttribLocation` has signed storage and represents `-1` correctly;
- invalid enum-domain values were removed;
- stricter enum types and checked range conversions reject previously accepted
  invalid calls.

Compatibility overloads are retained where they are valid, including the
legacy draw-index and active-attribute call forms.

---

## 6. Known limitations

- Emscripten code and presets are present, but context loss/restore has not yet
  been exercised by an automated test in a real browser/WebGL runtime.
- The real-GPU CI smoke test currently covers Linux EGL/Mesa only. Native WGL,
  GLX, ANGLE, and vendor drivers are not runtime-tested in CI.
- `AllFunctionsLoaded()` answers whether every tracked loader slot is non-null;
  it cannot prove that a mock or driver implementation behaves correctly.
- Loader and context-state initialization is not a concurrent operation.
  Complete `Initialize()` or `RestoreCurrentContext()` before render threads
  call wrappers, as documented in `Loader.hpp`.
- Buffered Windows debug logging must be flushed explicitly with
  `metagl::FlushDebugLog()` before DLL teardown, or built with
  `METAGL_DEBUG_IMMEDIATE=ON`.

None of these limitations blocks the 0.3.0 release.

---

## 7. Recommended next work

### Release 0.3.0

After the release-preparation commit is green:

```bash
git tag -a v0.3.0 -m "Release 0.3.0"
git push origin v0.3.0
```

Then create the GitHub release from the `0.3.0` changelog section. Do not move
or recreate the existing `v0.2.0` tag.

### Browser runtime coverage

Add a small Emscripten/WebGL test page that:

1. creates a WebGL 2 context;
2. initializes `meta-gl` through `emscripten_webgl_get_proc_address`;
3. forces context loss and restore with `WEBGL_lose_context`;
4. verifies generation/status and listener ordering after reload.

This is the highest-value remaining platform test.

### Broader native runtime coverage

Add one of the following only when a reliable runner is available:

- Windows ANGLE or WGL smoke test;
- Linux desktop GL/GLX smoke test;
- macOS OpenGL compile/runtime coverage.

### Release automation

Optionally add a tag-triggered workflow that builds release archives, validates
the installed CMake package, and attaches artifacts to the GitHub release.

---

## 8. Architectural invariants

1. `meta-gl` must never depend on `easy-gl`.
2. Handle types do not own resources and must stay trivial/lightweight.
3. `detail::GlTable` remains the single function-pointer table.
4. A failed or lost context must not expose stale loader state or capabilities.
5. Restore must reload function pointers before restored listeners run.
6. Enum domains must model legal GL parameter domains, not merely share a raw
   underlying type.
7. Raw pointer overloads remain available where OpenGL uses `nullptr` to mean
   allocation without initial data.
8. No C++ modules, C++26-only features, heavy metaprogramming, or
   `std::expected`-based framework should be introduced.

---

## 9. Key files

| Path | Purpose |
|---|---|
| `include/metagl/Functions.hpp` | Public typed wrapper declarations and templates |
| `include/metagl/Enums.hpp` | OpenGL enum domains and bitfield traits |
| `include/metagl/Types.hpp` | GL aliases, handles, concepts, checked conversions |
| `include/metagl/Loader.hpp` | Initialization, restore, and function availability |
| `include/metagl/Context.hpp` | Context state and generation |
| `include/metagl/Capabilities.hpp` | Version/backend/extension capabilities |
| `include/metagl/ContextEvents.hpp` | Context lifecycle listeners |
| `include/metagl/Debug.hpp` | Optional debug wrapper layer |
| `include/metagl/Emscripten.hpp` | Browser context-loss callbacks |
| `src/Functions.cpp` | Loader table and 358 wrapper implementations |
| `src/Context.cpp` | Context/capability state and restore flow |
| `src/Debug.cpp` | Debug records, error checks, and flushing |
| `tools/verify_api.py` | API/loader/minimum-function consistency verifier |
| `.github/workflows/ci.yml` | Cross-platform build and test matrix |
| `plan.md` | Completed audit and improvement task history |
