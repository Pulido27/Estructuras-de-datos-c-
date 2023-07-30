#include <iostream>
#include <string>
#include <vector>

/*
    las soluciones de este problema deben de regresar listas de palabras que tengan
    un prefijo comun.
    para facilitar las pruebas. las palabras seran sequencias de numeros

    este es un problema que parece dificil pero es simple
*/

struct solucion {
    void agregar(std::string p)
    {

    }
    std::vector<std::string> completar(std::string p)
    {
        return {};
    }
};

#include "referencia.h"

int main(){

    referencia sol;
    sol.agregar("1234");
    sol.agregar("1123");
    sol.agregar("1132");
    sol.agregar("1235");
    sol.agregar("1133");
    sol.agregar("1333");
    sol.agregar("2133");
    sol.agregar("2153");
    sol.agregar("2234");
    sol.agregar("2264");
    sol.agregar("3456");
    sol.agregar("3446");
    sol.agregar("3459");
    sol.agregar("3523");
    sol.agregar("3593");
    sol.agregar("3646");

    for(auto& w: sol.completar("35")) {
        std::cout<<w<<std::endl;
    }
    return 0;
}