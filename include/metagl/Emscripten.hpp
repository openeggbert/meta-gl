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
    /// On context lost the callback will:
    ///   1. Call metagl::NotifyContextLost() which marks the context lost and
    ///      notifies all registered ContextListeners.
    ///
    /// On context restored the callback will:
    ///   1. Call metagl::NotifyContextRestored() which marks the context
    ///      restored and notifies all registered ContextListeners.
    ///   Note: The application must call metagl::LoadCurrentContext() again
    ///   before rendering to reload function pointers (e.g. from the restored
    ///   callback or from the next frame's render path).
    ///
    /// Returns true on success.
    bool InstallEmscriptenContextLossCallbacks(const char* canvasSelector = nullptr);
}

#endif // __EMSCRIPTEN__
