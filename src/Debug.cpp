#include "metagl/Debug.hpp"

#ifdef METAGLDEBUG

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

namespace metagl::debug
{
    namespace
    {
        struct CallRecord
        {
            std::string func;
            std::string retval;
            std::string params;
        };

        std::vector<CallRecord> g_buf;
        std::chrono::steady_clock::time_point g_last_flush = std::chrono::steady_clock::now();

        void flush()
        {
            if (g_buf.empty()) return;
            std::cerr << "[METAGL DEBUG] --- " << g_buf.size() << " GL calls ---\n";
            for (const auto& r : g_buf)
            {
                std::cerr << "  " << r.func << '(' << r.params << ')';
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
        g_buf.push_back({std::string(func), std::string(retval), std::move(params)});

        const auto now = std::chrono::steady_clock::now();
        if (now - g_last_flush >= std::chrono::seconds(5))
        {
            flush();
            g_last_flush = now;
        }
    }
}

#endif // METAGLDEBUG