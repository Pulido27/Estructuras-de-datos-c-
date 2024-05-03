// meter cero  a un millon-1 de elementos en una matrix 1000x1000
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;

#define lado 10000
#define hilos 10

int matrix[lado][lado];

void inicializar_matrix() {

	for(int i = 0; i < lado; i++) {		
		for(int j = 0; j < lado; j++) {
			matrix[i][j] = j + i * lado; 	
		}	
	}
}

long suma(){
	long sum = 0;
	for(int i = 0; i < lado; i++) {	
		for(int j = 0; j < lado; j++) {
			sum += matrix[i][j]; 	
		}	
	}
	return sum;
}

void suma_filas(long& num, int indice) {
	num = 0;
	for(int i = indice; i< lado/hilos+indice; i++) {
        for(int j =0; j<lado; j++){
            num += matrix[i][j];
        }
	}
}

long suma_thread(){
	long sumas[lado];
	long sum = 0;
	thread* threads[hilos];
	for(int i=0; i<hilos; i++){
        threads[i] = new thread(suma_filas,ref(sumas[i]),i*lado/hilos);
	}
		
	for(int i = 0; i < hilos ; i++) {
		threads[i]->join();
		delete threads[i];
		sum += sumas[i]; 
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
	cout << suma_thread()<<endl;  
	stop = steady_clock::now();
	elapsed_normal = duration_cast<milliseconds>(stop - start);
    cout << "Tiempo de suma_thread():" << elapsed_normal.count() << " milisegundos" << endl;

	return 0;
}
/*opciones
1 hacerlo igual solo que ahora con 10 hilos

*/