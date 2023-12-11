#include <iostream>
#include <list>
#include <functional>
#include <vector>

using namespace std;

template <typename T, typename R>        // t y r dos atributos dinamicos
class HashMap {
public:
    int capacity;

    HashMap(int size = 100) {
        capacity = size;
        table.resize(capacity);            // Redimenciona el vector
    }

private:
    vector<list<pair<T, R>>> table;            // Se guardan los datos en un vector de pares

    size_t FuncionHash(T key) {
        hash<T> hashFunc;
        return hashFunc(key) % capacity;
    }

public:
    
    void push(pair<T, R> d) {                    // Push agrega un pair ya crado y emplace crea un pair nuevo 
        size_t index = FuncionHash(d.first);
        for (auto& pair : table[index]) {        
            if (pair.first == d.first) {                
                pair.second = d.second;
                break;
            }
        }
        table[index].push_back(d);
    }

    void emplace(T key, R value) {
        size_t index = FuncionHash(key);
        for (auto& pair : table[index]) {        // Se accede al pair dentro de la posicion dada en el vector 
            if (pair.first == key) {                // Se evalua para el caso de que la llave ya existe y sobreescribe
                pair.second = value;
                break;
            }
        }
        table[index].emplace_back(key, value); // Almacenar la clave junto con el valor
    }

    // Buscar un valor en la tabla por su clave y regresa el valor si  es que existe
    R search(T key) {
        R absent;
        size_t index = FuncionHash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return absent;
    }
    
    // regresa si la llave ya fue registrada en la tabla de hash o no 
    int count(T key) {
        R absent;
        size_t index = FuncionHash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return 1;
            }
        }
        return 0;
    }
};

int main() {
    
    HashMap<string, int> tabla(10);
    
    tabla.emplace("cinco", 5);
    tabla.emplace("cinco", 6);
    tabla.emplace("uno", 1);    
    tabla.emplace("dos", 2);
    
    tabla.search("cinco");
    tabla.search("tres");
    cout << tabla.count("uno") << endl;
    cout << tabla.count("k") << endl;
    return 0;    
}

