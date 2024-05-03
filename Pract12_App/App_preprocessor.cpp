#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

//Clase para manejar archivos
class File {
	string name;
	ifstream file;
	ofstream index;
	
	//Funcion para abrir el arvhivo
	void open_file() {
		file.open(name, ios::binary);
	    // Verificar si se pudo abrir el archivo
	    if (!file.is_open()) {
	        cerr << "No se pudo abrir el archivo." << endl;
	    } 
	}	
	
	//Funcion para generar el arvhivo donde se guardaran los indices
	void index_file_generator() {
		
		size_t pos = name.find_last_of('.');
		string new_name = name.substr(0, pos);
		new_name = new_name + "_index.bin";
		
		index.open(new_name, ios::binary);
		
		// Verificar si se creo el indice
		if (!index.is_open()) {
	        cerr << "No se pudo crear el archivo index." << endl;
	    }
	}
	
	//Funcion para obtener la posicion de la linea (la valida y si es invalida regresa -1)
	//Funcion para escribir la posicion si es valida o cero en su defecto.
	long get_pos(char& character, ifstream& file) {
		long pos;
		if (character == '0'){
			return pos = -1;
		}
		return pos = static_cast<long>(file.tellg()) + 1;
	}
	
public:
	File(string s) {
		name = s;
	}
	
	//funcion para rellenar el indice
	void index_content_generator() {
	    
	    open_file();
	    
	    index_file_generator();
	    
	    
	    long pos = 0;
		char character;
	    //Ciclo para escribir el indice validando si es valido(1) o no(0)
		while (file.get(character)) {
			if (character == ',') {
				
				//recorre el caracter para obtener el numero de validacion
				file.get(character);
	    
	    		//obtiene la posicion
	    		pos = get_pos(character,file);
				
				//Escribe el indice reinterpretando la dir de memoria del entero como char y asignandole 4 bytes a la escritura
				index.write(reinterpret_cast<char*>(&pos), 4);
				
				//ignore en este caso se usa para ignorar todos los caracteres hasta encontrar el salto de linea
				file.ignore(numeric_limits<std::streamsize>::max(), '\n');
			}
	    }
	    
	    file.close();
	    index.close();
	} 	

};

int main(){
	
	File file1("hugefile.txt");
	
	file1.index_content_generator();
	
	return 0;
}
