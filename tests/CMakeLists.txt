cmake_minimum_required(VERSION 3.23)

add_executable(metagl-tests
    test_compile.cpp
)
target_link_libraries(metagl-tests PRIVATE meta-gl::meta-gl)
target_compile_features(metagl-tests PRIVATE cxx_std_23)
set_target_properties(metagl-tests PROPERTIES CXX_EXTENSIONS NO)
metagl_apply_warnings(metagl-tests)
metagl_stage_runtime(metagl-tests)
add_test(NAME metagl-compile-tests COMMAND metagl-tests)

add_executable(metagl-mock-tests
    test_mock_loader.cpp
)
target_link_libraries(metagl-mock-tests PRIVATE meta-gl::meta-gl)
target_compile_features(metagl-mock-tests PRIVATE cxx_std_23)
set_target_properties(metagl-mock-tests PROPERTIES CXX_EXTENSIONS NO)
metagl_apply_warnings(metagl-mock-tests)
metagl_stage_runtime(metagl-mock-tests)
add_test(NAME metagl-mock-loader-test COMMAND metagl-mock-tests)

add_executable(metagl-release-contract-tests
    test_release_contract.cpp
)
target_link_libraries(metagl-release-contract-tests PRIVATE meta-gl::meta-gl)
target_compile_features(metagl-release-contract-tests PRIVATE cxx_std_23)
set_target_properties(metagl-release-contract-tests PROPERTIES CXX_EXTENSIONS NO)
metagl_apply_warnings(metagl-release-contract-tests)
metagl_stage_runtime(metagl-release-contract-tests)
add_test(NAME metagl-release-contract-test COMMAND metagl-release-contract-tests)

add_executable(metagl-thread-tests
    test_threads.cpp
)
target_link_libraries(metagl-thread-tests PRIVATE meta-gl::meta-gl)
target_compile_features(metagl-thread-tests PRIVATE cxx_std_23)
set_target_properties(metagl-thread-tests PROPERTIES CXX_EXTENSIONS NO)
metagl_apply_warnings(metagl-thread-tests)
metagl_stage_runtime(metagl-thread-tests)
add_test(NAME metagl-thread-test COMMAND metagl-thread-tests)

if(UNIX AND BUILD_SHARED_LIBS AND NOT APPLE)
    find_program(READELF_EXE readelf)
    find_package(Python3 REQUIRED COMPONENTS Interpreter)
    if(READELF_EXE AND Python3_Interpreter_FOUND)
        add_test(NAME metagl-soname-test
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_soname.py
            $<TARGET_FILE:meta-gl>
            "libmeta-gl.so.0"
        )
    endif()
endif()

find_package(Python3 REQUIRED COMPONENTS Interpreter)
add_test(
    NAME metagl-api-consistency-test
    COMMAND ${Python3_EXECUTABLE} ${PROJECT_SOURCE_DIR}/tools/verify_api.py
)

add_test(
    NAME metagl-installed-package-test
    COMMAND ${CMAKE_COMMAND}
        -DMETAGL_SOURCE_DIR=${PROJECT_SOURCE_DIR}
        -DMETAGL_BUILD_DIR=${PROJECT_BINARY_DIR}
        -DMETAGL_TEST_CONFIG=$<CONFIG>
        -P ${CMAKE_CURRENT_SOURCE_DIR}/test_installed_package.cmake
)

if(METAGL_BUILD_GPU_TESTS)
    find_path(METAGL_EGL_INCLUDE_DIR EGL/egl.h REQUIRED)
    find_library(METAGL_EGL_LIBRARY NAMES EGL REQUIRED)

    add_executable(metagl-egl-smoke-tests egl_smoke.cpp)
    target_link_libraries(metagl-egl-smoke-tests
        PRIVATE
            meta-gl::meta-gl
            ${METAGL_EGL_LIBRARY}
    )
    target_include_directories(metagl-egl-smoke-tests
        PRIVATE ${METAGL_EGL_INCLUDE_DIR})
    target_compile_features(metagl-egl-smoke-tests PRIVATE cxx_std_23)
    set_target_properties(metagl-egl-smoke-tests PROPERTIES CXX_EXTENSIONS NO)
    metagl_apply_warnings(metagl-egl-smoke-tests)
    metagl_stage_runtime(metagl-egl-smoke-tests)

    add_test(NAME metagl-egl-smoke-test COMMAND metagl-egl-smoke-tests)
    set_tests_properties(metagl-egl-smoke-test PROPERTIES
        ENVIRONMENT "EGL_PLATFORM=surfaceless")
endif()
