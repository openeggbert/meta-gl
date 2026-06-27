/**
 * @file Emscripten.hpp
 * @brief Emscripten-specific GL context-loss and context-restore helpers.
 *
 * This file is a **no-op on non-Emscripten builds** — the entire body is
 * guarded by `#ifdef __EMSCRIPTEN__`.  metagl.hpp includes it automatically
 * under that preprocessor flag; you do not need to include it directly.
 *
 * ### Purpose
 * WebGL contexts can be lost at any time (e.g. when the browser tab is
 * backgrounded or the GPU driver resets).  This header provides a single
 * convenience function that installs the two necessary HTML5 callbacks so
 * meta-gl's context-lifecycle machinery handles loss and restore automatically.
 *
 * ### Manual callback alternative
 * If you manage WebGL context callbacks yourself (e.g. via
 * `emscripten_set_webglcontextlost_callback` /
 * `emscripten_set_webglcontextrestored_callback`), replicate the correct
 * call order in your handlers:
 *
 * @code
 * // Context-lost handler:
 * metagl::NotifyContextLost();
 *
 * // Context-restored handler:
 * metagl::LoadCurrentContext(emscripten_webgl_get_proc_address);
 * metagl::NotifyContextRestored();
 * @endcode
 *
 * @note `LoadCurrentContext` MUST complete before `NotifyContextRestored` is
 *       called.  @ref InstallEmscriptenContextLossCallbacks enforces this order.
 */
#pragma once

// Emscripten-specific GL context-loss / context-restored helpers.
// This file is a no-op on non-Emscripten builds.

#ifdef __EMSCRIPTEN__

namespace metagl
{
    /**
     * @brief Installs Emscripten HTML5 context-lost and context-restored callbacks.
     *
     * Registers two internal C callbacks on the canvas identified by
     * @p canvasSelector using the Emscripten HTML5 API:
     *
     * - **Context-lost callback** calls:
     *   1. @ref NotifyContextLost — marks the context lost and dispatches
     *      @ref ContextListener::OnContextLost to all registered listeners.
     *
     * - **Context-restored callback** calls:
     *   1. @ref LoadCurrentContext `(emscripten_webgl_get_proc_address)` — reloads
     *      all GL function pointers for the new WebGL context.
     *   2. @ref NotifyContextRestored — marks the context restored and dispatches
     *      @ref ContextListener::OnContextRestored to all registered listeners.
     *
     * @par IMPORTANT — call order on context restore
     * `LoadCurrentContext()` **must** complete before `NotifyContextRestored()` is
     * called.  Listeners that call GL functions inside `OnContextRestored()` rely
     * on valid function pointers.  This function already enforces the correct order.
     *
     * @param canvasSelector  CSS selector for the target canvas element
     *                        (e.g. `"#canvas"`), or `nullptr` for the default canvas.
     * @return `true` on success; `false` if the Emscripten callback registration
     *         failed (check browser console for details).
     */
    bool InstallEmscriptenContextLossCallbacks(const char* canvasSelector = nullptr);
}

#endif // __EMSCRIPTEN__
