cmake_minimum_required(VERSION 3.14)
project(ListaORGA C)

set(CMAKE_C_STANDARD 99)

add_executable(ListaORGA ListaSimplementeEnlazada.c lista.h TestLista.c)