# Añadir el ejecutable para las pruebas
add_executable(test_b-tree test_b-tree.cpp)

# Enlazar Google Test con el ejecutable de pruebas
target_link_libraries(test_b-tree gtest gtest_main)

# Añadir un test para que CMake pueda ejecutarlo
add_test(NAME Testbtree COMMAND test_b-tree)
