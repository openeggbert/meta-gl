#include "metagl/Debug.hpp"

#ifdef METAGLDEBUG

#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

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

        std::uint64_t    g_call_counter = 0;
        std::vector<CallRecord> g_buf;
        Clock::time_point g_start      = Clock::now();
        Clock::time_point g_last_flush = Clock::now();

        void flush()
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

        // Destructor runs at static-storage teardown, after g_buf is still alive,
        // ensuring buffered calls are not lost on normal program exit.
        struct FlushOnExit { ~FlushOnExit() { flush(); } };
        FlushOnExit g_flush_on_exit;

        unsigned int (*g_get_error)() = nullptr;
    }

    void set_get_error_fn(unsigned int (*fn)()) noexcept { g_get_error = fn; }

    void check_gl_error(std::string_view func) noexcept
    {
        if (!g_get_error) return;
        const unsigned int err = g_get_error();
        if (err == 0) return; // GL_NO_ERROR
        std::cerr << "[METAGL GL_ERROR] "
                  << metagl::to_string(static_cast<metagl::ErrorCode>(err))
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
        flush();
        g_last_flush = Clock::now();
#else
        const auto now = Clock::now();
        if (now - g_last_flush >= std::chrono::seconds(5))
        {
            flush();
            g_last_flush = now;
        }
#endif
    }
}

#endif // METAGLDEBUG