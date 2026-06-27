#pragma once

namespace metagl
{
    /// Interface for objects that wish to be notified of GL context lifecycle
    /// events.  Derive from this class, implement the callbacks you care about,
    /// and register with AddContextListener().
    class ContextListener
    {
    public:
        virtual ~ContextListener() = default;

        /// Called when the GL context has been lost.  All GL handles are now
        /// invalid; do not call any GL function from this callback.
        virtual void OnContextLost() {}

        /// Called after the GL context has been restored and function pointers
        /// have been reloaded.  Recreate GPU resources here.
        virtual void OnContextRestored() {}
    };

    // -------------------------------------------------------------------------
    // Listener registration
    // -------------------------------------------------------------------------

    /// Register a listener to receive context-lost / context-restored events.
    /// The caller retains ownership; the pointer must remain valid until
    /// RemoveContextListener is called.
    void AddContextListener(ContextListener* listener);

    /// Remove a previously registered listener.  No-op if not found.
    void RemoveContextListener(ContextListener* listener);

    // -------------------------------------------------------------------------
    // Event dispatch
    // -------------------------------------------------------------------------

    /// Notify all registered listeners that the context has been lost, then
    /// mark the context as lost.  Safe to call from a platform callback.
    void NotifyContextLost();

    /// Notify all registered listeners that the context has been restored,
    /// then mark the context as restored.
    ///
    /// Required call order after a context-restore event:
    ///   1. Call LoadCurrentContext(getProcAddress) — reloads all GL function
    ///      pointers and re-detects capabilities.  No metagl::gl* call is safe
    ///      before this step completes successfully.
    ///   2. Call NotifyContextRestored() — fires OnContextRestored() on all
    ///      registered listeners so they can recreate GPU resources.
    ///
    /// Calling NotifyContextRestored() before LoadCurrentContext() is undefined
    /// behaviour: listeners may invoke GL functions through stale/null pointers.
    void NotifyContextRestored();
}
