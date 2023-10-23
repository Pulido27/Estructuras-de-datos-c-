#include <iostream>
#include <unordered_set>
#include <functional>

using namespace std;

struct llaves {
    int a;
    int b;
    int c;

    llaves(int a, int b, int c) :
        a(a), b(b), c(c) {}
};

class bloomfilter {
public:
    unordered_set<bool> almacen; // 
    int tabla_size; // Agregado para calcular las llaves

    bloomfilter(int size) : tabla_size(size) {}

    llaves calcula_llaves(string txt) {
        char sal = '1'; // Cambiado a comillas simples
        int llave1 = hash<string>{}(txt + sal) % tabla_size;
        int llave2 = llave1;
        int llave3 = 0;

        while (llave1 == llave2) {
            sal++;
            llave2 = hash<string>{}(txt + sal) % tabla_size;
        }

        llave3 = llave2;
        while (llave1 == llave3 || llave2 == llave3) {
            sal++;
            llave3 = hash<string>{}(txt + sal) % tabla_size;
        }

        return { llave1, llave2, llave3 };
    }

    void insert(string a) {
        llaves llaves = calcula_llaves(a);
        almacen.insert(llaves.a);
        almacen.insert(llaves.b);
        almacen.insert(llaves.c);
    }

    void agregar(string a) {
        insert(a);
    }

    bool buscar(string a) {
        llaves llaves = calcula_llaves(a);
        return almacen.count(llaves.a) && almacen.count(llaves.b) && almacen.count(llaves.c);
    }
};

int main() {
    bloomfilter filtro(100); // Proporciona el tamaño de la tabla
    filtro.agregar("ejemplo1");
    filtro.agregar("ejemplo2");

    if (filtro.buscar("ejemplo1")) {
        cout << "ejemplo1 está en el filtro." << endl;
    } else {
        cout << "ejemplo1 no está en el filtro." << endl;
    }

    if (filtro.buscar("ejemplo3")) {
        cout << "ejemplo3 está en el filtro." << endl;
    } else {
        cout << "ejemplo3 no está en el filtro." << endl;
    }

    return 0;
}

