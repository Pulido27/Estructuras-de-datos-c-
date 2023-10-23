#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;         

class nodo {
public:
    string nombre;
    unordered_map<string, nodo*> amigos;
    
    nodo(string n = " ") {
        nombre = n;
    }
};

class grafo {
    
public:
    nodo todos;
    
    void agregar(string a, string b) {
        if (!todos.amigos.count(a)) {
            todos.amigos.emplace(a, new nodo(a));
        }
        if (!todos.amigos.count(b)) {
            todos.amigos.emplace(b, new nodo(b));
        }
        
        todos.amigos[a]->amigos.emplace(b, todos.amigos[b]);
        todos.amigos[b]->amigos.emplace(a, todos.amigos[a]);
    } 
    
    bool acquaintances(string a, string b) {
    
        unordered_set<string> visitados;
        queue<string> queue1;
        queue1.push(a);
        string temp;
        
        while (!queue1.empty()) {
            temp = queue1.front();
            queue1.pop();
            
            while (visitados.count(temp) == 1) {
                if (queue1.empty()) {
                    cout << "No se conocen" << endl;
                    return false;
                }
                temp = queue1.front();
                queue1.pop();
            }
    
            if (temp == b) {
                cout << "Si se conocen" << endl;
                return true;
            }
        
            visitados.insert(temp);
    
            for (const auto& item : todos.amigos[temp]->amigos) {
                if (visitados.count(item.first) != 1) {
                    queue1.push(item.first);    
                }
            }
        }
        cout << "No se conocen" << endl;
        return false;
    }
    
};

int main(){
    grafo red;
    
    red.agregar("Juan", "Maria");
    red.agregar("Maria", "Pedro");
    red.agregar("Pedro", "Luis");
    
    red.acquaintances("Juan", "Pedro");  // Debería imprimir "Si se conocen"
    red.acquaintances("Juan", "Luis");   // Debería imprimir "Si se conocen"
    red.acquaintances("Maria", "Luis");  // Debería imprimir "Si se conocen"
    red.acquaintances("Juan", "Marta");  // Debería imprimir "No se conocen"
    
    return 0;
}

