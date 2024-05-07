#pragma once

#include <iostream>
#include <atomic>
#include <optional>
#include <assert.h>
using namespace std;

// Clase que combina una estructura fifo y lifo en un buffer circular
template<class T>
class fifo {
private:
    T* data = nullptr;     // apunta al arreglo dinamico que se crea
    uint16_t max_size;     // tama;o del arreglodinamico + 1
    struct cursor {
        uint16_t     front;               // apunta al inicio del buffer circular
        uint16_t     rear;                // apunta al final del buffer circular
        uint16_t     size;
        uint16_t     padding = 0;
    };
    atomic<cursor> idx;                   // contiene los punteros del fifo

public:
    fifo(int size = 5) {        // se le agrega un tamaño por defecto
        max_size = size+1;
        data = new T[max_size];
        idx.store({0,0});
    }

    ~fifo() {
        delete[] data;            // se elimina la memoria dinamica
    }

    bool push(T value) {
        cursor temp;
        cursor temp2;
        temp = idx.load();
        
        do{
            if(temp.front == (temp.rear + 1) % max_size) {
                assert(temp.size == max_size - 1);
                return false; //lleno
            }
            uint16_t r = (temp.rear + 1)%max_size;
            uint16_t s = temp.size + 1;
            temp2 = {
                temp.front,
                r,
                s,
                0
                };
        }while(!idx.compare_exchange_strong(temp, temp2, memory_order_acq_rel));

        data[temp.rear] = value;
        return true;
    }

    optional<T> pop() {
        cursor temp;
        cursor temp2;

        temp = idx.load();
        do{
            if(temp.front == temp.rear) {
                assert(temp.size == 0);
                return {};
            }
            uint16_t f = (temp.front + 1) % max_size;
            uint16_t s = temp.size - 1;
            temp2 = {
                f,
                temp.rear,
                s,
                0
                };
        }while(!idx.compare_exchange_strong(temp,temp2,memory_order_acq_rel));

        return data[temp.front];
    }

    size_t size() {
        return idx.load().size;
    }
};