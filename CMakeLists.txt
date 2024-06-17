cmake_minimum_required(VERSION 3.5)
project(estructuras_de_datos)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest CONFIG REQUIRED)


#practica 1
add_executable(fifolifo "Pract1_Fifolifo/fifolifo.cpp")

#practica 2
add_executable(ArbolDeBusqueda "Pract2_ArbolBusqueda/ArbolDeBusqueda.cpp")
add_executable(ArbolDeBusqueda2 "Pract2_ArbolBusqueda/ArbolDeBusqueda2.cpp")
