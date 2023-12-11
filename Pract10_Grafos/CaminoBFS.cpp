#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

// Definición de direcciones posibles (arriba, abajo, izquierda, derecha)
const vector<pair<int, int>> direcciones = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// Función para verificar si una celda está dentro de la cuadrícula y es un camino libre (0)
 bool esCaminoLibre(const vector<vector<int>>& cuadricula, int fila, int columna) {
    int filas = cuadricula.size();
    
	int columnas = cuadricula[0].size();
    
	return (fila >= 0 && fila < filas && columna >= 0 && columna < columnas && cuadricula[fila][columna] == 0);
}

// Función para encontrar el camino más corto entre dos puntos en la cuadrícula
vector<tuple<int, int>> encontrarCaminoMasCorto(const vector<vector<int>>& cuadricula, tuple<int, int> inicio, tuple<int, int> final) {
    int filas = cuadricula.size();
    int columnas = cuadricula[0].size();

    vector<vector<int>> distancias(filas, vector<int>(columnas, -1)); // Inicializar todas las distancias como -1
    vector<vector<tuple<int, int>> > camino(filas, vector<tuple<int, int>>(columnas)); // Rastrear el camino

    queue<tuple<int, int>> cola;
    cola.push(inicio);
    distancias[get<0>(inicio)][get<1>(inicio)] = 0;
	int flag = 0;
    while (!cola.empty()) {
        tuple<int, int> actual = cola.front();
        cola.pop();
		
		if(actual == final) {
			cout<< "final : "<<endl;
			break;
		}
	
        for (const auto& direccion : direcciones) {
            int nuevaFila = get<0>(actual) + direccion.first;
            int nuevaColumna = get<1>(actual) + direccion.second;

            if (esCaminoLibre(cuadricula, nuevaFila, nuevaColumna) && distancias[nuevaFila][nuevaColumna] == -1) {
                cola.push(make_tuple(nuevaFila, nuevaColumna));
                
				distancias[nuevaFila][nuevaColumna] = distancias[get<0>(actual)][get<1>(actual)] + 1;
                
				camino[nuevaFila][nuevaColumna] = actual;
            }
        }
    }

    // Reconstruir el camino desde el punto final hasta el punto inicial
    vector<tuple<int, int>> resultado;
    
	tuple<int, int> puntoActual = final;
    
	while (puntoActual != inicio) {
        resultado.push_back(puntoActual);
        puntoActual = camino[get<0>(puntoActual)][get<1>(puntoActual)];
    }
    
    resultado.push_back(inicio);
    reverse(resultado.begin(), resultado.end());
	//cout << "final : " << flag <<endl;
    return resultado;
}

int main() {
    vector<vector<int>> cuadricula = {
        {1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0}
    };

    tuple<int, int> inicio = make_tuple(5, 0);
    tuple<int, int> final = make_tuple(3, 1);

    vector<tuple<int, int>> camino = encontrarCaminoMasCorto(cuadricula, inicio, final);

    cout << "Camino más corto:" << endl;
    for (const auto& punto : camino) {
        cout << "(" << get<0>(punto) << ", " << get<1>(punto) << ")" << " -> ";
    }
    cout << "Fin" << endl;

    return 0;
}

