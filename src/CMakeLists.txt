
cmake_minimum_required(VERSION 3.0)

project(oolog)

set(CMAKE_CXX_STANDARD 11)


set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 0)
set(${PROJECT_NAME}_VERSION_REVISION 1)


include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/../include
)


configure_file(
    version.h.in
    version.h
)


set(SOURCES
    oolog.cpp
    printers/Console.cpp
    printers/File.cpp
    printers/Fake.cpp
    printers/decorators/Color.cpp
    printers/decorators/Decorator.cpp
    printers/decorators/Level.cpp
    printers/decorators/NewLine.cpp
    printers/decorators/Timestamp.cpp
)

if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DOOLOG_EXPORTS")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -DOOLOG_EXPORTS")
endif()

add_library(${PROJECT_NAME} SHARED ${SOURCES})
add_library(${PROJECT_NAME}-static STATIC ${SOURCES})


