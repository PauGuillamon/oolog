
cmake_minimum_required(VERSION 3.30)

project(oolog)


set(${PROJECT_NAME}_VERSION_MAJOR 1)
set(${PROJECT_NAME}_VERSION_MINOR 0)
set(${PROJECT_NAME}_VERSION_REVISION 0)


configure_file(
    version.h.in
    version.h
)


set(SOURCES
    oolog.cpp
    printers/Console.cpp
    printers/File.cpp
    printers/Fake.cpp
    printers/RotatedFile.cpp
    printers/decorators/Decorator.cpp
    printers/decorators/Level.cpp
    printers/decorators/NewLine.cpp
    printers/decorators/Split.cpp
    printers/decorators/Timestamp.cpp
)

if(MSVC)
    list(APPEND SOURCES printers/decorators/ColorWin32Console.cpp)
else()
    list(APPEND SOURCES printers/decorators/ColorANSI.cpp)
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd -DOOLOG_EXPORTS")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} /MT -DOOLOG_EXPORTS")
endif()

add_library(${PROJECT_NAME}-shared SHARED ${SOURCES})
add_library(oolog::oolog-shared ALIAS ${PROJECT_NAME}-shared)

add_library(${PROJECT_NAME}-static STATIC ${SOURCES})
add_library(oolog::oolog-static ALIAS ${PROJECT_NAME}-static)

target_include_directories(${PROJECT_NAME}-shared PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../include
)
target_include_directories(${PROJECT_NAME}-static PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../include
)

target_compile_features(${PROJECT_NAME}-shared PUBLIC cxx_std_11)
target_compile_features(${PROJECT_NAME}-static PUBLIC cxx_std_11)
