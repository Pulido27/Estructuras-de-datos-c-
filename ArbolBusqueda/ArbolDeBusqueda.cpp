#include <iostream>

// Definición de la clase Nodo 
class Nodo {
public:
  int valor;
  Nodo* izquierdo;
  Nodo* derecho;

  Nodo(int valor) {       // el valor pasado como parametro es diferente al valor anteriormente escrito
    this->valor = valor;  // this es un puntero autoreferencial al mismo objeto que pertenece  
    izquierdo = derecho = nullptr;
  }
};

// Definición de la clase ArbolBinarioBusqueda
class ArbolBinarioBusqueda {
private:
  Nodo* raiz;

public:
  ArbolBinarioBusqueda() {
    raiz = nullptr;
  }

  // Función auxiliar para insertar un nodo en el árbol
  Nodo* insertarNodo(Nodo* nodo, int valor) {
    if (nodo == nullptr) {
      return new Nodo(valor);
    }

    if (valor < nodo->valor) {
      nodo->izquierdo = insertarNodo(nodo->izquierdo, valor);
    } else {
      nodo->derecho = insertarNodo(nodo->derecho, valor);
    }

    return nodo;
  }

  // Función para insertar un valor en el árbol
  void insertar(int valor) {
    raiz = insertarNodo(raiz, valor);
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

  return 0;
}
