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

        const auto now = Clock::now();
        if (now - g_last_flush >= std::chrono::seconds(5))
        {
            flush();
            g_last_flush = now;
        }
    }
}

#endif // METAGLDEBUG