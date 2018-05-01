
cmake_minimum_required(VERSION 3.0)

project(sample_004)

set (CMAKE_CXX_STANDARD 11)

find_package(Threads REQUIRED)

if(UNIX)
	set(CMAKE_CXX_FLAGS "-pthread")
elseif(MSVC)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
endif()


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)

set(SOURCES
	main.cpp
)


add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} oolog)


