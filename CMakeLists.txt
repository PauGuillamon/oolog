
cmake_minimum_required(VERSION 3.0)

project(oologProject)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MP")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} /MP")
endif()

option(BUILD_SAMPLES "Build oolog samples" ON)
option(BUILD_TESTS "Build oolog tests" ON)

add_subdirectory(src)
if (BUILD_TESTS)
    add_subdirectory(test)
endif()
if (BUILD_SAMPLES)
    add_subdirectory(samples)
endif()

if (BUILD_TESTS)
    enable_testing()
    add_test(oologTest ${CMAKE_BINARY_DIR}/bin/test/oologTest)
endif()
