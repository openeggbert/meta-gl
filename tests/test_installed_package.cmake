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
