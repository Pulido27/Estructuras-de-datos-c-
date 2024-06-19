#include <iostream>
#include <list>

using namespace std;
//12345
// Clase que combina una estructura fifo y lifo en un buffer circular

class Fifolifo {
private:
    int* data = nullptr;     // apunta al arreglo dinámico que se crea
    int max_size;            // le da el tamaño al arreglo dinámico
    int front;               // apunta al inicio del buffer circular
    int rear;                // apunta al final del buffer circular
    int count;               // lleva el tamaño de la cola

public:
    Fifolifo(int size = 5) {        // se le agrega un tamaño por defecto
        max_size = size;
        data = new int[max_size];
        front = max_size - 1;            // front apunta a la última posición del arreglo para el caso de que no se use push
        rear = 0;                        // rear apunta a la primera posición del arreglo para el caso de que no se use append
        count = 0;
    }

    ~Fifolifo() {
        delete[] data;            // se elimina la memoria dinámica
    }

    void push(int value) {
        if (count == max_size) {
            cout << "Error: La lista está llena." << endl;
            return;
        }

        front = (front + 1) % max_size;            // se usa % para que si front = max_size se regrese a la posición 0;
        data[front] = value;
        count++;
    }

    void append(int value) {
        if (count == max_size) {
            cout << "Error: La lista está llena." << endl;
            return;
        }

        rear = (rear - 1 + max_size) % max_size;    // se usa % para que si rear = 0 se regrese a la posición max_size - 1;
        data[rear] = value;
        count++;
    }

    int pop_front() {
        if (count == 0) {
            cout << "Error: La lista está vacía." << endl;
            return -1;
        }

        int value = data[front];
        front = (front - 1 + max_size) % max_size;
        count--;
        return value;
    }

    int pop_back() {
        if (count == 0) {
            cout << "Error: La lista está vacía." << endl;
            return -1;
        }

        int value = data[rear];
        rear = (rear + 1) % max_size;
        count--;
        return value;
    }

    int size() {
        return count;
    }
};

int main() {

    Fifolifo list1(5);

    // Llenar el objeto con números
    list1.append(1);
    list1.append(2);
    list1.append(3);
    list1.append(4);
    list1.append(5);

    // Invertirlos
    Fifolifo list2;

    while (list1.size() > 0) {
        list2.push(list1.pop_front());
    }

    // Ordenar la lista
    while (list2.size() > 0) {
        int min = list2.pop_front();
        int size = list2.size();

        for (int i = 0; i < size; i++) {
            int num = list2.pop_front();
            if (num < min) {
                list1.append(min);
                min = num;
            } else {
                list1.append(num);
            }
        }

        list1.append(min);
    }

    // Imprimir los elementos de la lista
    while (list1.size() > 0) {
        cout << list1.pop_front() << " ";
    }
    cout << endl;

    // Usando la biblioteca estándar (std::list)

    // Guardar una lista de 10 números
    list<int> numbers;
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);
    numbers.push_back(4);
    numbers.push_back(5);
    numbers.push_back(6);
    numbers.push_back(7);
    numbers.push_back(8);
    numbers.push_back(9);
    numbers.push_back(10);

    // Invertir la lista
    numbers.reverse();

    // Ordenar la lista
    numbers.sort();

    // Imprimir los elementos de la lista
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

