cmake_minimum_required(VERSION 3.23)

project(meta-gl
    VERSION 0.1.0
    DESCRIPTION "Low-level type-safe C++ wrapper over OpenGL function pointers"
    LANGUAGES CXX)

add_library(meta-gl)
add_library(meta-gl::meta-gl ALIAS meta-gl)

set_target_properties(meta-gl PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR})

target_sources(meta-gl
    PRIVATE
        src/Functions.cpp
        src/Context.cpp
        src/Debug.cpp
)

target_sources(meta-gl
    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
        include/metagl/metagl.hpp
        include/metagl/Types.hpp
        include/metagl/Enums.hpp
        include/metagl/Functions.hpp
        include/metagl/Loader.hpp
        include/metagl/Context.hpp
        include/metagl/Capabilities.hpp
        include/metagl/ContextEvents.hpp
        include/metagl/Emscripten.hpp
        include/metagl/Debug.hpp
        include/metagl/EnumNames.hpp
)

target_include_directories(meta-gl
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party/Khronos>
        $<INSTALL_INTERFACE:include>
)

target_compile_options(meta-gl PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

option(SANITIZE "Enable AddressSanitizer and UndefinedBehaviorSanitizer (GCC/Clang only)" OFF)
if(SANITIZE)
    target_compile_options(meta-gl PUBLIC
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-fsanitize=address,undefined -fno-omit-frame-pointer>
    )
    target_link_options(meta-gl PUBLIC
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-fsanitize=address,undefined>
    )
endif()

option(BUILD_TESTING "Build the test suite" OFF)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS meta-gl
        EXPORT meta-gl-targets
        FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT meta-gl-targets
        FILE meta-glTargets.cmake
        NAMESPACE meta-gl::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/meta-gl
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/meta-glConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/meta-glConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/meta-gl
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/meta-glConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/meta-glConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/meta-glConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/meta-gl
)
