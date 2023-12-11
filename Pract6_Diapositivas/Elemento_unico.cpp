#include <iostream>
#include <algorithm>
#include <unordered_map> // Utilizamos unordered_map para almacenar los valores únicos
//usa una tabla de has internamente
using namespace std;
//comentar lo de el doble hashmap
bool valor_unico(int arreglo[], int n) {
    unordered_map<int, int> frecuencias;

    for (int i = 0; i < n; i++) {
        if (frecuencias.count(arreglo[i]) == 1) {
            frecuencias[arreglo[i]]++;
        } else {
            frecuencias[arreglo[i]] = 1;
        }
    }
    // se puede optimizar con otro arreglo o con un hashmap extra
    // también modificando el array original;
    for (int i = 0; i < n; i++) {
        if (frecuencias[arreglo[i]] == 1) {
            return true;
        }
    }

    return false;
}

int main() {
    const int n = 10;
    int arreglo[n] = {1, 3, 3, 1};
    if (valor_unico(arreglo, n)) {
        cout << "El arreglo contiene valores únicos.\n";
    } else {
        cout << "El arreglo contiene elementos duplicados.\n";
    }

    return 0;
}
