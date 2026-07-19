/**
 * @file Debug.hpp
 * @brief Optional compile-time GL call logging and `glGetError` checking.
 *
 * Configure meta-gl with `-DMETAGL_ENABLE_DEBUG_LOGGING=ON` to compile
 * per-call logging into the library. Defining `METAGLDEBUG` only in a
 * consuming target is not sufficient because wrappers are compiled in
 * `src/Functions.cpp`.
 *
 * When active, each `metagl::gl*` wrapper records:
 * - the function name,
 * - all formatted parameters (enums shown as symbolic names via @ref EnumNames.hpp),
 * - and the return value (or `"void"`).
 *
 * Records are buffered and flushed to `stderr` every 5 seconds.
 * Configure `-DMETAGL_DEBUG_IMMEDIATE=ON` to flush after every call — this
 * trades throughput for crash-safety when debugging hard crashes.
 *
 * When `METAGLDEBUG` is **not** defined, all macros expand to `do {} while(0)`,
 * resulting in exactly zero runtime overhead.
 *
 * Example output:
 * @code
 * [METAGL DEBUG] --- 2 GL calls ---
 *   #1 [0.100ms] glClear(16640)
 *   #2 [0.140ms] glDrawArrays(Triangles, 0, 3)
 * [METAGL DEBUG] ---
 * @endcode
 */
#pragma once

#include "metagl/Export.hpp"
#include "metagl/Enums.hpp"
#include <cstddef>

namespace metagl
{
    /**
     * @brief Flushes buffered debug call records to `stderr`.
     *
     * This function is always available and is a no-op when meta-gl was built
     * without `METAGL_ENABLE_DEBUG_LOGGING`. Call it before program shutdown
     * when buffered logging is enabled. Windows DLL teardown intentionally
     * avoids automatic I/O while the loader lock is held.
     */
    METAGL_API void FlushDebugLog() noexcept;

    /**
     * @brief Formats a GL error code into a human-readable string.
     *
     * @param error  GL error code to format.
     * @param buffer Pointer to a character buffer to receive the string.
     * @param size   Size of the provided buffer.
     * @return Number of characters written (excluding null terminator).
     */
    METAGL_API std::size_t FormatGlError(ErrorCode error, char* buffer, std::size_t size) noexcept;
}

// Define METAGLDEBUG to enable per-call GL logging.
// Each call records the function name, formatted parameters, and return value.
// The buffer is printed to stderr and cleared every 5 seconds.
// Define METAGLDEBUG_IMMEDIATE (alongside METAGLDEBUG) to flush after every
// call — trades throughput for crash-safety when debugging hard crashes.

//#define METAGLDEBUG

#ifdef METAGLDEBUG

#include <string>
#include <string_view>
#include <sstream>
#include <type_traits>
#include <cstdint>
#include <utility>
#include "metagl/EnumNames.hpp"

/**
 * @namespace metagl::debug
 * @brief Internal implementation namespace for the METAGLDEBUG logging layer.
 *
 * Do not call these functions directly; they are invoked through the
 * `METAGL_DEBUG_LOG_VOID` and `METAGL_DEBUG_LOG` macros emitted by each
 * `metagl::gl*` wrapper in `src/Functions.cpp`.
 */
namespace metagl::debug
{
    // ---- per-value formatter ------------------------------------------------

    /**
     * @brief Formats a single GL call argument as a human-readable string.
     *
     * - `enum class` values are shown as their symbolic name when a `to_string()`
     *   overload is available (from @ref EnumNames.hpp), falling back to the raw integer.
     * - Pointer values are shown as `0x<hex>` or `"null"`.
     * - Handle types with a `to_string()` overload are shown symbolically.
     * - All other types use `std::to_string`.
     *
     * @tparam T  Type of the argument.
     * @param  val  Value to format.
     * @return Human-readable string representation.
     */
    template<typename T>
    std::string to_str(T val)
    {
        if constexpr (std::is_enum_v<T>)
        {
            // Use the generated to_string() overload when available (returns the
            // enumerator name), falling back to the raw numeric value otherwise.
            if constexpr (requires { metagl::to_string(val); })
            {
                auto sv = metagl::to_string(val);
                if (sv != "?") return std::string(sv);
            }
            return std::to_string(static_cast<std::underlying_type_t<T>>(val));
        }
        else if constexpr (std::is_pointer_v<T>)
        {
            if (!val) return "null";
            std::ostringstream oss;
            oss << "0x" << std::hex << reinterpret_cast<std::uintptr_t>(val);
            return oss.str();
        }
        else if constexpr (requires { metagl::to_string(val); })
        {
            return std::string(metagl::to_string(val));
        }
        else
            return std::to_string(val);
    }

    /**
     * @brief Specialisation of @ref to_str for C-string arguments.
     *
     * Returns the string surrounded by double-quotes, or `"null"` for a null pointer.
     */
    inline std::string to_str(const char* s)
    {
        return s ? (std::string("\"") + s + "\"") : "null";
    }

    // ---- variadic arg formatter ---------------------------------------------

    /**
     * @brief Formats a variadic list of GL call arguments as a comma-separated string.
     *
     * Uses @ref to_str for each individual argument.
     * Returns an empty string when called with no arguments (void functions).
     *
     * @tparam Args  Parameter types (deduced).
     * @param  args  Arguments to format.
     * @return Comma-separated argument list suitable for log output.
     */
    template<typename... Args>
    std::string fmt_args(Args&&... args)
    {
        if constexpr (sizeof...(args) == 0) return "";
        std::string r;
        bool first = true;
        ((r += (first ? "" : ", ") + to_str(std::forward<Args>(args)), first = false), ...);
        return r;
    }

    // ---- recording ----------------------------------------------------------

    /**
     * @brief Records one GL call entry into the in-memory log buffer.
     *
     * Flushes the buffer to `stderr` every 5 seconds (or immediately if
     * `METAGLDEBUG_IMMEDIATE` is defined).
     *
     * @param func    GL function name (e.g. `"glDrawArrays"`).
     * @param retval  Formatted return value string (e.g. `"void"`, `"42"`, `"0x1000"`).
     * @param params  Formatted parameter list produced by @ref fmt_args.
     */
    void record(std::string_view func, std::string_view retval, std::string params);

    /**
     * @brief Records a void-returning GL call.
     *
     * Formats all arguments with @ref fmt_args, then delegates to @ref record.
     *
     * @tparam Args  Argument types (deduced).
     * @param  func  GL function name.
     * @param  args  GL call arguments forwarded to @ref fmt_args.
     */
    template<typename... Args>
    void record_void(std::string_view func, Args&&... args)
    {
        record(func, "void", fmt_args(std::forward<Args>(args)...));
    }

    /**
     * @brief Records a value-returning GL call.
     *
     * Formats the return value with @ref to_str and all arguments with @ref fmt_args,
     * then delegates to @ref record.
     *
     * @tparam R     Return type (deduced).
     * @tparam Args  Argument types (deduced).
     * @param  func    GL function name.
     * @param  retval  Return value of the GL call.
     * @param  args    GL call arguments forwarded to @ref fmt_args.
     */
    template<typename R, typename... Args>
    void record_ret(std::string_view func, const R& retval, Args&&... args)
    {
        record(func, to_str(retval), fmt_args(std::forward<Args>(args)...));
    }

    // ---- glGetError integration ----------------------------------------------

    /**
     * @brief Registers the `glGetError` function pointer for per-call error checking.
     *
     * Called from @ref Initialize when `METAGLDEBUG` is active so that
     * @ref check_gl_error can call `GetError` directly without going through the
     * meta-gl wrapper (which would create a recursive logging loop).
     *
     * @param fn  Pointer to the loaded `glGetError` implementation.
     */
    void set_get_error_fn(unsigned int (*fn)()) noexcept;

    /**
     * @brief Calls the registered `glGetError` function after a GL wrapper call.
     *
     * If `glGetError` returns anything other than `GL_NO_ERROR` (0), prints an
     * immediate diagnostic to `stderr`:
     * @code
     * [METAGL GL_ERROR] InvalidOperation (0x502) after glDrawArrays
     * @endcode
     *
     * No-op if no error function has been registered via @ref set_get_error_fn.
     *
     * @param func  Name of the GL function that was just called (for the error message).
     */
    void check_gl_error(std::string_view func) noexcept;
}

/**
 * @brief Logs a void-returning GL call and checks for GL errors.
 *
 * Expands to a `record_void` call followed by a `check_gl_error` call.
 * Only active when `METAGLDEBUG` is defined; otherwise expands to nothing.
 *
 * @param name  GL function name string literal.
 * @param ...   GL call arguments (optional; forwarded to @ref metagl::debug::fmt_args).
 */
#define METAGL_DEBUG_LOG_VOID(name, ...) \
    do { \
        metagl::debug::record_void(name __VA_OPT__(,) __VA_ARGS__); \
        metagl::debug::check_gl_error(name); \
    } while(0)

/**
 * @brief Logs a value-returning GL call and checks for GL errors.
 *
 * Expands to a `record_ret` call followed by a `check_gl_error` call.
 * Only active when `METAGLDEBUG` is defined; otherwise expands to nothing.
 *
 * @param name  GL function name string literal.
 * @param _r    Return value of the GL call.
 * @param ...   GL call arguments (optional; forwarded to @ref metagl::debug::fmt_args).
 */
#define METAGL_DEBUG_LOG(name, _r, ...) \
    do { \
        metagl::debug::record_ret(name, _r __VA_OPT__(,) __VA_ARGS__); \
        metagl::debug::check_gl_error(name); \
    } while(0)

#else // METAGLDEBUG not defined — zero overhead

/// @cond INTERNAL
#define METAGL_DEBUG_LOG_VOID(name, ...) do {} while(0)
#define METAGL_DEBUG_LOG(name, _r, ...)  do {} while(0)
/// @endcond

#endif // METAGLDEBUG
