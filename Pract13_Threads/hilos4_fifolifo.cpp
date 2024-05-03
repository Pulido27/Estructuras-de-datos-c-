#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include "Headers/fifo.h"

using namespace std;
using namespace chrono;

#define FILA 30000
#define COLUMNA 30000
#define num_hilos 10

mutex mtx;
uint64_t** matrix = new uint64_t*[FILA];


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

uint64_t suma() {
    uint64_t sum = 0;
    for(int i = 0; i < FILA; i++) {	
        for(int j = 0; j < COLUMNA; j++) {
            sum += matrix[i][j]; // Cambio en el orden de los índices	
        }	
    }
    return sum;
}

void suma_fila(uint64_t& num, int fila) {
    num = 0;
        for(uint64_t c = 0; c < COLUMNA; c++) {
            num += matrix[fila][c]; // Cambio en el orden de los índices	
        }	
}

void tarea_hilo(Fifolifo<int>& tareas, uint64_t& sum) {
    
    optional<int>temp;
    while(true) {

        temp = tareas.pop();
        
        if(!temp){
            return;
        }

        uint64_t temp_sum = 0;
        suma_fila(temp_sum,temp.value());
        {
            lock_guard<mutex> lock(mtx);
            sum += temp_sum;
        }
    }
}

uint64_t suma_thread() {
    uint64_t sum = 0;
    
    Fifolifo<int> tareas(FILA);
    for(int i = 0; i < FILA; i++) {
        tareas.push(i);
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
	cout << suma()<<endl; 
	auto stop = steady_clock::now();
	auto elapsed_normal = duration_cast<milliseconds>(stop - start);
    cout << "Tiempo de suma(): " << elapsed_normal.count() << " milisegundos" << endl;
	
	
	start = steady_clock::now();
    //for(int i = 0; i<100 ; i++){
        //cout<<"numero: " << i+1 << " "<<suma_thread()<<endl;
        suma_thread();    
    //}
    stop = steady_clock::now();
    elapsed_normal = duration_cast<milliseconds>(stop - start);
    cout << "Tiempo de suma_thread():" << elapsed_normal.count() << " milisegundos" << endl;

    finalizar_matrix();
    return 0;
}