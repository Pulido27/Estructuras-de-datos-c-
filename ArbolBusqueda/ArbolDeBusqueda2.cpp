#include <iostream>
#include <math.h>


// Definición de la clase ArbolBinarioBusqueda con arrays
class ArbolBinarioBusqueda2 {
private:
   int capacidad;
   int* arbol;

public:
  ArbolBinarioBusqueda2(int n) {
    	capacidad = (pow(n, 2))-1;
		arbol = new int[capacidad];
		for(int i =0; i<capacidad; i++){
			arbol[i]=-1;
		}		 
  }
  
void insertar(int valor){
  	if (arbol[0] == -1) {
    arbol[0] = valor;
    return;
  }
  
  int indice = 0;
  while (true) {
    int siguienteIndice = (valor < arbol[indice]) ? ((2*indice)+1) : ((2*indice)+2);
    if (arbol[siguienteIndice] == -1) {
      arbol[siguienteIndice] = valor;
      return;
    }
    indice = siguienteIndice;
  }
  }
  
  


};
// Ejemplo de uso
int main() {
  ArbolBinarioBusqueda2 arbol(4);
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
