
cmake_minimum_required(VERSION 3.30)

project(sample_001)


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

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)

