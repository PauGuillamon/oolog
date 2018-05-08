
cmake_minimum_required(VERSION 3.0)

project(sample_001)

set (CMAKE_CXX_STANDARD 11)


include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../../include
	${CMAKE_CURRENT_SOURCE_DIR}/../../include/printers
)

set(SOURCES
	main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../src/oolog.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../src/printers/Console.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../src/printers/decorators/Decorator.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../src/printers/decorators/NewLine.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})

