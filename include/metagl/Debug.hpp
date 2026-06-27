#pragma once

// Define METAGLDEBUG to enable per-call GL logging.
// Each call records the function name, formatted parameters, and return value.
// The buffer is printed to stderr and cleared every 5 seconds.

//#define METAGLDEBUG

#ifdef METAGLDEBUG

#include <string>
#include <string_view>
#include <sstream>
#include <type_traits>
#include <cstdint>
#include "metagl/EnumNames.hpp"

namespace metagl::debug
{
    // ---- per-value formatter ------------------------------------------------

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

    inline std::string to_str(const char* s)
    {
        return s ? (std::string("\"") + s + "\"") : "null";
    }

    // ---- variadic arg formatter ---------------------------------------------

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

    // Record one GL call entry.  Flushes to stderr every 5 seconds.
    void record(std::string_view func, std::string_view retval, std::string params);

    template<typename... Args>
    void record_void(std::string_view func, Args&&... args)
    {
        record(func, "void", fmt_args(std::forward<Args>(args)...));
    }

    template<typename R, typename... Args>
    void record_ret(std::string_view func, const R& retval, Args&&... args)
    {
        record(func, to_str(retval), fmt_args(std::forward<Args>(args)...));
    }
}

// Macros used in Functions.cpp
#define METAGL_DEBUG_LOG_VOID(name, ...) metagl::debug::record_void(name __VA_OPT__(,) __VA_ARGS__)
#define METAGL_DEBUG_LOG(name, _r, ...)  metagl::debug::record_ret(name, _r __VA_OPT__(,) __VA_ARGS__)

#else // METAGLDEBUG not defined — zero overhead

#define METAGL_DEBUG_LOG_VOID(name, ...) do {} while(0)
#define METAGL_DEBUG_LOG(name, _r, ...)  do {} while(0)

#endif // METAGLDEBUG
