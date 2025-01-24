# Añadir el ejecutable para las pruebas
add_executable(test_cache2 test_cache2.cpp)

# Enlazar Google Test con el ejecutable de pruebas
target_link_libraries(test_cache2 gtest gtest_main)

# Añadir un test para que CMake pueda ejecutarlo
add_test(NAME Testcache2 COMMAND test_cache2)
