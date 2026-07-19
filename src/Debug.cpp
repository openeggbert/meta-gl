#include "metagl/Debug.hpp"

#ifdef METAGLDEBUG

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "metagl/EnumNames.hpp"

namespace metagl::debug
{
    namespace
    {
        using Clock = std::chrono::steady_clock;

        struct CallRecord
        {
            std::uint64_t            number;
            Clock::time_point        timestamp;
            std::string              func;
            std::string              retval;
            std::string              params;
        };

        thread_local std::uint64_t    g_call_counter = 0;
        thread_local std::vector<CallRecord> g_buf;
        Clock::time_point g_start      = Clock::now();
        thread_local Clock::time_point g_last_flush = Clock::now();

        void flush_buffer()
        {
            if (g_buf.empty()) return;
            std::cerr << "[METAGL DEBUG] --- " << g_buf.size() << " GL calls ---\n";
            for (const auto& r : g_buf)
            {
                const double ms = std::chrono::duration<double, std::milli>(
                    r.timestamp - g_start).count();
                std::cerr << "  #" << r.number
                          << " [" << std::fixed << std::setprecision(3) << ms << "ms] "
                          << r.func << '(' << r.params << ')';
                if (r.retval != "void")
                    std::cerr << " -> " << r.retval;
                std::cerr << '\n';
            }
            std::cerr << "[METAGL DEBUG] ---\n";
            g_buf.clear();
        }

        // Windows invokes DLL static destructors while holding the loader lock.
        // Performing iostream I/O there can deadlock, so Windows callers use
        // FlushDebugLog() explicitly (or METAGLDEBUG_IMMEDIATE).
#ifndef _WIN32
        struct FlushOnExit { ~FlushOnExit() { metagl::FlushDebugLog(); } };
        FlushOnExit g_flush_on_exit;
#endif

        thread_local unsigned int (*g_get_error)() = nullptr;
    }

    void set_get_error_fn(unsigned int (*fn)()) noexcept { g_get_error = fn; }

    void flush() noexcept
    {
        try
        {
            flush_buffer();
        }
        catch (...)
        {
            // Debug logging must never affect application control flow.
        }
    }

    void check_gl_error(std::string_view func) noexcept
    {
        if (!g_get_error) return;
        const unsigned int err = g_get_error();
        if (err == 0) return; // GL_NO_ERROR

        char buffer[64];
        metagl::FormatGlError(static_cast<metagl::ErrorCode>(err), buffer, sizeof(buffer));

        std::cerr << "[METAGL GL_ERROR] "
                  << buffer
                  << " (0x" << std::hex << err << std::dec << ") after "
                  << func << '\n';
    }

    void record(std::string_view func, std::string_view retval, std::string params)
    {
        g_buf.push_back({
            ++g_call_counter,
            Clock::now(),
            std::string(func),
            std::string(retval),
            std::move(params)
        });

#ifdef METAGLDEBUG_IMMEDIATE
        flush_buffer();
        g_last_flush = Clock::now();
#else
        const auto now = Clock::now();
        if (now - g_last_flush >= std::chrono::seconds(5))
        {
            flush_buffer();
            g_last_flush = now;
        }
#endif
    }
}

namespace metagl
{
    void FlushDebugLog() noexcept
    {
        debug::flush();
    }

    std::size_t FormatGlError(ErrorCode error, char* buffer, std::size_t size) noexcept
    {
        if (!buffer || size == 0) return 0;

        std::string_view sv = metagl::to_string(error);
        std::size_t to_copy = std::min(sv.size(), size - 1);

        std::memcpy(buffer, sv.data(), to_copy);
        buffer[to_copy] = '\0';

        return to_copy;
    }
}

#else

namespace metagl
{
    void FlushDebugLog() noexcept {}

    std::size_t FormatGlError(ErrorCode, char* buffer, std::size_t size) noexcept
    {
        if (buffer && size > 0) buffer[0] = '\0';
        return 0;
    }
}

#endif // METAGLDEBUG
