/**
 * @file Context.hpp
 * @brief GL context lifecycle state: API kind, version, generation counter, and status.
 *
 * `ContextInfo` holds the minimal runtime facts about the active GL context.
 * Feature detection (GLES version flags, extension strings, vendor/renderer strings)
 * lives in @ref Capabilities.hpp to keep this header small.
 *
 * Typical usage:
 * @code
 * metagl::Initialize(getProcAddress);
 * const auto& info = metagl::GetContextInfo();
 * if (info.api == metagl::ApiKind::OpenGLES && info.major >= 3)
 *     // ES 3.x path
 * @endcode
 */
#pragma once

#include <cstdint>

namespace metagl
{
    /**
     * @brief Identifies the GL API exposed by the current context.
     */
    enum class ApiKind : std::uint8_t
    {
        Unknown,   ///< API not yet detected or unrecognised version string.
        OpenGLES,  ///< Desktop or mobile OpenGL ES context.
        WebGL,     ///< Emscripten/WebGL context (detected via `__EMSCRIPTEN__` and version string).
        OpenGL     ///< Desktop OpenGL context.
    };

    /**
     * @brief Lifecycle state of the current GL context.
     *
     * Transitions:
     * - `NotCreated` → `Current`  after the first successful @ref Initialize call.
     * - `Current`    → `Lost`     via @ref MarkContextLost or @ref NotifyContextLost.
     * - `Lost`       → `Restored` briefly while @ref NotifyContextRestored dispatches
     *                              resource-recreation callbacks.
     * - `Restored`   → `Current`  when @ref NotifyContextRestored finishes.
     *
     * Prefer @ref RestoreCurrentContext for the complete `Lost` → `Current`
     * transition; it reloads entry points before dispatching callbacks.
     */
    enum class ContextStatus : std::uint8_t
    {
        NotCreated,  ///< No context has been initialised yet.
        Current,     ///< Context is active and rendering is possible.
        Lost,        ///< Context was lost; all GL handles are invalid.
        Restored     ///< Context was restored; GPU resources must be recreated.
    };

    /**
     * @brief Snapshot of the current GL context's identity and lifecycle state.
     *
     * Feature detection (GLES version flags, extension strings, vendor/renderer)
     * is in @ref Capabilities, obtainable via @ref GetCapabilities.
     */
    struct ContextInfo
    {
        ApiKind api = ApiKind::Unknown;  ///< API kind detected from the GL_VERSION string.

        int major = 0;  ///< Major version number (e.g. `3` for OpenGL ES 3.2).
        int minor = 0;  ///< Minor version number (e.g. `2` for OpenGL ES 3.2).

        /**
         * @brief Monotonically increasing context generation counter.
         *
         * Incremented each time @ref Initialize (or @ref LoadCurrentContext) succeeds.
         * GPU resources created under a previous generation are invalid and must not
         * be used or deleted after context loss/restore.
         */
        std::uint64_t generation = 0;

        ContextStatus status = ContextStatus::NotCreated;  ///< Current lifecycle status.
    };

    // -------------------------------------------------------------------------
    // Context state query API
    // -------------------------------------------------------------------------

    /**
     * @brief Returns a copy of the current @ref ContextInfo.
     *
     * The returned struct is a snapshot; it does not update automatically.
     * Call @ref GetContextStatus for a cheap single-field check.
     */
    [[nodiscard]] ContextInfo GetContextInfo() noexcept;

    /**
     * @brief Returns the current context generation counter.
     *
     * Equivalent to `GetContextInfo().generation` but avoids copying the full struct.
     */
    [[nodiscard]] std::uint64_t GetContextGeneration() noexcept;

    /**
     * @brief Returns the current @ref ContextStatus.
     *
     * Cheap single-field read; prefer over @ref GetContextInfo when only the status is needed.
     */
    [[nodiscard]] ContextStatus GetContextStatus() noexcept;

    /**
     * @brief Returns `true` when the context is in the `Lost` state.
     *
     * Callers should guard all GL work with this check when the application
     * supports context loss (e.g. on Android or WebGL):
     * @code
     * if (!metagl::IsContextLost())
     *     metagl::glDrawArrays(...);
     * @endcode
     */
    [[nodiscard]] bool IsContextLost() noexcept;

    // -------------------------------------------------------------------------
    // Context state mutation API
    // -------------------------------------------------------------------------

    /**
     * @brief Marks the context as lost.
     *
     * Transitions the status from `Current` → `Lost`.
     * Current API/version identity and capabilities are cleared, and loader
     * availability queries return `false` until a successful reload. The
     * context generation is preserved so stale resource handles remain
     * distinguishable from resources created after restore.
     *
     * Typically called by platform hooks (Emscripten context-lost callback,
     * Android `onSurfaceDestroyed`, etc.).
     *
     * Prefer @ref NotifyContextLost, which also dispatches @ref ContextListener events.
     */
    void MarkContextLost() noexcept;

    /**
     * @brief Marks the context as restored.
     *
     * Transitions the status to the temporary `Restored` state.
     *
     * @warning This is a low-level state mutation only. Prefer
     *          @ref RestoreCurrentContext, which reloads function pointers,
     *          dispatches listeners, and returns the status to `Current`.
     */
    void MarkContextRestored() noexcept;

    /**
     * @brief Internal: writes the full @ref ContextInfo (used by @ref LoadCurrentContext).
     *
     * Not intended for direct use by application code.
     */
    void SetContextInfo(ContextInfo info) noexcept;
}
