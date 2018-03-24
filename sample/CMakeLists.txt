

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCES
	main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/oolog.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/LogPrinters/ConsoleLogPrinter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/LogPrinters/ColoredLogPrinter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/LogPrinters/EndlLogPrinter.cpp
)
add_executable(main ${SOURCES})

