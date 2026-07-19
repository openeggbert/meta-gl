/**
 * @file Capabilities.hpp
 * @brief GL capabilities and extension detection after context initialisation.
 *
 * `Capabilities` is populated by @ref metagl::Initialize /
 * @ref metagl::LoadCurrentContext and
 * is available immediately after either returns `true`.
 *
 * @code
 * metagl::Initialize(getProcAddress);
 * const auto& caps = metagl::GetCapabilities();
 * if (caps.gles30)
 *     // safe to use ES 3.0 API
 * if (metagl::HasExtension("GL_EXT_texture_filter_anisotropic"))
 *     // enable anisotropic filtering
 * @endcode
 */
#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace metagl
{
    /**
     * @brief GL capability strings and feature flags detected after context initialisation.
     *
     * An instance is populated internally during @ref Initialize and replaced on every
     * subsequent @ref LoadCurrentContext call.  Obtain a const reference via @ref GetCapabilities.
     */
    struct Capabilities
    {
        std::string version_string;           ///< Raw GL_VERSION string (e.g. `"OpenGL ES 3.0 NVIDIA"`).
        std::string vendor;                   ///< GL_VENDOR string (e.g. `"NVIDIA Corporation"`).
        std::string renderer;                 ///< GL_RENDERER string (e.g. `"Adreno 650"`).
        std::string shading_language_version; ///< GL_SHADING_LANGUAGE_VERSION string.
        std::vector<std::string> extensions;  ///< All extensions reported via `glGetStringi(GL_EXTENSIONS, i)`.

        bool gles20 = false;  ///< True for GLES 2.0+ or its WebGL equivalent.
        bool gles30 = false;  ///< True for GLES 3.0+ or its WebGL 2 equivalent.
        bool gles31 = false;  ///< True when the context supports at least OpenGL ES 3.1.
        bool gles32 = false;  ///< True when the context supports at least OpenGL ES 3.2.

        /// @brief True when compiling with Emscripten and the runtime exposes WebGL 1.
        bool webgl1 = false;
        /// @brief True when compiling with Emscripten and the runtime exposes WebGL 2.
        bool webgl2 = false;

        /// @brief True for a desktop OpenGL context (rather than OpenGL ES/WebGL).
        bool desktop_gl = false;

        /**
         * @brief True when GL_VERSION, GL_VENDOR, or GL_RENDERER identifies ANGLE.
         *
         * ANGLE exposes OpenGL ES through another graphics API. Function and
         * extension availability must still be queried normally.
         */
        bool angle = false;
    };

    // -------------------------------------------------------------------------
    // Capabilities query API
    // -------------------------------------------------------------------------

    /**
     * @brief Returns capabilities for the current loaded context.
     *
     * Context loss or loader failure clears every string, extension, and feature
     * flag. A successful @ref Initialize or @ref RestoreCurrentContext replaces
     * the contents with capabilities detected for the new current context.
     *
     * @note Do not retain this reference across context loss/restore events;
     *       copy any diagnostic data that must outlive the current context.
     */
    [[nodiscard]] const Capabilities& GetCapabilities() noexcept;

    /**
     * @brief Returns `true` for OpenGL ES 2.0+ or its WebGL equivalent.
     * @note Equivalent to `GetCapabilities().gles20`.
     */
    [[nodiscard]] bool SupportsGLES20() noexcept;

    /**
     * @brief Returns `true` for OpenGL ES 3.0+ or its WebGL 2 equivalent.
     *
     * WebGL exposes a browser-compatible subset of GLES 3.0. Check
     * @ref SupportsWebGL2 and @ref IsFunctionAvailable when code depends on an
     * entry point that is not part of that subset.
     * @note Equivalent to `GetCapabilities().gles30`.
     */
    [[nodiscard]] bool SupportsGLES30() noexcept;

    /**
     * @brief Returns `true` if the context supports at least OpenGL ES 3.1.
     * @note Equivalent to `GetCapabilities().gles31`.
     */
    [[nodiscard]] bool SupportsGLES31() noexcept;

    /**
     * @brief Returns `true` if the context supports at least OpenGL ES 3.2.
     * @note Equivalent to `GetCapabilities().gles32`.
     */
    [[nodiscard]] bool SupportsGLES32() noexcept;

    /**
     * @brief Returns `true` only when compiling with Emscripten and the runtime provides WebGL 2.
     * @note Always returns `false` on non-Emscripten builds.
     */
    [[nodiscard]] bool SupportsWebGL2() noexcept;

    /**
     * @brief Returns `true` when the loaded context is desktop OpenGL.
     */
    [[nodiscard]] bool SupportsDesktopOpenGL() noexcept;

    /**
     * @brief Returns `true` when the context strings identify an ANGLE backend.
     */
    [[nodiscard]] bool IsAngle() noexcept;

    /**
     * @brief Returns `true` if the named extension was present in the last @ref LoadCurrentContext call.
     *
     * The check is an exact-match string search over @ref Capabilities::extensions.
     *
     * @param extensionName  Extension string to look up (e.g. `"GL_EXT_texture_filter_anisotropic"`).
     * @return `true` if the extension is present; `false` otherwise or if not yet initialised.
     */
    [[nodiscard]] bool HasExtension(std::string_view extensionName) noexcept;
}
