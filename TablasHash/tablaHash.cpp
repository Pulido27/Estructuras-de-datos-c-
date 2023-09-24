#include <iostream>
#include <list>
#include <functional>
#include <vector>

using namespace std;

template <typename T>
class TablaHash {
public:
	int TAMANO_TABLA;
	
	TablaHash(int size){
		TAMANO_TABLA = size;
		tabla.resize(TAMANO_TABLA);
	}
	
private:
    vector<list<T>> tabla;

    // Función de hash que utiliza std::hash
    //el tipo de dato size es un numero positivo que se adapta a la maquina 
    //normalmente usado para direccion de memoria o indices
	size_t FuncionHash(T clave) {
        hash<T> hashFunc;              // se crea un objeto tipo has recibe datos y devuelve el has
        return hashFunc(clave) % TAMANO_TABLA; // modulo para asegurar que el indice sea valido
    }

public:
    // Método para agregar un valor a la tabla de hash
    void agregar(T valor) {
        size_t indice = FuncionHash(valor);
        tabla[indice].push_back(valor); // push back porque trabajamos con listas enlazadas
    }

    // Metodo para buscar un valor en la tabla de hash
    bool buscar(T valor) {
        size_t indice = FuncionHash(valor);
        //for each en el caso de que hubiera coliciones
        for (const auto& elemento : tabla[indice]) {
            if (elemento == valor) {
                return true; // Valor encontrado
            }
        }
        return false; // Valor no encontrado
    }
};

int main() {
    TablaHash<int> tabla(10);

    // Agregar algunos valores a la tabla
    tabla.agregar(5);
    tabla.agregar(10);
    tabla.agregar(15);

    // Buscar valores en la tabla
    //uso de operador ternario en cout
    cout << "EL valor 5 se encuentra en la tabla? " << (tabla.buscar(5) ? "Si" : "No") << std::endl;
    cout << "EL valor  8se encuentra en la tabla? " << (tabla.buscar(8) ? "Si" : "No") << std::endl;

    return 0;
}

