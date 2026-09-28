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

set(CPACK_PACKAGE_NAME "parallel_mean")
set(CPACK_PACKAGE_VENDOR "nom4")
set(CPACK_PACKAGE_CONTACT "nom4@tpu.ru")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Parallelism demonstration")

if(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
elseif(UNIX)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "nom4@tpu.ru")
endif()

include(CPack)
