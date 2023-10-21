#include <iostream>
#include <vector>

using namespace std;


vector<pair> camino(int tabla[6][7], int filas, int columnas, pair<int, int> inicio, pair<int, int> final) {
	vector<pair<int, int>> solucion;
	solucion.push_back(inicio);
	
	unordered_set<pair<int, int>> visitados;
	queue<pair<int, int>> queue1;
	queue1.push(inicio);
	pair<int, int> temp;
	
	while (!queue1.empty()) {
		temp = queue1.front();
	    queue1.pop();
	    	
	    while (visitados.count(temp) == 1) {
	    	if (queue1.empty()) {
	    		cout << "No es posible llegar" << endl;
				return;		
			} 
			temp = queue1.front();
	    	queue1.pop();
		}
	
	    if (temp == final) {
	    	cout << "se llego al final" << endl;
	        return vector;
	    }
	    
	    visitados.insert(temp);
		
		
	}	
}


int main() {
	int tabla[6][7]=[1,0,0,0,0,0,0
					 0,0,1,0,0,1,0
					 0,0,0,0,0,0,0
					 0,0,1,0,1,0,0
					 0,0,1,0,0,0,0
					 0,1,0,0,0,1,0]	
	return 0;
}
