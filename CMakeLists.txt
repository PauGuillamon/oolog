
cmake_minimum_required(VERSION 3.0)


add_subdirectory(test)
add_subdirectory(src)
add_subdirectory(samples)

# TODO PGJ: a decidir si tenir-ho aqui o al subdir test
enable_testing()
add_test(oologTest ${CMAKE_BINARY_DIR}/bin/test/oologTest)
