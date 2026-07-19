/**
 * @file ContextEvents.hpp
 * @brief Observer interface for GL context-lost and context-restored lifecycle events.
 *
 * Implement @ref metagl::ContextListener, override
 * @ref metagl::ContextListener::OnContextLost and/or
 * @ref metagl::ContextListener::OnContextRestored, and register with
 * @ref metagl::AddContextListener.
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

#include "metagl/Export.hpp"

namespace metagl
{
    /**
     * @brief Interface for objects that wish to be notified of GL context lifecycle events.
     *
     * Derive from this class, override the callbacks you need, and register the instance
     * with @ref AddContextListener.  The listener must remain alive until either
     * @ref RemoveContextListener is called or the listener is destroyed.
     */
    class METAGL_API ContextListener
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
    METAGL_API void AddContextListener(ContextListener* listener);

    /**
     * @brief Removes a previously registered listener.
     *
     * No-op if @p listener is not found in the registered set.
     * Must be called before the listener object is destroyed.
     *
     * @param listener  Pointer previously passed to @ref AddContextListener.
     */
    METAGL_API void RemoveContextListener(ContextListener* listener);

    // -------------------------------------------------------------------------
    // Event dispatch
    // -------------------------------------------------------------------------

    /**
     * @brief Marks the context lost, then dispatches
     *        @ref ContextListener::OnContextLost to registered listeners.
     *
     * Safe to call from a platform context-loss callback (e.g. Emscripten,
     * Android `onSurfaceDestroyed`).  Do not call any GL function after this
     * point until a successful @ref LoadCurrentContext.
     */
    METAGL_API void NotifyContextLost();

    /**
     * @brief Dispatches the restored event after a successful explicit reload.
     *
     * Prefer the atomic @ref RestoreCurrentContext helper. The compatible manual
     * call order after a context-restore event is:
     * 1. Call @ref LoadCurrentContext — reloads all GL function pointers and redetects
     *    capabilities.  No `metagl::gl*` call is safe before this step completes.
     * 2. Call @ref NotifyContextRestored — fires @ref ContextListener::OnContextRestored
     *    on all registered listeners so they can recreate GPU resources.
     *
     * If no successful load has occurred since @ref NotifyContextLost, this
     * function leaves the context lost and does not dispatch callbacks.
     *
     * During callbacks @ref GetContextStatus returns `ContextStatus::Restored`.
     * After all callbacks return it is `ContextStatus::Current`.
     *
     * Listener registration is snapshotted before dispatch. A listener may safely
     * add or remove itself during a callback; changes take effect on the next event.
     */
    METAGL_API void NotifyContextRestored();
}
