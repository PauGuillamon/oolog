

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(main main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../src/oolog.cpp)

