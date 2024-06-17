#include <iostream>

using namespace std;

// Definicion de la clase nodo
class Nodo {
public:
    int valor;
    Nodo* izquierdo = nullptr;
    Nodo* derecho = nullptr;

    Nodo(int valor) {
        this->valor = valor; // Puntero autoreferenciado
    }
};

// Definicion de la clase ArbolBinarioBusqueda
class ArbolBinarioBusqueda {
private:
    Nodo* raiz = nullptr;    // Se inicializa el nodo raiz

public:
    ArbolBinarioBusqueda() {    // Se hace el constructor 
    }
    
    // Este es el metodo insertar
    void insertar(int valor) {
        
        // Se revisa que la raiz no sea nula
        if (raiz == nullptr) {
            raiz = new Nodo(valor);
            return;
        }

        // Se declara el Nodo actual en la raiz para poder navegar entre nodos
        Nodo* nodoActual = raiz;
        
        
        //se inicia el ciclo para recorre el arbol
        // Comienza el ciclo while en true para que se ejecute hasta que el if entre al return
        while (true) {
            /*
            Se declara una referencia a un puntero tipo nodo(Nodo*&)            
            
            Para no solo apuntar a la misma direccion del otro puntero si no 
            para literalmente convertirse en el otro puntero

            Esto se hace para a la hora de agregarle un valor a ese puntero y no solo se cambie el del puntero copia si no
            que se cambia el valor del puntero del nodo del arbol
            
            La referencia de puntero se le asigna uno de los hijos del nodoActual a traves del op ternario
             
            La referencia a puntero se declara en el ciclo para que es te resetie su direccion 
            y no solo se sobreescriba el valor 
            */
            Nodo*& siguienteNodo = (valor < nodoActual->valor) ? nodoActual->izquierdo : nodoActual->derecho;
            
            //Se valida si el nodo esta disponible para poder colocar el valor nuevo ahi
            if (siguienteNodo == nullptr) {
                siguienteNodo = new Nodo(valor);
                return;
            }
            
            // En el caso de que el siguiente nodo no este disponible se convierte en el nodo actual para repetir el proceso 
            nodoActual = siguienteNodo;
        }
    }


    bool buscar(int valor) {
        if (raiz == nullptr) {
            return false;
        }

        Nodo* nodoActual = raiz;
        
        while (true) {
            if (nodoActual->valor == valor) {
                return true;
            }
            Nodo*& siguienteNodo = (valor < nodoActual->valor) ? nodoActual->izquierdo : nodoActual->derecho;
            if (siguienteNodo == nullptr) {
                return false;
            }
            nodoActual = siguienteNodo;
        }
    }
    
    void remove(int value) {
        
    }
};

// Ejemplo de uso
int main() {
    ArbolBinarioBusqueda arbol;
    arbol.insertar(8);
    arbol.insertar(3);
    arbol.insertar(10);
    arbol.insertar(1);
    arbol.insertar(6);
    arbol.insertar(14);
    arbol.insertar(4);
    arbol.insertar(7);
    arbol.insertar(13);

    cout << arbol.buscar(8);
    cout << arbol.buscar(3);
    cout << arbol.buscar(10);
    cout << arbol.buscar(1);
    cout << arbol.buscar(6);
    cout << arbol.buscar(14);
    cout << arbol.buscar(4);
    cout << arbol.buscar(7);
    cout << arbol.buscar(13);
    cout << arbol.buscar(25);

    return 0;
}

