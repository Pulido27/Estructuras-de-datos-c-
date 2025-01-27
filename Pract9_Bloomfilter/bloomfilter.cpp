#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include "bitset.h"

using namespace std;

class bloomfilter {
public:
    Bitset data; 
    int num_keys; 
    int tabla_size; // Agregado para calcular las llaves

    bloomfilter(int size, int keys) {
        data.resize(size);
        num_keys = keys;
        tabla_size = size;
    }

    vector<int> calculate_keys(string txt) {
        vector<int> keys;
        hash<string> hasher;
        int key = 0;
        string sal = "0";
        int nsal = 0;

        for(int i = 0; i < num_keys; i++) {
            key = hasher(txt + sal) % tabla_size;

            for(int j = 0; j < keys.size(); j++) {
                while(keys[j] == key) {
                    nsal++;
                    sal = to_string(nsal);
                    key = hasher(txt + sal) % tabla_size;
                    j=0;
                }
            }
            keys.push_back(key);
        }

        return keys;
    }

int encontrar_valor(const std::vector<int>& v, int valor) {
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] == valor) {
            return i;
        }
    }
    return -1; // Valor no encontrado
}

    void insert(string a) {
        vector<int>keys = calculate_keys(a);

        for(int i=0; i<1000; i++){
            int x = encontrar_valor(keys,i);
            if(x==-1){
                cout<<"fallo";
            }
        }

        for(int k : keys) {
            data.set(k);
        }
    }

    void agregar(string a) {
        insert(a);
    }

    bool buscar(string a) {
        vector<int>keys = calculate_keys(a);

        for(int k : keys) {
            if(!data.test(k)) {
                return false;
            }
        }

        return true;
    }
};


int main() {

    bloomfilter bloom1(1000,1000);

    bloom1.agregar("pulido");


    bloom1.agregar("cristian");

    bloom1.agregar("daniel");

    bloom1.agregar("carrillo");
    bloom1.agregar("scar");
    bloom1.agregar("as");


    cout << bloom1.buscar("pulido");
    cout << bloom1.buscar("cristian");
    cout << bloom1.buscar("daniel");
    cout << bloom1.buscar("carrillo");
    cout << bloom1.buscar("scar");
    cout << bloom1.buscar("as");
    cout << bloom1.buscar("pulidu");
    cout << bloom1.buscar("pu");

    return 0;
}
