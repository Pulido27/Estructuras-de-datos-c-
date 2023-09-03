#include <iostream>
#include <forward_list>
#include <unordered_set>

using namespace std;

void borrar_duplicados(forward_list<int> &lista) {
    unordered_set<int> frecuencias;
    auto iterador1 = lista.begin();
    auto iterador2 = lista.begin();
    frecuencias.insert(*iterador1);
    iterador1++;
    while (iterador1 != lista.end()) {
        if (frecuencias.find(*iterador1) != frecuencias.end()) {
            iterador1++;
            lista.erase_after(iterador2);
        } else {
            frecuencias.insert(*iterador1);
            iterador1++;
            iterador2++;
        }
    }
}

int main() {
    forward_list<int> lista;
    lista.push_front(1);
    lista.push_front(1);
    lista.push_front(2);
    lista.push_front(3);
    lista.push_front(4);
    lista.push_front(5);
    lista.push_front(5);
    lista.push_front(5);
    lista.push_front(6);
    lista.push_front(7);
    
    // Mostrar la lista
    for (const auto& item : lista) {
        cout << item << " -> ";
    }
    cout << "nullptr" << std::endl;

    borrar_duplicados(lista);
    
    // Mostrar la lista sin duplicados
    for (const auto& item : lista) {
        cout << item << " -> ";
    }
    cout << "nullptr" << std::endl;
    
    return 0;
}
