#include <thread>
#include <mutex>
#include <chrono>
#include <algorithm>
#include <queue>
#include <iostream>
#include <atomic>

#define optimize

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
mutex mqueue;
matrix_t** matrix = new matrix_t*[FILA];
uint64_t sum = 0;
stats medidas[EJECUCIONES];


atomic<uint64_t> thread_alive(0);
atomic<uint64_t> trabajo_completo(0);
atomic<bool>     should_live(true);

queue<pair<accion,fila_t>> tareas;

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


//estos threads estan vivos durante la ejecucion del programa.
//la idea es reusarlos para calcular la suma cada vez.
void tarea_hilo(int thread_idx) {
    pair<accion,fila_t>tarea;
    bool could_pop;
    uint64_t idx_bit = 1<<thread_idx;
    uint64_t idx_mask = 0xFFFFFFFF ^ idx_bit;
    //usamos thread_alive para saber si el thread aun esta corriendo.
    //no es necesario en realidad pero ayuda con la depuacion
    thread_alive |=idx_bit;
    while(should_live) {
        //el lock es necesario por que queue NO es threadsafe
        mqueue.lock();
        if(tareas.size() == 0) {
            mqueue.unlock();
            this_thread::yield();
            continue;
        }
        tarea = tareas.front();
        tareas.pop();
        mqueue.unlock();
        if(likely(tarea.first == sumar)){
            uint64_t temp_sum = 0;
            matrix_t* row = matrix[tarea.second];
            for(uint64_t c = 0; c < COLUMNA; c++) {
                temp_sum += row[c]; // Cambio en el orden de los índices	
            }
            {
                lock_guard<mutex> lock(mtx);
                sum += temp_sum;
                trabajo_completo++;
            }
        }
    }
    thread_alive &= idx_mask;
}


void Manejador() {
    trabajo_completo = 0;
    for(int i = 0; i < FILA;) {
        mqueue.lock();
        while(tareas.size() < num_tareas && i < FILA) {
            tareas.push(make_pair(sumar,i++));
        }
        mqueue.unlock();
    }
    while (trabajo_completo.load() < FILA) this_thread::yield();
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
        hilos[i] = thread(tarea_hilo, i);
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