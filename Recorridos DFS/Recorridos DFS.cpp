#include <iostream>
#include <math.h>

using namespace std;

// Definición de la clase ArbolBinarioBusqueda con arrays
class ArbolBinarioBusqueda2 {
private:
    int capacidad;
    int* arbol;
    bool* vacio;
    
    void _posOrder(int indice) {
    	
    	if (inHijoIzq(indice) <= capacidad) {
			if (vacio[ inHijoIzq(indice) ] == false) {
				_posOrder( inHijoIzq(indice) );
			}		
		}
    	
		if (inHijoDer(indice) <= capacidad) {
			if (vacio[ inHijoDer(indice) ] == false) {
				_posOrder( inHijoDer(indice) );
			}		
		}
		
		cout << arbol[indice] << " ";
	}
	
	void _inOrder(int indice) {
    	
    	if (inHijoIzq(indice) <= capacidad) {
			if (vacio[ inHijoIzq(indice) ] == false) {
				_inOrder( inHijoIzq(indice) );
			}		
		}
		
		cout << arbol[indice] << " ";
    	
		if (inHijoDer(indice) <= capacidad) {
			if (vacio[ inHijoDer(indice) ] == false) {
				_inOrder( inHijoDer(indice) );
			}		
		}	
	}
	
	void _preOrder(int indice) {
		
		cout << arbol[indice] << " ";
    	
    	if (inHijoIzq(indice) <= capacidad) {
			if (vacio[ inHijoIzq(indice) ] == false) {
				_preOrder( inHijoIzq(indice) );
			}		
		}
		
		if (inHijoDer(indice) <= capacidad) {
			if (vacio[ inHijoDer(indice) ] == false) {
				_preOrder( inHijoDer(indice) );
			}		
		}	
	}

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

            if (siguienteIndice >= capacidad) {
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
            if (arbol[indice] == valor) {
                return true;
            }

            int siguienteIndice = (valor < arbol[indice]) ? inHijoIzq(indice) : inHijoDer(indice);

            if (siguienteIndice >= capacidad) {
                return false;
            }
            if (vacio[siguienteIndice] == true) {
                return false;
            }
            indice = siguienteIndice;
        }
    }
    
    void posOrder(){
    	 _posOrder(0);
    	 cout << endl;
	}
	
	void inOrder(){
		_inOrder(0);
		cout<< endl;
	}

	void preOrder(){
		_preOrder(0);
		cout<< endl;
	}

};

// Ejemplo de uso
int main() {
    ArbolBinarioBusqueda2 arbol(4);
    arbol.insertar(5);
    arbol.insertar(2);
    arbol.insertar(8);
    arbol.insertar(1);
    arbol.insertar(3);
    arbol.insertar(7);
    arbol.insertar(9);
    
    arbol.posOrder();
    arbol.inOrder();
    arbol.preOrder();
    return 0;
}
