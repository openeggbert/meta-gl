cmake_minimum_required(VERSION 3.23)

add_executable(hello-metagl
    hello_metagl.cpp
)

target_link_libraries(hello-metagl PRIVATE meta-gl::meta-gl)
target_compile_features(hello-metagl PRIVATE cxx_std_23)
set_target_properties(hello-metagl PROPERTIES CXX_EXTENSIONS NO)
metagl_apply_warnings(hello-metagl)
metagl_stage_runtime(hello-metagl)
