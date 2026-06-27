/**
 * @file Loader.hpp
 * @brief GL function-pointer loader: Initialize, LoadCurrentContext, and query helpers.
 *
 * The loader fills the internal `detail::GlTable` with function pointers obtained
 * from the platform's `GetProcAddress`-equivalent.  After a successful
 * @ref Initialize call, all `metagl::gl*` wrapper functions are safe to call
 * from the same thread that owns the GL context.
 *
 * Typical usage:
 * @code
 * // Platform-agnostic initialization — choose the right loader for the build target:
 * #ifdef __EMSCRIPTEN__
 *     // WebGL: use emscripten_webgl_get_proc_address, NOT eglGetProcAddress.
 *     // The WebGL security model restricts which extensions eglGetProcAddress exposes;
 *     // emscripten_webgl_get_proc_address returns the full set available in the browser.
 *     metagl::Initialize(
 *         reinterpret_cast<metagl::GlGetProcAddressFn>(emscripten_webgl_get_proc_address));
 * #else
 *     // Native OpenGL ES: any of these work depending on your windowing library:
 *     //   SDL2:  SDL_GL_GetProcAddress
 *     //   GLFW:  glfwGetProcAddress
 *     //   EGL:   eglGetProcAddress
 *     metagl::Initialize(eglGetProcAddress);
 * #endif
 * @endcode
 *
 * Under Emscripten, prefer @ref InstallEmscriptenContextLossCallbacks (Emscripten.hpp)
 * to automate context-loss / context-restore handling instead of calling Initialize directly.
 *
 * @note **Emscripten loader selection:** on WebGL builds the correct loader is
 *       `emscripten_webgl_get_proc_address` (from `<emscripten/html5.h>`),
 *       **not** `eglGetProcAddress`.  The Emscripten EGL emulation layer does not
 *       expose all WebGL 2 extensions through `eglGetProcAddress`; the HTML5 API
 *       variant is the authoritative source for WebGL extension entry-points.
 */
#pragma once

#include "Types.hpp"

#include <string_view>

namespace metagl
{
    /// Convenient alias for @ref GlGetProcAddressFn matching common naming conventions.
    using GetProcAddress = GlGetProcAddressFn;

    /**
     * @brief Loads all GL function pointers and initialises the library.
     *
     * Iterates over the list of 358 OpenGL ES 3.2 function names, calls @p loader for each,
     * and stores the resulting function pointers.  After a successful call:
     * - All `metagl::gl*` wrappers are ready to use.
     * - @ref GetContextStatus returns `ContextStatus::Current`.
     * - The context generation counter is incremented.
     * - Capabilities (version, extensions, GLES flags) are (re-)detected.
     * - Under `METAGLDEBUG`, `glGetError` is registered for per-call error checking.
     *
     * **Thread-safety:** `Initialize()` must complete fully before any render thread
     * calls `metagl::gl*` wrappers.  Concurrent calls from multiple threads are
     * **not** supported and result in undefined behaviour.  Typical usage: call once on
     * the GL thread during context creation (and again after context restore), then
     * hand off rendering to any thread.
     *
     * @param loader  Platform `GetProcAddress` function.  Must not be `nullptr`.
     * @return `true` if the core ES 2.0 function set was loaded successfully.
     *         `false` if the loader returned `nullptr` for one or more core functions.
     */
    bool Initialize(GlGetProcAddressFn loader);

    /**
     * @brief Convenience alias for @ref Initialize; provided for API consistency.
     *
     * Equivalent to `Initialize(getProcAddress)`.  Use this name in contexts where
     * "loading" semantics are more natural than "initialising" (e.g. after context restore).
     *
     * **Android example:**
     * @code
     * // GLSurfaceView.Renderer::onSurfaceCreated (via JNI) or after EGL context recreation:
     * metagl::LoadCurrentContext(eglGetProcAddress);
     * metagl::NotifyContextRestored();
     * // Note: old GL handles (textures, buffers, shaders, programs) are invalid after
     * // context loss; do not attempt glDelete* on them.
     * @endcode
     *
     * @param getProcAddress  Platform `GetProcAddress` function.
     * @return `true` on success; same semantics as @ref Initialize.
     */
    inline bool LoadCurrentContext(GlGetProcAddressFn getProcAddress)
    {
        return Initialize(getProcAddress);
    }

    /**
     * @brief Returns `true` if @ref Initialize has previously succeeded.
     *
     * Does not verify that function pointers are still valid (e.g. after context loss).
     * Use @ref GetContextStatus to check the lifecycle state.
     */
    bool IsInitialized();

    /**
     * @brief Returns `true` if the named GL function was loaded during the last
     *        @ref Initialize call.
     *
     * Useful for checking whether an optional extension entry-point is available
     * before calling it.
     *
     * @param name  Null-terminated GL function name (e.g. `"glBlendBarrier"`).
     * @return `true` if the function pointer is non-null; `false` otherwise.
     */
    [[nodiscard]] bool IsFunctionAvailable(std::string_view name) noexcept;

    /**
     * @brief Returns `true` if every OpenGL ES 3.2 function pointer was loaded successfully.
     *
     * A `true` result indicates a complete ES 3.2 driver.  A `false` result means
     * at least one ES 3.2 entry-point was absent (the driver may still be ES 2.0 or 3.x).
     *
     * @note A stub / mock loader that returns a non-null noop for every query will
     *       satisfy this check even without a real GPU.  It is intended as a
     *       completeness sanity-check, not a GPU presence check.
     */
    [[nodiscard]] bool AllFunctionsLoaded() noexcept;
}
