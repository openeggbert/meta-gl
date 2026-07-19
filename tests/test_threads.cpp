#include <metagl/metagl.hpp>
#include <GLES3/gl32.h>
#include <cstring>
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

namespace
{
    const GLubyte* GL_APIENTRY stub_GetString_T1(GLenum name)
    {
        static const GLubyte version[] = "OpenGL ES 3.1 Thread 1";
        if (name == GL_VERSION) return version;
        return reinterpret_cast<const GLubyte*>("");
    }

    const GLubyte* GL_APIENTRY stub_GetString_T2(GLenum name)
    {
        static const GLubyte version[] = "OpenGL ES 3.2 Thread 2";
        if (name == GL_VERSION) return version;
        return reinterpret_cast<const GLubyte*>("");
    }

    void GL_APIENTRY stub_noop() {}

    void* loader_T1(const char* name)
    {
        if (std::strcmp(name, "glGetString") == 0) return (void*)stub_GetString_T1;
        return (void*)stub_noop;
    }

    void* loader_T2(const char* name)
    {
        if (std::strcmp(name, "glGetString") == 0) return (void*)stub_GetString_T2;
        return (void*)stub_noop;
    }
}

int main()
{
    std::atomic<int> failed{0};

    // Thread 1: Load GLES 3.1
    std::thread t1([&]() {
        if (!metagl::Initialize(loader_T1)) {
            std::cerr << "T1: Initialize failed\n";
            failed++;
            return;
        }
        if (metagl::GetContextInfo().minor != 1) {
            std::cerr << "T1: Expected minor version 1, got " << metagl::GetContextInfo().minor << "\n";
            failed++;
        }
        if (!metagl::SupportsGLES31() || metagl::SupportsGLES32()) {
            std::cerr << "T1: Wrong capabilities detected\n";
            failed++;
        }
        
        // Wait a bit to ensure T2 has time to run and potentially overwrite global state
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Re-check after T2 should have finished
        if (metagl::GetContextInfo().minor != 1) {
            std::cerr << "T1: State was corrupted by another thread! Expected 1, got " << metagl::GetContextInfo().minor << "\n";
            failed++;
        }
    });

    // Thread 2: Load GLES 3.2
    std::thread t2([&]() {
        // Sleep a bit to ensure T1 starts first
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        
        if (!metagl::Initialize(loader_T2)) {
            std::cerr << "T2: Initialize failed\n";
            failed++;
            return;
        }
        if (metagl::GetContextInfo().minor != 2) {
            std::cerr << "T2: Expected minor version 2, got " << metagl::GetContextInfo().minor << "\n";
            failed++;
        }
        if (!metagl::SupportsGLES32()) {
            std::cerr << "T2: Wrong capabilities detected\n";
            failed++;
        }
    });

    t1.join();
    t2.join();

    if (failed == 0) {
        std::cout << "Thread-local context test passed!\n";
    } else {
        std::cerr << failed << " thread tests failed.\n";
    }

    return failed;
}
