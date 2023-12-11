#include <iostream>
#include <set>
#include <unordered_map>

using namespace std;

class Medidas_T_C {
private:
    long long suma;
    long double promedio;
    double mediana;
    pair<int, int> moda;
    unordered_map<int, int> frecuencia_map;
    multiset<int> numeros;

public:
    Medidas_T_C() : suma(0), promedio(0), mediana(0) {}

    void agregar(int num) {
        numeros.insert(num);
        suma += num;

        // actualizacion de la moda;
        frecuencia_map[num]++;
    }

    long double Promedio() {
        return static_cast<long double>(suma) / numeros.size();
    }

    int Mediana() {
        int n = numeros.size();
        auto iterador = numeros.begin();
        advance(iterador, (n - 1) / 2);
        mediana = *iterador;
        return mediana;
    }

    int Moda() {
        for (const auto& temp : frecuencia_map) {
            if (moda.second < temp.second) {
                moda = temp;
            }
        }
        return moda.first;
    }
};

int main() {

    Medidas_T_C procesador;

    procesador.agregar(8);
    procesador.agregar(2);
    procesador.agregar(3);
    procesador.agregar(2);
    procesador.agregar(7);
    procesador.agregar(7);

    cout << procesador.Promedio() << endl;
    cout << procesador.Mediana() << endl;
    cout << procesador.Moda() << endl;

    return 0;
}