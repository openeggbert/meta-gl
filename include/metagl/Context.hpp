#pragma once

#include <cstdint>
#include <string>

namespace metagl
{
    /// Which API kind the current context represents.
    enum class ApiKind : std::uint8_t
    {
        Unknown,
        OpenGLES,
        WebGL
    };

    /// Lifecycle state of the current GL context.
    enum class ContextStatus : std::uint8_t
    {
        NotCreated,  ///< No context has been initialised yet.
        Current,     ///< Context is active and rendering is possible.
        Lost,        ///< Context was lost; GL handles are invalid.
        Restored     ///< Context was restored; resources must be recreated.
    };

    /// Snapshot of capabilities detected after context initialisation.
    struct ContextInfo
    {
        ApiKind api = ApiKind::Unknown;

        int major = 0;
        int minor = 0;

        std::string vendor;
        std::string renderer;

        // OpenGL ES version flags
        bool gles2  = false;
        bool gles3  = false;
        bool gles31 = false;
        bool gles32 = false;

        // WebGL version flags (only relevant when compiled with Emscripten)
        bool webgl  = false;
        bool webgl1 = false;
        bool webgl2 = false;

        /// Monotonically increasing counter. Incremented each time a context is
        /// successfully initialised (or restored).  Resources created under a
        /// generation != the current generation are stale.
        std::uint64_t generation = 0;

        /// Current lifecycle status.
        ContextStatus status = ContextStatus::NotCreated;
    };

    // -------------------------------------------------------------------------
    // Context state query / mutation API
    // -------------------------------------------------------------------------

    /// Returns a copy of the current ContextInfo.
    [[nodiscard]] ContextInfo GetContextInfo() noexcept;

    /// Returns the current context generation counter.
    [[nodiscard]] std::uint64_t GetContextGeneration() noexcept;

    /// Returns the current ContextStatus.
    [[nodiscard]] ContextStatus GetContextStatus() noexcept;

    /// Returns true when the context is lost; GL calls must be skipped.
    [[nodiscard]] bool IsContextLost() noexcept;

    /// Mark the context as lost.  Typically called by platform hooks
    /// (Emscripten context-lost callback, Android onSurfaceDestroyed, …).
    void MarkContextLost() noexcept;

    /// Mark the context as restored.  Call LoadCurrentContext() first to reload
    /// function pointers and redetect capabilities, then call this (or rely on
    /// LoadCurrentContext() which calls this internally).
    void MarkContextRestored() noexcept;

    /// Internal: set the full ContextInfo (used by LoadCurrentContext).
    void SetContextInfo(ContextInfo info) noexcept;
}
