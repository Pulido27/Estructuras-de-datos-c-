#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <random>
#include <algorithm>
#include "Headers/fifo.h"

using namespace std;
using namespace chrono;

#define FILA 10000
#define COLUMNA 10000
#define num_hilos 6
#define pausas 10
#define Kill_thread 4
mutex mtx;
uint64_t** matrix = new uint64_t*[FILA];

enum accion{
    sumar,
    esperar,
    terminar,
};

void inicializar_matrix() {
    for(int i = 0; i < FILA; i++){
        matrix[i] = new uint64_t[COLUMNA];
        for(int j = 0; j < COLUMNA; j++) {
            matrix[i][j] = j + i * COLUMNA; // Cambio en el orden de los índices	
        }	
    }

}

void finalizar_matrix() {
    for (int i = 0; i < FILA; i++) {
        delete[] matrix[i];  // Liberar las columnas de cada fila
    }
    delete[] matrix;  // Liberar las filas
}

void suma_fila(uint64_t& num, int fila) {
    num = 0;
        for(uint64_t c = 0; c < COLUMNA; c++) {
            num += matrix[fila][c]; // Cambio en el orden de los índices	
        }	
}

void tarea_hilo(Fifolifo<pair<accion,int>>& tareas, uint64_t& sum) {
    
    optional<pair<accion,int>>temp;
    while(true) {

        temp = tareas.pop();
        
        if(!temp || temp.value().first == terminar){
            return;
        }

        if(temp.value().first == sumar){
            uint64_t temp_sum = 0;
            suma_fila(temp_sum,temp.value().second);
            
            {
                lock_guard<mutex> lock(mtx);
                sum += temp_sum;
            }
        }
    }
}

vector<pair<accion,int>> Mixer(){
    vector<pair<accion,int>> v;
    for(int i = 0; i < FILA; i++) {
        v.push_back(make_pair(sumar,i));
    }

    for(int i = 0; i < pausas ;i++){
        v.push_back(make_pair(esperar,0));
    }

    for(int i = 0; i < Kill_thread ;i++){
        v.push_back(make_pair(terminar,0));
    }

    random_device rd;
    mt19937 gen(rd());

    // Desordenar el vector
    shuffle(v.begin(), v.end(), gen);

    return v;
}

uint64_t Manejador() {
    uint64_t sum = 0;
    int dim = FILA + pausas + Kill_thread;
    Fifolifo<pair<accion,int>> tareas(dim);
    vector<pair<accion,int>> pre_tareas = Mixer();

    for(int i = 0; i < dim; i++) {
        tareas.push(pre_tareas[i]);
    }
  
    vector<thread> hilos(num_hilos);
    for(int i = 0; i < num_hilos; i++) {      
        hilos[i] = thread(tarea_hilo, ref(tareas), ref(sum));
    }

    for(auto& hilo : hilos) {        
        hilo.join();
    }
    
    return sum;
}

int main() {
    inicializar_matrix();

    auto start = steady_clock::now();
        cout << Manejador()<<endl; 
        auto stop = steady_clock::now();
        auto elapsed_normal = duration_cast<milliseconds>(stop - start);
        cout << "Tiempo de suma(): " << elapsed_normal.count() << " milisegundos" << endl;
    finalizar_matrix();
    return 0;
}