#include <iostream>
#include <list>
#include <functional>

using namespace std;

const int TAMANO_TABLA = 10;

class TablaHash {
private:
    list<int> tabla[TAMANO_TABLA];

    // Función de hash que utiliza std::hash
    //el tipo de dato size es un numero positivo que se adapta a la maquina 
    //normalmente usado para direccion de memoria o indices
	size_t FuncionHash(int clave) {
        hash<int> hashFunc;              // se crea un objeto tipo has recibe datos y devuelve el has
        return hashFunc(clave) % TAMANO_TABLA; // modulo para asegurar que el indice sea valido
    }

public:
    // Método para agregar un valor a la tabla de hash
    void agregar(int valor) {
        size_t indice = FuncionHash(valor);
        tabla[indice].push_back(valor); // push back porque trabajamos con listas enlazadas
    }

    // Método para buscar un valor en la tabla de hash
    bool buscar(int valor) {
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
    TablaHash tabla;

    // Agregar algunos valores a la tabla
    tabla.agregar(5);
    tabla.agregar(10);
    tabla.agregar(15);

    // Buscar valores en la tabla
    //uso de operador ternario en cout
    cout << "¿5 se encuentra en la tabla? " << (tabla.buscar(5) ? "Sí" : "No") << std::endl;
    cout << "¿8 se encuentra en la tabla? " << (tabla.buscar(8) ? "Sí" : "No") << std::endl;

    return 0;
}

