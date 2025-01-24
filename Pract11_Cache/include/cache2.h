#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <optional>
#include <math.h>

using namespace std;

template <typename T>
struct dato {
    int id;
    T val;
    time_t epoc = time(nullptr);
};

template <typename T>
class CacheMemory {
public:
    int capacity;
    dato<T>* storage;
    int count;
    unordered_map<int, int> address;

public:
    CacheMemory(int n = 5) {
        capacity = pow(2, n) - 1;
        storage = new dato<T>[capacity];
        count = 0;
    }

    ~CacheMemory() {
        delete[] storage;
    }

    int Parent(int index) {
        return (index - 1) / 2;
    }

    int leftChild(int index) {
        return (index * 2) + 1;
    }

    int rightChild(int index) {
        return (index * 2) + 2;
    }

    void push(dato<T> value) {
        int index;

        if (address.count(value.id) == 1) {
            index = address[value.id];
            storage[index].epoc = time(nullptr);
        } else if (count == capacity) {
            address.erase(storage[0].id);
            index = 0;
            storage[0] = value;
            address[value.id] = 0;
        } else {
            storage[count] = value;
            address[value.id] = count;
            count++;
            return;
        }

        while (leftChild(index) < count) {
            int inLeft = leftChild(index);
            int inRight = rightChild(index);

            if (inRight >= count) {
                address[storage[index].id] = inLeft;
                address[storage[inLeft].id] = index;
                swap(storage[index], storage[inLeft]);
                return;
            }

            if (storage[inLeft].epoc < storage[inRight].epoc) {
                address[storage[index].id] = inLeft;
                address[storage[inLeft].id] = index;
                swap(storage[index], storage[inLeft]);
                index = inLeft;
            } else {
                address[storage[index].id] = inRight;
                address[storage[inRight].id] = index;
                swap(storage[index], storage[inRight]);
                index = inRight;
            }
        }
    }

    optional<dato<T>> get(int id) {
        if (address.count(id) == 1) {
            int index = address[id];
            return storage[index];
        } else {
            return nullopt;
        }
    }
};