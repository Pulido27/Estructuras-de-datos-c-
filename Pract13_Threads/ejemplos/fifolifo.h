#pragma once

#include <iostream>
#include <atomic>
#include <optional>
using namespace std;

// Clase que combina una estructura fifo y lifo en un buffer circular
template<class T>
class Fifolifo {
private:
    T* data = nullptr;     // apunta al arreglo dinamico que se crea
    int max_size;            // le da el tamaño al arreglo dinamico
    atomic<int> front;               // apunta al inicio del buffer circular
    atomic<int> rear;                // apunta al final del buffer circular
    atomic<int> count;               // lleva el tamaño de la cola

public:
    Fifolifo(int size = 5) {        // se le agrega un tamaño por defecto
        max_size = size;
        data = new T[max_size];
        front = max_size - 1; //front apunta a la ultima posicion del array para el caso de que no se use push
        rear = 0;        // rear apunta a la primera posicion del arreglo para el caso de que no se use append
        count = 0;
    }

    ~Fifolifo() {
        delete[] data;            // se elimina la memoria dinamica
    }

    bool push(T value) {
        if (count >= max_size) {
            return false;
        }

        int temp;
        int temp2;
        temp = front.load();
        do{
            temp2 = (temp + 1) % max_size;
        }while(!front.compare_exchange_strong(temp,temp2,memory_order_acq_rel));

        data[temp2] = value;
        count++;
        return true;
    }

    optional<T> pop() {
        if (count <= 0) {
            return {};
        }
        
        int temp_count = count.load();
        int temp_count2;
        do{
            temp_count2 = (temp_count - 1);
        }while(!count.compare_exchange_strong(temp_count,temp_count2,memory_order_acq_rel));

        if (count < 0) {
            count = 0;
            return {};
        }

        int temp;
        int temp2;

        temp = rear.load();
        do{
            temp2 = (temp + 1) % max_size;
        }while(!rear.compare_exchange_strong(temp,temp2,memory_order_acq_rel));

        return data[temp];
    }

    int size() {
        return count;
    }
};