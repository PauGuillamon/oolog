
cmake_minimum_required(VERSION 3.0)

project(oolog)

set(CMAKE_CXX_STANDARD 11)


set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 0)
set(${PROJECT_NAME}_VERSION_REVISION 1)


include_directories(
    $[CMAKE_CURRENT_LIST_DIR]/../include
    $[CMAKE_CURRENT_LIST_DIR]/../include/printers
)


configure_file(
    version.h.in
    version.h
)


set(SOURCES
    oolog.cpp
    printers/ConsoleLogPrinter.cpp
    printers/ColoredLogPrinter.cpp
    printers/EndlLogPrinter.cpp
)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
add_library(${PROJECT_NAME}-static STATIC ${SOURCES})


