# meta-gl

`meta-gl` is a low-level, type-safe C++23 wrapper targeting **OpenGL ES 3.0 or higher**.

OpenGL or OpenGL ES older than 3.0 are not supported.

It is the foundation layer used by [easy-gl](../easy-gl) and provides:

- Runtime OpenGL function loading via a host-supplied `GetProcAddress` callback.
- Type-safe `enum class` wrappers for OpenGL constants (buffer targets, shader types, texture formats, etc.).
- Thin inline-style wrapper functions in the `metagl` namespace (`metagl::GlBindBuffer`, `metagl::GlClear`, …).
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

## Initialization

Before calling any `metagl::Gl*` function, initialize the function pointer table by passing a `GetProcAddress`-style callback:

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
| `metagl/Types.hpp` | Primitive GL type aliases (`GLuint`, `GLint`, `GlGetProcAddressFn`, …) |
| `metagl/Enums.hpp` | Type-safe `enum class` wrappers for GL constants |
| `metagl/Functions.hpp` | Declarations of all `metagl::Gl*` wrapper functions |
| `metagl/Loader.hpp` | `metagl::Initialize()` / `metagl::IsInitialized()` |
| `metagl/metagl.hpp` | Umbrella header — include this |

### Example

```cpp
#include <metagl/metagl.hpp>

// After Initialize():
metagl::GlClearColor(0.2f, 0.3f, 0.3f, 1.0f);
metagl::GlClear(metagl::ClearBufferBit::Color | metagl::ClearBufferBit::Depth);

metagl::GLuint vao = 0;
metagl::GlGenVertexArrays(1, &vao);
metagl::GlBindVertexArray(vao);

metagl::GLuint shader = metagl::GlCreateShader(metagl::ShaderType::Vertex);
```

## Design notes

- Raw OpenGL values (`GL_ARRAY_BUFFER`, `GL_VERTEX_SHADER`, …) stay **internal** to meta-gl.
- Callers use `enum class` values; conversions to `GLenum` happen inside `metagl::detail`.
- No OpenGL headers are exposed in public headers.
- Only OpenGL ES 3.0 or higher is supported; plain OpenGL and OpenGL ES older than 3.0 are not supported.
