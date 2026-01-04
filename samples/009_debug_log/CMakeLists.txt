
cmake_minimum_required(VERSION 3.30)

project(sample_009)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

set(SOURCES
	main.cpp
)


add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} oolog-static)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)

