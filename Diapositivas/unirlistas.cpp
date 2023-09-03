#include <iostream>
#include <forward_list>
#include <vector>

using namespace std;

/*
void unir(forward_list<int> &lista1, forward_list<int> &lista2) {
    auto it1 = lista2.begin();

    if (lista1.front() < *it1) {
        lista2.push_front(lista1.front());
        lista1.pop_front();
    } else {
        it1++;
    }

    auto it2 = lista2.begin();
    auto it3 = lista1.begin();
    while (it3 != lista1.end()) {
        if (*it3 > *it1) {
            it1++;
            it2++;
        } else {
            lista2.insert_after(it2, *it3);
            it2++;
            it3++;
        }
    }
}
*/

forward_list<int> unir(forward_list<int> &lista1, forward_list<int> &lista2) {
    forward_list<int> result;
    auto it1 = lista1.begin();
    auto it2 = lista2.begin();

    while (it1 != lista1.end() && it2 != lista2.end()) {
        if (*it1 <= *it2) {
            result.push_front(*it1);
            ++it1;
        } else {
            result.push_front(*it2);
            ++it2;
        }
    }

    while (it1 != lista1.end()) {
        result.push_front(*it1);
        ++it1;
    }

    while (it2 != lista2.end()) {
        result.push_front(*it2);
        ++it2;
    }

    result.reverse();
    return result;
}

void unirN(vector<forward_list<int> *> &vectorDeListas) {
    int distancia = 1;
    int count = 1;
    while (count != 0) {
        count = 0;
        int i = 0;
        while ((i + distancia) < vectorDeListas.size()) {
            *vectorDeListas[i] = unir(*vectorDeListas[i + distancia], *vectorDeListas[i]);
            i += distancia * 2;
            count++;
        }
        distancia *= 2;
    }

    for (int num : *vectorDeListas[0]) {
        cout << num << " -> ";
    }
    cout << "nullptr" << std::endl;
}

int main() {
    forward_list<int> lista;
    lista.push_front(9);
    lista.push_front(7);
    lista.push_front(5);
    lista.push_front(3);
    lista.push_front(2);

    for (const auto &item : lista) {
        cout << item << " -> ";
    }
    cout << "nullptr" << std::endl;

    forward_list<int> lista2;
    lista2.push_front(10);
    lista2.push_front(8);
    lista2.push_front(6);
    lista2.push_front(4);
    lista2.push_front(1);

    for (const auto &item : lista2) {
        cout << item << " -> ";
    }
    cout << "nullptr" << std::endl;

    forward_list<int> lista3;
    lista3 = unir(lista, lista2);

    for (const auto &item : lista3) {
        cout << item << " -> ";
    }
    cout << "nullptr" << std::endl;

    // ejercicio de n listas

    forward_list<int> list1 = {1, 2, 7};
    forward_list<int> list2 = {3, 5, 6, 8};
    forward_list<int> list3 = {22, 34, 45};
    forward_list<int> list4 = {15, 33, 55};
    forward_list<int> list5 = {11, 12, 13};
    forward_list<int> list6 = {9, 10};

    // Crear un vector de punteros a forward_list
    vector<forward_list<int> *> vectorDeListas;

    // Asignar los punteros a las listas al vector
    vectorDeListas.push_back(&list1);
    vectorDeListas.push_back(&list2);
    vectorDeListas.push_back(&list3);
    vectorDeListas.push_back(&list4);
    vectorDeListas.push_back(&list5);
    vectorDeListas.push_back(&list6);

    unirN(vectorDeListas);

    return 0;
}
