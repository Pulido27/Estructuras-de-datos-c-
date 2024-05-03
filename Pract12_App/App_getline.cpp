#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <random>
#include <vector>
#include <limits>
#include <thread>

using namespace std;
using namespace chrono;

ifstream file;
ifstream index_file;

struct Line_time{
	string line;
	long long time;
};

void open_files(string text) {
	file.open(text, ios::binary);
	
	size_t pos = text.find_last_of('.');
	string index_name = text.substr(0, pos);
	index_name = index_name + "_index.bin";
	index_file.open(index_name, ios::binary);	
}

Line_time get_line(long line, string& s) {
	//Marca el tiempo de inicio
	
	auto start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();	
	
	long pos = 0;
	
	//Se coloca la posicion de lectura en el inicio de la linea indicada (*4 porque estan guardados los datos en binario 4 bytes)
	index_file.seekg(line*4);
	//Se lee y guarda el el contenido de esos 4 bytes en pos
	index_file.read(reinterpret_cast<char*>(&pos),4);
		
	//Se usa la pos del index para localizar la pos de la linea
	file.seekg(pos);
	
	//Se crea un buffer de 4096 bytes (4kilobytes que es algunas veces la unidad minima que lee un disco)
	char buffer[4096];
	
	//Se lee un caracter menos pa asegurar el caracter nulo que marca final de linea y evitar desbordamiento de buffer
	file.get(buffer, 4095,'\n');
	
	// Se assing para asignarle al string el contenido del buffer
	s.assign(buffer);
	
	//Marca el tiempo del final
	auto stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	
	return {s,stop-start};
}

#define iteraciones 10000

void customer() {
	//generacion de semilla diferente en cada corrida usando el reloj de chrono en epoch
	//no se uso random device porque este hardware no lo soporta
	//auto seed = static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count());	
	
	// Generador Mersenne Twister de numeros aleatorios a travez de la semilla
	mt19937 gen(5);
	
	uniform_int_distribution<long> dis(0, 8388607); // Distribución uniforme entre  0 y 8388607
	
	Line_time lines[iteraciones];
	
	string buffer;
    // Realiza 10 busquedas y lecturas de lineas y su guardado en lines
    for (int i = 0; i < iteraciones; i++) {
    	long line = dis(gen);
		lines[i] = get_line(line, buffer);
    }
	
	
	long long max_time = 0;
	long long min_time = LLONG_MAX;
	long long average_time = 0;
	
	for( int i = 0; i < iteraciones; i++) {
		max_time = max(max_time,lines[i].time);
		min_time = min(min_time,lines[i].time);
		average_time+= lines[i].time;
	}
	
	cout << "max " << max_time << "us" <<endl;
	cout << "min " << min_time <<  "us" <<endl;
	cout << "average " << average_time/static_cast<float>(iteraciones) << "us" << endl;
}



int main() {
	
	open_files("hugefile.txt");
	cout<<"paso2";
	customer();
	//thread hilo1(customer);
	//thread hilo2(customer);

	//hilo1.join();
	//hilo2.join();
	
	cout << "hola mundo";

    return 0;
}
