#include <iostream>
#include <iomanip>

#include "../include/comun.h"
#include "referencia.h"
#include <chrono>

using namespace std;

/*
    Este es un problema usado en entrevistas.
    Obtener la moda, mediana y el promedio de un stream de numeros.
    en este problema los valores se calculan en diferentes intervalos para medir desempe;o del algoritmo.

    nota: se recomienda NO imprimir en la clase solucion para asegurar que la ejecucion sea mas rapida.
*/
#include <set>
#include <unordered_map>

class solucion {
    private:
        long long suma;
        long double promedio;
        double mediana;
        multiset<int>::iterator iterador;
        pair<int, int> moda;
        unordered_map<int, int> frecuencia_map;
        multiset<int> numeros;
    
    public:
        solucion()  : suma(0), promedio(0), mediana(0) {}

        void agregar(int num) {
            numeros.insert(num);
            suma += num;

            //actualizacion de moda;
            frecuencia_map[num]++;

            //actualizacion de la mediana;
            if(numeros.size()==1){
                iterador = numeros.begin();
                return;
            }

            if(numeros.size() % 2 == 0) {
                if(num > *iterador) {
                    advance(iterador,1);
                }
                return;
            }

            if(num < *iterador) {
                advance(iterador,-1);
            }
        }

        long double Promedio () {
            return static_cast<long double>(suma) / numeros.size();
        }

        int Mediana() {
        mediana =  *iterador;
        return mediana;	
        }

        int Moda() {
            for( const auto& temp : frecuencia_map ) {
                if( moda.second < temp.second ) {
                    moda = temp;
                }
            }
            return moda.first;	
        }
};

int main(){
    generator g;
    solucion  sol;

    auto s_t = std::chrono::high_resolution_clock::now();
    //procesa 5M + 1 elementos para evitar tener que sacar promedios
    for (int i=0; i<=5000000; i++) {
        sol.agregar(g.n());
        switch(i){
            case 100:
            case 1000:
            case 1000000:
            case 5000000:
                std::cout<<i<<": moda: " << sol.Moda();
                std::cout<<" mediana:" << sol.Mediana();
                std::cout<<std::fixed << std::setprecision(2);
                std::cout<<" promedio: " << std::setw(15) << sol.Promedio() <<std::endl;
                break;
            default:
                break;
        }
    }
    auto s_e = std::chrono::high_resolution_clock::now();
    std::cout<<"tiempo:"<<std::chrono::duration_cast<std::chrono::milliseconds>(s_e - s_t).count()<<"ms"<<std::endl<<std::endl;

    //Prueba de referencia. esto es para ver que los resultados sean correctos y para comparar el tiempo de ejecucion
    referencia_number_stream  ref;
    g.reset(); //usemos la misma lista de numeros para poder comparar los resultados
    auto r_t = std::chrono::high_resolution_clock::now();
    for (int i=0; i<=5000000; i++) {
        ref.add(g.n());
        switch(i){
            case 100:
            case 1000:
            case 1000000:
            case 5000000:
                std::cout<<i<<": moda: " << ref.moda();
                std::cout<<" mediana:" << ref.mediana();
                std::cout<<std::fixed << std::setprecision(2);
                std::cout<<" promedio: " << std::setw(15) << ref.promedio() <<std::endl;
                break;
            default:
                break;
        }
    }
    auto r_e = std::chrono::high_resolution_clock::now();
    std::cout<<"tiempo:"<<std::chrono::duration_cast<std::chrono::milliseconds>(r_e - r_t).count()<<"ms"<<std::endl;
    return 0;
}