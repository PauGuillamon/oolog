
cmake_minimum_required(VERSION 3.0)

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/samples)

set(SOURCES
	main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/oolog.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/printers/ConsoleLogPrinter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/printers/ColoredLogPrinter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/printers/EndlLogPrinter.cpp
)
add_executable(main ${SOURCES})

