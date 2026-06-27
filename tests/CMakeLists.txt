cmake_minimum_required(VERSION 3.23)

add_executable(metagl-tests
    test_compile.cpp
)

target_link_libraries(metagl-tests PRIVATE meta-gl::meta-gl)
target_compile_features(metagl-tests PRIVATE cxx_std_23)

add_test(NAME metagl-compile-tests COMMAND metagl-tests)
