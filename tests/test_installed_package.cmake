if(NOT DEFINED METAGL_SOURCE_DIR OR NOT DEFINED METAGL_BUILD_DIR)
    message(FATAL_ERROR "METAGL_SOURCE_DIR and METAGL_BUILD_DIR are required")
endif()

set(install_prefix "${METAGL_BUILD_DIR}/package-test/install")
set(consumer_build "${METAGL_BUILD_DIR}/package-test/consumer-build")

file(REMOVE_RECURSE "${METAGL_BUILD_DIR}/package-test")

set(install_command
    "${CMAKE_COMMAND}" --install "${METAGL_BUILD_DIR}" --prefix "${install_prefix}")
if(METAGL_TEST_CONFIG)
    list(APPEND install_command --config "${METAGL_TEST_CONFIG}")
endif()

execute_process(
    COMMAND ${install_command}
    RESULT_VARIABLE install_result
)
if(NOT install_result EQUAL 0)
    message(FATAL_ERROR "meta-gl installation failed: ${install_result}")
endif()

execute_process(
    COMMAND "${CMAKE_COMMAND}"
        -S "${METAGL_SOURCE_DIR}/tests/package-consumer"
        -B "${consumer_build}"
        "-DCMAKE_PREFIX_PATH=${install_prefix}"
    RESULT_VARIABLE configure_result
)
if(NOT configure_result EQUAL 0)
    message(FATAL_ERROR "Installed-package consumer configure failed: ${configure_result}")
endif()

set(build_command "${CMAKE_COMMAND}" --build "${consumer_build}")
if(METAGL_TEST_CONFIG)
    list(APPEND build_command --config "${METAGL_TEST_CONFIG}")
endif()

execute_process(
    COMMAND ${build_command}
    RESULT_VARIABLE build_result
)
if(NOT build_result EQUAL 0)
    message(FATAL_ERROR "Installed-package consumer build failed: ${build_result}")
endif()

# R12: Run the consumer executable to verify out-of-line symbol resolution.
if(METAGL_TEST_CONFIG)
    set(consumer_exe "${consumer_build}/${METAGL_TEST_CONFIG}/meta-gl-package-consumer")
else()
    set(consumer_exe "${consumer_build}/meta-gl-package-consumer")
endif()

# Also accept the executable without a config subdirectory (single-config generators on Unix).
if(NOT EXISTS "${consumer_exe}" AND EXISTS "${consumer_build}/meta-gl-package-consumer")
    set(consumer_exe "${consumer_build}/meta-gl-package-consumer")
endif()

execute_process(
    COMMAND "${consumer_exe}"
    RESULT_VARIABLE run_result
)
if(NOT run_result EQUAL 0)
    message(FATAL_ERROR "Installed-package consumer executable failed with exit code: ${run_result}")
endif()

# R13: Re-run the consumer explicitly as a static-library consumer.
# This verifies that the installed CMake package works correctly when
# the downstream project forces BUILD_SHARED_LIBS=OFF (the default for
# meta-gl, but we make it explicit to guard against regressions).
set(consumer_build_static "${METAGL_BUILD_DIR}/package-test/consumer-build-static")

execute_process(
    COMMAND "${CMAKE_COMMAND}"
        -S "${METAGL_SOURCE_DIR}/tests/package-consumer"
        -B "${consumer_build_static}"
        "-DCMAKE_PREFIX_PATH=${install_prefix}"
        -DBUILD_SHARED_LIBS=OFF
    RESULT_VARIABLE configure_static_result
)
if(NOT configure_static_result EQUAL 0)
    message(FATAL_ERROR "Static-library consumer configure failed: ${configure_static_result}")
endif()

set(build_static_command "${CMAKE_COMMAND}" --build "${consumer_build_static}")
if(METAGL_TEST_CONFIG)
    list(APPEND build_static_command --config "${METAGL_TEST_CONFIG}")
endif()

execute_process(
    COMMAND ${build_static_command}
    RESULT_VARIABLE build_static_result
)
if(NOT build_static_result EQUAL 0)
    message(FATAL_ERROR "Static-library consumer build failed: ${build_static_result}")
endif()

# Locate and run the static-library consumer executable.
if(METAGL_TEST_CONFIG)
    set(consumer_static_exe "${consumer_build_static}/${METAGL_TEST_CONFIG}/meta-gl-package-consumer")
else()
    set(consumer_static_exe "${consumer_build_static}/meta-gl-package-consumer")
endif()

# Also accept the executable without a config subdirectory (single-config generators on Unix).
if(NOT EXISTS "${consumer_static_exe}" AND EXISTS "${consumer_build_static}/meta-gl-package-consumer")
    set(consumer_static_exe "${consumer_build_static}/meta-gl-package-consumer")
endif()

execute_process(
    COMMAND "${consumer_static_exe}"
    RESULT_VARIABLE run_static_result
)
if(NOT run_static_result EQUAL 0)
    message(FATAL_ERROR "Static-library consumer executable failed with exit code: ${run_static_result}")
endif()
