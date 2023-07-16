#include <iostream>
#include <math.h>

using namespace std;


// Definición de la clase ArbolBinarioBusqueda con arrays
class ArbolBinarioBusqueda2 {
private:
	int capacidad;
	int* arbol;
	bool* vacio;

public:
	ArbolBinarioBusqueda2(int n) {
		capacidad = pow(2, n) - 1;
		arbol = new int[capacidad];
		vacio = new bool[capacidad];
		for (int i = 0; i < capacidad; i++) {
			vacio[i] = true;
		}
	}

	~ArbolBinarioBusqueda2() {
		delete[] arbol;
		delete[] vacio;
	}

	int inPadre(int indice) {
		return (indice - 1) / 2;
	}

	int inHijoIzq(int indice) {
		return (2 * indice) + 1;
	}

	int inHijoDer(int indice) {
		return (2 * indice) + 2;
	}
	

	void insertar(int valor) {
		if (vacio[0] == true) {
			arbol[0] = valor;
			vacio[0] = false;
			return;
		}

		int indice = 0;
		while (true) {
			int siguienteIndice = (valor < arbol[indice]) ? inHijoIzq(indice) : inHijoDer(indice);
			
			if(siguienteIndice>=capacidad){
				cout << "Indice invalido";
				return;
			}
			
			if (vacio[siguienteIndice] == true) {
				arbol[siguienteIndice] = valor;
				vacio[siguienteIndice] = false;
				return;
			}
			indice = siguienteIndice;
		}
	}
	
	bool buscar(int valor) {
		if (vacio[0] == true) {
			return false;
		}

		int indice = 0;
		
		while (true) {
			if(arbol[indice] == valor){
				return true;  		
			}
			
			int siguienteIndice = (valor < arbol[indice]) ? inHijoIzq(indice) : inHijoDer(indice);
			
			if(siguienteIndice>=capacidad){
				return false;	
			}
			if (vacio[siguienteIndice] == true) {
				return false;
			}
			indice = siguienteIndice;
		}
	}
		
};

// Ejemplo de uso
int main() {
	ArbolBinarioBusqueda2 arbol(4);
	arbol.insertar(1);
	arbol.insertar(2);
	arbol.insertar(3);
	arbol.insertar(4);
	arbol.insertar(5);
	arbol.insertar(6);
	arbol.insertar(7);
	arbol.insertar(8);
	arbol.insertar(9);

	cout << arbol.buscar(1);
	cout << arbol.buscar(2);
	cout << arbol.buscar(3);
	cout << arbol.buscar(4);
	cout << arbol.buscar(5);
	cout << arbol.buscar(6);
	cout << arbol.buscar(7);
	cout << arbol.buscar(8);
	cout << arbol.buscar(9);
	
	
	
/*	arbol.insertar(8);
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
*/





	return 0;
}
