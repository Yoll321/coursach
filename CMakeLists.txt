cmake_minimum_required(VERSION 3.23)

set(PATCH_VERSION "1" CACHE STRING "Patch version provided by GitHub Actions")

project(parallel_mean
    LANGUAGES CXX
    VERSION 1.0.${PATCH_VERSION})

find_package(TBB REQUIRED)

add_library(parallel_mean_lib INTERFACE)
target_include_directories(parallel_mean_lib
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(parallel_mean_lib
    INTERFACE 
        TBB::tbb)
target_compile_features(parallel_mean_lib
    INTERFACE
        cxx_std_17)


add_executable(parallel_mean
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_link_libraries(parallel_mean
    PRIVATE
        parallel_mean_lib)