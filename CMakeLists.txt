cmake_minimum_required(VERSION 3.23)

project(meta-gl
    VERSION 0.2.0
    DESCRIPTION "Low-level type-safe C++ wrapper over OpenGL function pointers"
    LANGUAGES CXX)

# Keep conventional BUILD_SHARED_LIBS behavior without forcing a cache option
# into parent projects that consume meta-gl via add_subdirectory().
if(PROJECT_IS_TOP_LEVEL AND NOT DEFINED BUILD_SHARED_LIBS)
    option(BUILD_SHARED_LIBS "Build libraries as shared libraries" OFF)
endif()

# Backward-compatible aliases for the pre-0.3 standalone option names.
if(PROJECT_IS_TOP_LEVEL AND DEFINED SANITIZE AND NOT DEFINED METAGL_SANITIZE)
    set(METAGL_SANITIZE "${SANITIZE}")
endif()
if(PROJECT_IS_TOP_LEVEL AND DEFINED BUILD_TESTING AND NOT DEFINED METAGL_BUILD_TESTS)
    set(METAGL_BUILD_TESTS "${BUILD_TESTING}")
endif()
if(PROJECT_IS_TOP_LEVEL AND DEFINED BUILD_EXAMPLES AND NOT DEFINED METAGL_BUILD_EXAMPLES)
    set(METAGL_BUILD_EXAMPLES "${BUILD_EXAMPLES}")
endif()

option(METAGL_SANITIZE "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)
option(METAGL_BUILD_TESTS "Build the meta-gl test suite" OFF)
option(METAGL_BUILD_GPU_TESTS "Build EGL tests that require a real GL implementation" OFF)
option(METAGL_BUILD_EXAMPLES "Build the meta-gl examples" OFF)
option(METAGL_BUILD_DOCS "Build Doxygen API documentation" OFF)
option(METAGL_ENABLE_DEBUG_LOGGING "Compile per-call GL debug logging into meta-gl" OFF)
option(METAGL_DEBUG_IMMEDIATE "Flush debug logging after every GL call" OFF)

add_library(meta-gl)
add_library(meta-gl::meta-gl ALIAS meta-gl)

set_target_properties(meta-gl PROPERTIES
    CXX_EXTENSIONS NO
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    WINDOWS_EXPORT_ALL_SYMBOLS ON)

target_compile_features(meta-gl PUBLIC cxx_std_23)

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

function(metagl_apply_warnings target_name)
    target_compile_options(${target_name} PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic>
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive- /Zc:preprocessor>
    )
endfunction()

metagl_apply_warnings(meta-gl)

if(METAGL_ENABLE_DEBUG_LOGGING OR METAGL_DEBUG_IMMEDIATE)
    target_compile_definitions(meta-gl PRIVATE METAGLDEBUG)
endif()
if(METAGL_DEBUG_IMMEDIATE)
    target_compile_definitions(meta-gl PRIVATE METAGLDEBUG_IMMEDIATE)
endif()

if(METAGL_SANITIZE)
    target_compile_options(meta-gl PUBLIC
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-fsanitize=address,undefined -fno-omit-frame-pointer>
    )
    target_link_options(meta-gl PUBLIC
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-fsanitize=address,undefined>
    )
endif()

if(METAGL_BUILD_GPU_TESTS AND NOT METAGL_BUILD_TESTS)
    message(FATAL_ERROR "METAGL_BUILD_GPU_TESTS requires METAGL_BUILD_TESTS=ON")
endif()

if(METAGL_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(METAGL_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(METAGL_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Doxyfile.in"
        "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
        @ONLY
    )
    add_custom_target(metagl-docs
        COMMAND Doxygen::doxygen "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Generating meta-gl API documentation"
        VERBATIM
    )
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS meta-gl
        EXPORT meta-gl-targets
        FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY
        third_party/Khronos/GLES2
        third_party/Khronos/GLES3
        third_party/Khronos/KHR
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES
        LICENSE
        third_party/Khronos/LICENSE-MIT.txt
        DESTINATION ${CMAKE_INSTALL_DATADIR}/licenses/meta-gl
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
    COMPATIBILITY SameMinorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/meta-glConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/meta-glConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/meta-gl
)
