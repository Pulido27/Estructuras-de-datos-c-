#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

// La funcion recibe start la palabra inicial y end la palabra final 
// Tambien recibe el set de palabras dict
vector<string> word_Converter(string start, string end, unordered_set<string>& dict) {
	
	// Comienza el bfs
    // Inicia la cola que contiene vectores de string
    // Contiene vectores de string porque alamcenara todos los posibles caminos de palabras para llegar a la palabra final
	queue<vector<string>> q;
    
    // Agrega la palabra inicial a la cola para que pueda empezar el bfs
	q.push({start});
    
    // Se declara el set que guardara las palabras visitadas
	unordered_set<string> visited;
    
    // Marca la palabra inicial como visitada
	visited.insert(start);
    
    // EL ciclo se efectua hasta encontrar la palabra final o que la cola se vacie
	while (!q.empty()) {
		
		// Se saca el primer elemento de la cola q y se almacena en path. 
		// Este vector path representa el camino actual que estamos explorando.
        vector<string> path = q.front();
        
		q.pop();
        
        // Se toma la última palabra en el camino actual path y se almacena en word
		string word = path.back();
        
    	// Retorna en el caso de que word sea igual a la palabra final
		if (word == end) {
            return path;
        }
        
		// Empieza el ciclo para recorrer la palabra letra por letra
		for (int i = 0; i < word.size(); i++) {
            
            // Se guarda la letra original
			char origChar = word[i];
            
            // Probamos todas las combinaciones posibles de letras en esa posicion
			for (char c = 'a'; c <= 'z'; c++) {
                
				word[i] = c;
                
                // Se verifica si la palabra existe en el conjunto y si ha sido visitada
                if (dict.count(word) && !visited.count(word)) {
                    
                    // Se hace una copia del camino actual 
					vector<string> newPath = path;
                    
                    // Se le agrega la nueva palabra generada
					newPath.push_back(word);
                    
                    // Se agrega este nuevo camino a la cola
					q.push(newPath);
                    
                    // Se marca como vistado
					visited.insert(word);
                }
            }
            // Se termina el primer ciclo y se vulve a poner la letra original a la palabra
            word[i] = origChar;
        }
    }
    return {};
}

int main() {
    unordered_set<string> dict = {"dead", "pair", "second", "deed", "reed", "reef", "beef"};
    vector<string> path = word_Converter("dead", "beef", dict);
    for (string word : path) {
        cout << word << " -> ";
    }
    cout << endl;
}

