#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <chrono>

using namespace std;
using namespace chrono;

#define lado 10000
#define num_hilos 10

int matrix[lado][lado];
mutex mtx;

void inicializar_matrix() {
    for(int i = 0; i < lado; i++) {		
        for(int j = 0; j < lado; j++) {
            matrix[i][j] = j + i * lado; // Cambio en el orden de los índices	
        }	
    }
}

long long suma() {
    long long sum = 0;
    for(int i = 0; i < lado; i++) {	
        for(int j = 0; j < lado; j++) {
            sum += matrix[i][j]; // Cambio en el orden de los índices	
        }	
    }
    return sum;
}

void suma_fila(long long& num, int fila) {
    num = 0;
    for(int i = 0; i < lado; i++) {
        num += matrix[fila][i];// Cambio en el orden de los índices
    }
}

void tarea_hilo(queue<int>& tareas, long long& sum) {
    while(true) {
        int tarea;
        {
            lock_guard<mutex> lock(mtx);
            if(tareas.empty()) {
                break;
            }
            tarea = tareas.front();
            tareas.pop();
        }
        long long temp_sum = 0;
        suma_fila(temp_sum, tarea);
        {
            lock_guard<mutex> lock(mtx);
            sum += temp_sum;
        }
    }
}

long long suma_thread() {
    long long sum = 0;
    queue<int> tareas;
    for(int i = 0; i < lado; i++) {
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

     cout << suma_thread();  
    //cout << suma_thread()<<endl;  
    stop = steady_clock::now();
    elapsed_normal = duration_cast<milliseconds>(stop - start);
    cout << "Tiempo de suma_thread():" << elapsed_normal.count() << " milisegundos" << endl;
    return 0;
}
