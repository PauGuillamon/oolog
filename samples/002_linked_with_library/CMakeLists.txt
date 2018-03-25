
cmake_minimum_required(VERSION 3.0)

project(sample_002)

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/samples)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

set(SOURCES
	main.cpp
)


add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} oolog)


