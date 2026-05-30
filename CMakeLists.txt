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

install(TARGETS meta-gl
        EXPORT meta-gl-targets
        FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
