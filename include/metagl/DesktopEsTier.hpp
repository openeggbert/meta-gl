/**
 * @file DesktopEsTier.hpp
 * @brief Internal-only desktop OpenGL ES-tier equivalence diagnostic (R76-R78).
 *
 * This header is **not** part of the stable public API surface documented by
 * @ref metagl.hpp. It is intentionally excluded from that umbrella header and
 * exists only so that `metagl::detail::GetDesktopEsTier()` can be exercised by
 * internal tests. It may change or be removed without notice and without a
 * `CHANGELOG.md` entry.
 *
 * Background: `Capabilities::gles30/gles31/gles32` are only ever set for
 * OpenGL ES/WebGL contexts (see `Capabilities.hpp`); a desktop OpenGL 3.3+
 * context always reports them as `false`, even when the underlying driver
 * additionally satisfies the same mandatory-function set required by a
 * higher OpenGL ES tier. Publicly unifying those flags across desktop and
 * ES was considered and rejected as out of scope (see
 * [analysis.md finding 22](../../../analysis.md#finding-22) and
 * [plan.md R76](../../../plan.md)) to keep `Capabilities` unambiguous about
 * the actual context kind. This header instead exposes the tier purely for
 * internal validation/diagnostics during @ref metagl::Initialize.
 */
#pragma once

#include "metagl/Export.hpp"

namespace metagl::detail
{
    /**
     * @brief OpenGL ES mandatory-function tier additionally satisfied by a
     *        desktop OpenGL 3.3+ context.
     *
     * Computed internally by @ref metagl::Initialize / @ref
     * metagl::LoadCurrentContext for desktop OpenGL contexts only, by
     * checking the same `gles30/31/32_required_names` mandatory-entry-point
     * lists used for native OpenGL ES, plus `GL_ARB_ES3_1_compatibility` /
     * `GL_ARB_ES3_2_compatibility` as a fast additional signal (R77) that
     * replaces any per-function ARB extension fallback.
     */
    enum class DesktopEsTier
    {
        None,     ///< Not a desktop OpenGL 3.3+ context (GLES/WebGL, or not initialised).
        Baseline, ///< Desktop OpenGL 3.3+, ES-2.0-equivalent baseline only.
        Es30,     ///< Additionally satisfies the OpenGL ES 3.0 mandatory-function set.
        Es31,     ///< Additionally satisfies the OpenGL ES 3.1 mandatory-function set (or advertises `GL_ARB_ES3_1_compatibility`/`GL_ARB_ES3_2_compatibility`).
        Es32,     ///< Additionally satisfies the OpenGL ES 3.2 mandatory-function set (or advertises `GL_ARB_ES3_2_compatibility`).
    };

    /**
     * @brief Returns the desktop ES-tier diagnostic computed by the last
     *        successful @ref metagl::Initialize / @ref
     *        metagl::LoadCurrentContext call.
     *
     * Always @ref DesktopEsTier::None for a non-desktop context (OpenGL
     * ES/WebGL), for an uninitialised context, or after context loss.
     *
     * @note Internal-only diagnostic; not part of @ref metagl::Capabilities
     *       and not covered by the project's API/ABI stability guarantees.
     */
    [[nodiscard]] METAGL_API DesktopEsTier GetDesktopEsTier() noexcept;
}
