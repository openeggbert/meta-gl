/**
 * @file ContextEvents.hpp
 * @brief Observer interface for GL context-lost and context-restored lifecycle events.
 *
 * Implement @ref ContextListener, override @ref ContextListener::OnContextLost and/or
 * @ref ContextListener::OnContextRestored, and register with @ref AddContextListener.
 *
 * @code
 * class MyRenderer : public metagl::ContextListener
 * {
 * public:
 *     void OnContextLost() override
 *     {
 *         // Release CPU-side mirrors; do NOT call any GL function here.
 *         texture_handle = metagl::TextureId{};
 *     }
 *
 *     void OnContextRestored() override
 *     {
 *         // GL function pointers have been reloaded by LoadCurrentContext();
 *         // recreate GPU resources here.
 *         metagl::glGenTextures(1, &texture_handle.value);
 *     }
 *
 * private:
 *     metagl::TextureId texture_handle;
 * };
 *
 * MyRenderer renderer;
 * metagl::AddContextListener(&renderer);
 * @endcode
 */
#pragma once

namespace metagl
{
    /**
     * @brief Interface for objects that wish to be notified of GL context lifecycle events.
     *
     * Derive from this class, override the callbacks you need, and register the instance
     * with @ref AddContextListener.  The listener must remain alive until either
     * @ref RemoveContextListener is called or the listener is destroyed.
     */
    class ContextListener
    {
    public:
        virtual ~ContextListener() = default;

        /**
         * @brief Called when the GL context has been lost.
         *
         * All GL handles (textures, buffers, shaders, programs, …) are now invalid.
         * @warning Do NOT call any `metagl::gl*` wrapper function from this callback.
         *
         * Default implementation does nothing.
         */
        virtual void OnContextLost() {}

        /**
         * @brief Called after the GL context has been restored and function pointers have been reloaded.
         *
         * @ref LoadCurrentContext has already completed successfully before this callback fires,
         * so it is safe to call `metagl::gl*` functions here to recreate GPU resources.
         *
         * Default implementation does nothing.
         */
        virtual void OnContextRestored() {}
    };

    // -------------------------------------------------------------------------
    // Listener registration
    // -------------------------------------------------------------------------

    /**
     * @brief Registers a listener to receive context-lost / context-restored events.
     *
     * The caller retains ownership of @p listener; the pointer must remain valid
     * until @ref RemoveContextListener is called with the same pointer.
     *
     * @param listener  Non-null pointer to a @ref ContextListener instance.
     */
    void AddContextListener(ContextListener* listener);

    /**
     * @brief Removes a previously registered listener.
     *
     * No-op if @p listener is not found in the registered set.
     * Must be called before the listener object is destroyed.
     *
     * @param listener  Pointer previously passed to @ref AddContextListener.
     */
    void RemoveContextListener(ContextListener* listener);

    // -------------------------------------------------------------------------
    // Event dispatch
    // -------------------------------------------------------------------------

    /**
     * @brief Dispatches @ref ContextListener::OnContextLost to all registered listeners,
     *        then marks the context as lost via @ref MarkContextLost.
     *
     * Safe to call from a platform context-loss callback (e.g. Emscripten,
     * Android `onSurfaceDestroyed`).  Do not call any GL function after this
     * point until a successful @ref LoadCurrentContext.
     */
    void NotifyContextLost();

    /**
     * @brief Dispatches @ref ContextListener::OnContextRestored to all registered listeners,
     *        then marks the context as restored via @ref MarkContextRestored.
     *
     * **Required call order after a context-restore event:**
     * 1. Call @ref LoadCurrentContext — reloads all GL function pointers and redetects
     *    capabilities.  No `metagl::gl*` call is safe before this step completes.
     * 2. Call @ref NotifyContextRestored — fires @ref ContextListener::OnContextRestored
     *    on all registered listeners so they can recreate GPU resources.
     *
     * @warning Calling this function before @ref LoadCurrentContext is **undefined behaviour**:
     *          listeners may invoke GL functions through stale or null function pointers.
     */
    void NotifyContextRestored();
}
