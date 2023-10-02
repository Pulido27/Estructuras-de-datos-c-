#include <iostream>
#include <list>
#include <functional>
#include <vector>

using namespace std;

template <typename T, typename R>
class TablaHash {
public:
    int TAMANO_TABLA;

    TablaHash(int size) {
        TAMANO_TABLA = size;
        tabla.resize(TAMANO_TABLA);
    }

private:
    vector<list<pair<T, R>>> tabla;

    size_t FuncionHash(T clave) {
        hash<T> hashFunc;
        return hashFunc(clave) % TAMANO_TABLA;
    }

public:
    void agregar(T llave, R valor) {
        size_t indice = FuncionHash(llave);
        tabla[indice].emplace_back(llave, valor); // Almacenar la clave junto con el valor
    }

    // Buscar un valor en la tabla por su clave
    bool buscar(T llave) {
        size_t indice = FuncionHash(llave);
        for (const auto& par : tabla[indice]) {
            if (par.first == llave) {
                cout << par.second;
                return true;
            }
        }
        return false;
    }
};

int main() {
	
	TablaHash<string,int> tabla(10);
	
	tabla.agregar("cinco",5);
	tabla.agregar("uni",1);	
	tabla.agregar("dos",2);
	
	tabla.buscar("cinco");
	tabla.buscar("tres");
	return 0;	
}
