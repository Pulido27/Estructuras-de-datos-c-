cmake_minimum_required(VERSION 3.5)
project(Pract11_Cache)

# Habilitar pruebas
enable_testing()

# Establecer la version de c++ que se usara
set(CMAKE_CXX_STANDARD 17)

# Hacer obligatorio que la use 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Incluir directorio de Google Test
find_package(GTest CONFIG REQUIRED)

# Incluir directorio de encabezados
include_directories(${CMAKE_SOURCE_DIR}/include)

# Generamos el ejecutable
add_executable(cache2 "cache2.cpp")

# Agregamos la biblioteca de Google Test para que se compile
target_link_libraries(cache2 gtest gtest_main)

#Añasimo el directorio de
add_subdirectory(tests)





