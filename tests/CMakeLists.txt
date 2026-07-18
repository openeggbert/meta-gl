cmake_minimum_required(VERSION 3.23)

add_executable(metagl-tests
    test_compile.cpp
)
target_link_libraries(metagl-tests PRIVATE meta-gl::meta-gl)
target_compile_features(metagl-tests PRIVATE cxx_std_23)
set_target_properties(metagl-tests PROPERTIES CXX_EXTENSIONS NO)
metagl_apply_warnings(metagl-tests)
add_test(NAME metagl-compile-tests COMMAND metagl-tests)

add_executable(metagl-mock-tests
    test_mock_loader.cpp
)
target_link_libraries(metagl-mock-tests PRIVATE meta-gl::meta-gl)
target_compile_features(metagl-mock-tests PRIVATE cxx_std_23)
set_target_properties(metagl-mock-tests PROPERTIES CXX_EXTENSIONS NO)
metagl_apply_warnings(metagl-mock-tests)
add_test(NAME metagl-mock-loader-test COMMAND metagl-mock-tests)

add_test(
    NAME metagl-installed-package-test
    COMMAND ${CMAKE_COMMAND}
        -DMETAGL_SOURCE_DIR=${PROJECT_SOURCE_DIR}
        -DMETAGL_BUILD_DIR=${PROJECT_BINARY_DIR}
        -DMETAGL_TEST_CONFIG=$<CONFIG>
        -P ${CMAKE_CURRENT_SOURCE_DIR}/test_installed_package.cmake
)
