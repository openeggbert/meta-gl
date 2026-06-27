# meta-gl

`meta-gl` is a low-level, type-safe C++23 wrapper targeting **OpenGL ES 2.0 or higher**.

OpenGL or OpenGL ES older than 2.0 are not supported.

It is the foundation layer used by [easy-gl](../easy-gl) and provides:

- Runtime OpenGL function loading via a host-supplied `GetProcAddress` callback.
- Type-safe `enum class` wrappers for OpenGL constants (buffer targets, shader types, texture formats, etc.).
- Thin inline-style wrapper functions in the `metagl` namespace (`metagl::glBindBuffer`, `metagl::glClear`, …).
- No windowing, no context creation — the host application owns the GL context lifecycle.

## Architecture

```
Host application
    └── provides GL context + GetProcAddress callback
            └── easy-gl   (OOP wrapper, namespace easygl)
                    └── meta-gl  (function pointers + type-safe API, namespace metagl)
                            └── actual OpenGL driver
```

## Requirements

- C++23 compiler
- CMake `3.23+`
- A host-side GL context (provided externally)

## Build

`meta-gl` is intended to be consumed as a CMake subdirectory dependency:

```cmake
add_subdirectory(../meta-gl meta-gl)
target_link_libraries(my-target PRIVATE meta-gl::meta-gl)
```

It can also be built standalone:

```bash
cmake -S . -B build
cmake --build build
```

By default a **static** library is produced. Pass `-DBUILD_SHARED_LIBS=ON` to build a shared library instead:

```bash
cmake -S . -B build -DBUILD_SHARED_LIBS=ON
cmake --build build
```

### CMake presets

`CMakePresets.json` ships four configure/build presets:

| Preset | Description |
|--------|-------------|
| `default` | Debug build, host compiler |
| `release` | Optimized release, host compiler |
| `sanitize` | Debug + ASan/UBSan |
| `emscripten` | WebAssembly via Emscripten (requires `EMSDK` env var) |

```bash
cmake --preset default
cmake --build --preset default

# Emscripten (set EMSDK first)
cmake --preset emscripten
cmake --build --preset emscripten
```

### Emscripten / WebGL

Use the Emscripten toolchain wrappers:

```bash
emcmake cmake -S . -B build-wasm
emmake cmake --build build-wasm
```

Link your application with `-lGL` (Emscripten maps this to WebGL automatically):

```cmake
target_link_libraries(my-app PRIVATE meta-gl::meta-gl -lGL)
```

After creating a WebGL context, install the context-loss callbacks so meta-gl
can track `webglcontextlost` / `webglcontextrestored` browser events:

```cpp
#include <metagl/metagl.hpp>  // includes Emscripten.hpp automatically

metagl::Initialize(emscripten_webgl_get_proc_address);
metagl::InstallEmscriptenContextLossCallbacks("#canvas");
```

When context is restored, reload function pointers before notifying listeners:

```cpp
// Inside your webglcontextrestored handler:
metagl::LoadCurrentContext(emscripten_webgl_get_proc_address);
metagl::NotifyContextRestored();
```

## Initialization

Before calling any `metagl::gl*` function, initialize the function pointer table by passing a `GetProcAddress`-style callback:

```cpp
#include <metagl/metagl.hpp>

bool ok = metagl::Initialize(my_get_proc_address);
```

The callback type is:

```cpp
using GlGetProcAddressFn = void* (*)(const char* name);
```

## Public API

All symbols live in the `metagl` namespace under `include/metagl/`:

| Header | Contents |
|---|---|
| `metagl/metagl.hpp` | Umbrella header — include this |
| `metagl/Types.hpp` | Primitive GL type aliases, handle structs (`ShaderId`, `BufferId`, …), concepts (`GlHandle`, `GlEnum`, `GlBitfield`, `SpanCompatible`) |
| `metagl/Enums.hpp` | Type-safe `enum class` wrappers for all GL constants |
| `metagl/Functions.hpp` | All 358 `metagl::gl*` wrapper functions plus typed template dispatch helpers |
| `metagl/Loader.hpp` | `Initialize()`, `IsInitialized()`, `AllFunctionsLoaded()`, `IsFunctionAvailable()` |
| `metagl/Context.hpp` | `ContextInfo` struct, `GetContextInfo()`, `GetContextStatus()`, `MarkContextLost/Restored()` |
| `metagl/Capabilities.hpp` | `Capabilities` struct, `GetCapabilities()`, `SupportsGLES*()`, `HasExtension()` |
| `metagl/ContextEvents.hpp` | `ContextListener` interface, `AddContextListener()`, `NotifyContextLost/Restored()` |
| `metagl/EnumNames.hpp` | `to_string()` overloads for all enum classes and handle types (opt-out: `METAGL_NO_ENUM_NAMES`) |
| `metagl/Debug.hpp` | GL call logging infrastructure controlled by `METAGLDEBUG` (opt-out: `METAGL_NO_DEBUG`) |
| `metagl/Emscripten.hpp` | `InstallEmscriptenContextLossCallbacks()` — included automatically when `__EMSCRIPTEN__` is defined |

### Example

```cpp
#include <metagl/metagl.hpp>

// After Initialize():
metagl::glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
metagl::glClear(metagl::ClearBufferBit::Color | metagl::ClearBufferBit::Depth);

metagl::VertexArrayId vao{};
metagl::glGenVertexArrays(1, &vao.value);
metagl::glBindVertexArray(vao);

metagl::ShaderId shader = metagl::glCreateShader(metagl::ShaderType::Vertex);
```

## Design notes

- Raw OpenGL values (`GL_ARRAY_BUFFER`, `GL_VERTEX_SHADER`, …) stay **internal** to meta-gl.
- Callers use `enum class` values; conversions to `GLenum` happen inside `metagl::detail`.
- No OpenGL headers are exposed in public headers.
- Only OpenGL ES 3.0 or higher is supported; plain OpenGL and OpenGL ES older than 3.0 are not supported.
