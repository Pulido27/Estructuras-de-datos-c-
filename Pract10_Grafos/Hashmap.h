#pragma once
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
    
    R& operator[](T key) {  //const T& key
        size_t index = FuncionHash(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        table[index].emplace_back(key, R{}); // Crear una nueva entrada si la clave no existe
        return table[index].back().second;
    }
    
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

    // Buscar un valor en la tabla por su clave y regresa el valor si es que existe
    R& search(T key) {
        size_t index = FuncionHash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return R{};
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

    vector<pair<T, R>> list() {
        vector<pair<T, R>> storage;
        for (const auto& list2 : table) {
            for (const auto pair : list2) {
                storage.push_back(pair);
            }
        }
        return storage;
    }
};

