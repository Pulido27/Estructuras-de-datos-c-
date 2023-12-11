#include <iostream>
#include <queue>

using namespace std;

class pila {
private:
    queue<int> cola1;
    queue<int> cola2;

public:
    
    void insertar(int valor) {
        int aux = valor;
        
        if (cola1.size() < 5) {
            for (int i = 0; i < cola1.size(); i++) {
                cola1.push(aux);
                aux = cola1.front();
                cola1.pop(); 
            }
            cola1.push(aux);
            return;            
        }
        
        int tamano = cola2.size();
        
        while (cola1.size() != 0) {
            cola2.push(cola1.front());
            cola1.pop();
        }
        
        cola1.push(aux);
        
        for (int i = tamano; i > 0; i--) {
            aux = cola2.front();
            cola2.pop();
            cola2.push(aux);
        }
    }

    int top() {
        return cola1.front();
    }
    
    void pop() {
        cola1.pop();
    }
    
};

class pila_base {
private:
    queue<int> cola1;

public:
    pila_base() {
    }
    
    void insertar(int valor) {
        int aux = valor;
        
        for (int i = 0; i < cola1.size(); i++) {
            cola1.push(aux);
            aux = cola1.front();
            cola1.pop(); 
        }
        
        cola1.push(aux);
    }

    void pop() {
        cola1.pop();
    }

    int top() {
        return cola1.front();
    }    
    
};

class pila_base2 {
private:
    queue<int> q1, q2;

public:
    void insertar(int valor) {
        q1.push(valor);
    }
    
    void pop() {
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }
        q1.pop();
        swap(q1, q2);
    }
    
    int top() {
        return q1.back();
    }
};

int main() {
    pila pila1;
    pila1.insertar(1);
    pila1.insertar(2);
    pila1.insertar(3);
    pila1.insertar(4);
    
    cout << pila1.top();
    pila1.pop();
    cout << pila1.top();
    pila1.pop();
    cout << pila1.top();
    return 0;
}
