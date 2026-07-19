#include <metagl/metagl.hpp>
#include <iostream>
#include <csignal>
#include <cstdlib>

#ifndef _WIN32
#include <unistd.h>
#include <sys/wait.h>
#endif

using namespace metagl;

// Access the internal global table to simulate initialization
namespace metagl::detail {
    struct GlTable;
    extern thread_local struct GlTable g_gl;
}

// Since GlTable is private to Functions.cpp, we can't easily reach it.
// Let's use Initialize with a dummy loader that always returns a non-null no-op function.
void* dummy_loader(const char*) {
    static auto noop = []() { };
    return (void*)+noop; // Convert lambda to function pointer
}

bool expect_terminate(void (*func)()) {
#ifdef _WIN32
    return false; 
#else
    pid_t pid = fork();
    if (pid == 0) {
        // Ensure initialized for Debug builds to avoid assert(initialized) failing first
        Initialize(dummy_loader);
        func();
        std::exit(0);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status)) {
            int sig = WTERMSIG(status);
            std::cout << " (signal " << sig << ") ";
            // SIGABRT is 6, SIGSEGV is 11
            return sig == SIGABRT || sig == SIGSEGV;
        }
        return false;
    } else {
        return false;
    }
#endif
}

void test_overflow_glsizei() {
    std::size_t huge = static_cast<std::size_t>(2147483647) + 1;
    glGenBuffers(huge, nullptr);
}

void test_invalid_transpose() {
    float matrix[16] = {0};
    glUniformMatrix4fv(UniformLocation{0}, 1, GL_TRUE, matrix);
}

void test_invalid_element_count() {
    float data[3] = {1, 2, 3};
    // glUniform<4> expects multiple of 4 elements
    glUniform<4>(UniformLocation{0}, std::span<const float>{data, 3});
}

int main() {
    int failed = 0;

    std::cout << "Running Release-contract tests (R10)..." << std::endl;

    if (expect_terminate(test_overflow_glsizei)) {
        std::cout << "PASS: test_overflow_glsizei terminated as expected." << std::endl;
    } else {
        std::cerr << "FAIL: test_overflow_glsizei did NOT terminate." << std::endl;
        failed++;
    }

    if (expect_terminate(test_invalid_transpose)) {
        std::cout << "PASS: test_invalid_transpose terminated as expected." << std::endl;
    } else {
        std::cerr << "FAIL: test_invalid_transpose did NOT terminate." << std::endl;
        failed++;
    }

    if (expect_terminate(test_invalid_element_count)) {
        std::cout << "PASS: test_invalid_element_count terminated as expected." << std::endl;
    } else {
        std::cerr << "FAIL: test_invalid_element_count did NOT terminate." << std::endl;
        failed++;
    }

    if (failed == 0) {
        std::cout << "All Release-contract tests passed!" << std::endl;
    } else {
        std::cerr << failed << " Release-contract test(s) failed." << std::endl;
    }

    return failed;
}
