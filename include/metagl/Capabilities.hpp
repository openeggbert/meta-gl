#pragma once

#include <string>
#include <vector>

namespace metagl
{
    /// GL capabilities and strings detected after context initialisation.
    struct Capabilities
    {
        std::string version_string;
        std::string vendor;
        std::string renderer;
        std::string shading_language_version;
        std::vector<std::string> extensions;

        bool gles20 = false;
        bool gles30 = false;
        bool gles31 = false;
        bool gles32 = false;

        /// True when compiling with Emscripten and the runtime is WebGL 1.
        bool webgl1 = false;
        /// True when compiling with Emscripten and the runtime is WebGL 2.
        bool webgl2 = false;
    };

    // -------------------------------------------------------------------------
    // Capabilities query API
    // -------------------------------------------------------------------------

    /// Returns the capabilities detected during the last LoadCurrentContext call.
    [[nodiscard]] const Capabilities& GetCapabilities() noexcept;

    [[nodiscard]] bool SupportsGLES20() noexcept;
    [[nodiscard]] bool SupportsGLES30() noexcept;
    [[nodiscard]] bool SupportsGLES31() noexcept;
    [[nodiscard]] bool SupportsGLES32() noexcept;

    /// True only when compiling with Emscripten and the runtime provides WebGL 2.
    [[nodiscard]] bool SupportsWebGL2() noexcept;

    /// Returns true if the named extension was present in the last context.
    [[nodiscard]] bool HasExtension(std::string_view extensionName) noexcept;
}
