#pragma once

// Emscripten-specific GL context-loss / context-restored helpers.
// This file is a no-op on non-Emscripten builds.

#ifdef __EMSCRIPTEN__

namespace metagl
{
    /// Install Emscripten HTML5 context-lost and context-restored callbacks on
    /// the canvas identified by @p canvasSelector (e.g. "#canvas" or nullptr
    /// for the default canvas).
    ///
    /// On context lost the internal callback calls:
    ///   1. metagl::NotifyContextLost() — marks the context lost and notifies
    ///      all registered ContextListeners via OnContextLost().
    ///
    /// On context restored the internal callback calls:
    ///   1. metagl::LoadCurrentContext(emscripten_webgl_get_proc_address) —
    ///      reloads all GL function pointers for the new WebGL context.
    ///   2. metagl::NotifyContextRestored() — marks the context restored and
    ///      notifies all registered ContextListeners via OnContextRestored().
    ///
    /// IMPORTANT — order on context restore:
    ///   LoadCurrentContext() MUST complete before NotifyContextRestored() is
    ///   called.  Listeners that render inside OnContextRestored() rely on
    ///   valid function pointers being available.  The internal callback
    ///   installed by this function already enforces the correct order.
    ///
    /// If you manage context-loss callbacks manually (e.g. via
    /// emscripten_set_webglcontextrestored_callback), replicate the order:
    ///
    ///   @code
    ///   // Inside your EMSCRIPTEN_WEBGL_CONTEXT_RESTORED_CALLBACK:
    ///   metagl::LoadCurrentContext(emscripten_webgl_get_proc_address);
    ///   metagl::NotifyContextRestored();
    ///   @endcode
    ///
    /// Returns true on success.
    bool InstallEmscriptenContextLossCallbacks(const char* canvasSelector = nullptr);
}

#endif // __EMSCRIPTEN__
