#include <iostream>
#include <unordered_map> // Utilizamos unordered_map para almacenar los valores únicos
//usa una tabla de has internamente
using namespace std;

// Funcion para buscar al menos un elemento unico
bool unique_value(int arr[], int n) {
    unordered_map<int, bool> frec;

    for (int i = 0; i < n; i++) {         // se recorre al array se registran los duplicados
        if (frec.count(arr[i]) == 1) {
            frec[arr[i]] = false;

        } else {
            frec[arr[i]] = true;
        }
    }                                   //se recorre el map para ver si hay unicos
    for (int i = 0; i < n; i++) {
        if (frec[arr[i]] == true) {
            return true;
        }
    }

    return false;
}

int main() {
    const int n = 4;
    int arr[n] = {1, 3, 3, 1};
    if (unique_value(arr, n)) {
        cout << "El arr contiene valores únicos.\n";
    } else {
        cout << "El arr contiene elementos duplicados.\n";
    }

    return 0;



}
