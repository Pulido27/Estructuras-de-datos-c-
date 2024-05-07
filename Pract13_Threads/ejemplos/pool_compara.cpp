#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <random>
#include <algorithm>
#include <iostream>
#include <atomic>
#include <assert.h>

//use_mpmc_queue    = 1
//use_locked_queue  = 2
//use_fifo          = 3
//use_Fifolifo      = 4
#define QUEUE 3
#define optimize

#if QUEUE == 1
  #include "mpmc_fifo.h"
#elif QUEUE == 2
  #include "fifo_lock.h"
#elif QUEUE == 3
  #include "fifo_lockless.h"
#elif QUEUE == 4
  #include "fifolifo.h"
#endif


using namespace std;
using namespace chrono;
using fila_t = int;
using matrix_t = uint8_t;

#ifdef optimize
#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)
#else
#define likely(x) (x)
#define unlikely(x) (x)
#endif

#define FILA 1000
#define COLUMNA 100000
#define EJECUCIONES 100
#define num_hilos 8
#define num_tareas 16

enum accion{
    noop,
    sumar
};

struct stats {
    uint64_t elapsed;
    uint64_t resultado;
    bool     invalid_sum;
};

static_assert(num_hilos < 64);

mutex mtx;
matrix_t** matrix = new matrix_t*[FILA];
uint64_t sum = 0;
stats medidas[EJECUCIONES];

atomic<bool>     should_live(true);
atomic<uint64_t> trabajo_completado(0);

#if QUEUE == 1
mpmc_bounded_queue<pair<accion,fila_t>> tareas(num_tareas);
#elif QUEUE == 2
thread_safe_fifo<pair<accion,fila_t>> tareas(num_tareas);
#elif QUEUE == 3
fifo<pair<accion,fila_t>> tareas(num_tareas);
#elif QUEUE == 4
Fifolifo<pair<accion,fila_t>> tareas(num_tareas);
#endif

void inicializar_matrix() {
    for(int i = 0; i < FILA; i++){
        matrix[i] = new matrix_t[COLUMNA];
        for(int j = 0; j < COLUMNA; j++) {
            matrix[i][j] = 1;
        }
    }
}

void finalizar_matrix() {
    for (int i = 0; i < FILA; i++) {
        delete[] matrix[i];  // Liberar las columnas de cada fila
    }
    delete[] matrix;  // Liberar las filas
}

void tarea_hilo() {
    pair<accion,fila_t>tarea;
    bool could_pop;
#if QUEUE != 1
    optional<pair<accion,fila_t>> temp_pop;
#endif

    while(should_live) {
#if QUEUE == 1
        could_pop = tareas.pop(tarea);
#else
        temp_pop = tareas.pop();
        could_pop = temp_pop.has_value();
        if(unlikely(could_pop)) {
            tarea = temp_pop.value();
        }
#endif
        if(likely(!could_pop)) {
            this_thread::yield();
            continue;
        }
        if(likely(tarea.first == sumar)){
            uint64_t temp_sum = 0;
            matrix_t* row = matrix[tarea.second];
    
            for(uint64_t c = 0; c < COLUMNA; c++) {
                temp_sum += row[c]; // Cambio en el orden de los índices	
            }
            {
                lock_guard<mutex> lock(mtx);
                sum += temp_sum;
                trabajo_completado++;
            }
        }
    }
}


void Manejador() {
    trabajo_completado=0;
    for(int i = 0; i < FILA;) {
        while(!tareas.push(make_pair(sumar,i)) ) {
            this_thread::yield();
        }
        i++;
    }
    //espera a que se termine el trabajo
    auto start = steady_clock::now();
    while (trabajo_completado < FILA) {
        //si no se ha terminado despues de 1 segundo. terminar la ejecucion
        auto stop = steady_clock::now();
        auto elapsed = duration_cast<milliseconds>(stop - start);
        if(elapsed.count() > 1000){
            break;
        }
        this_thread::yield();
    }
}

void loop_main(int n) {
    sum = 0;
    
    auto start = steady_clock::now();
    Manejador();
    auto stop = steady_clock::now();
    auto elapsed_normal = duration_cast<microseconds>(stop - start);
    medidas[n].elapsed = elapsed_normal.count();
    medidas[n].invalid_sum = sum != FILA*COLUMNA;
    medidas[n].resultado = sum;
}

void imprime_resultados(){
    uint64_t min_time=medidas[0].elapsed;
    uint64_t max_time=0;
    uint64_t avg_time=0;
    uint32_t  errores = 0;
    cout<<endl<<endl;
    for(int i=0; i<EJECUCIONES; i++) {
        avg_time += medidas[i].elapsed;
        max_time = max(max_time, medidas[i].elapsed);
        min_time = min(min_time, medidas[i].elapsed);
        if(medidas[i].invalid_sum) {
            errores++;
        }
        cout<<"Ejecucion: "<< i << ", tiempo: "<< medidas[i].elapsed << "us,  resultado: " << medidas[i].resultado<<endl;
    }
    avg_time /= EJECUCIONES;
    cout<<"min: "<<min_time <<"us"<<endl;
    cout<<"max: "<<max_time <<"us"<<endl;
    cout<<"avg: "<<avg_time <<"us"<<endl;
    cout<<"errores: "<< errores <<endl;
}

int main() {
    inicializar_matrix();
    vector<thread> hilos(num_hilos);
    for(int i = 0; i < num_hilos; i++) {
        hilos[i] = thread(tarea_hilo);
    }

    for( int i = 0; i<EJECUCIONES; i++ ) {
        loop_main(i);
    }

    should_live = false;
    this_thread::sleep_for(200ms);
    for(auto& hilo : hilos) {
        hilo.join();
    }

    imprime_resultados();

    finalizar_matrix();
    return 0;
}