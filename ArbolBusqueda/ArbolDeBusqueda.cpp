#include <iostream>

using namespace std;

// Definición de la clase Nodo 
class Nodo {
public:
  int valor;
  Nodo* izquierdo = nullptr;
  Nodo* derecho = nullptr;

  Nodo(int valor) {       // el valor pasado como parametro es diferente al valor anteriormente escrito
    this->valor = valor;  // this es un puntero autoreferencial al mismo objeto que pertenece   
  }
};

// Definición de la clase ArbolBinarioBusqueda
class ArbolBinarioBusqueda {
private:
  Nodo* raiz = nullptr;

public:
  ArbolBinarioBusqueda() {
    	
  }

void insertar(int valor) {
  if (raiz == nullptr) {
    raiz = new Nodo(valor);
    return;
  }

  Nodo* nodoActual = raiz;
  while (true) {
    Nodo*& siguienteNodo = (valor < nodoActual->valor) ? nodoActual->izquierdo : nodoActual->derecho;
    if (siguienteNodo == nullptr) {
      siguienteNodo = new Nodo(valor);
      return;
    }
    nodoActual = siguienteNodo;
  }
}

bool buscar(int valor){
	if (raiz == nullptr) {
    return false; 
  }
  
  

  Nodo* nodoActual = raiz;
  while (true) {
  	if(nodoActual->valor==valor){
	  return true;  		
	  }
    Nodo*& siguienteNodo = (valor < nodoActual->valor) ? nodoActual->izquierdo : nodoActual->derecho;
    if (siguienteNodo == nullptr) {
      return false;
    }
    nodoActual = siguienteNodo;
  }	
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
  
  cout<< arbol.buscar(8);
  cout<< arbol.buscar(3);
  cout<< arbol.buscar(10);
  cout<< arbol.buscar(1);
  cout<< arbol.buscar(6);
  cout<< arbol.buscar(14);
  cout<< arbol.buscar(4);
  cout<< arbol.buscar(7);
  cout<< arbol.buscar(13);
  cout<< arbol.buscar(25);	


  return 0;
}
