#include <iostream>
#include <stack>

using namespace std;

class cola {
private:
    stack<int> pila1;
    stack<int> pila2;
    bool indicador = true;

public:

    void push(int valor) {
        pila1.push(valor);
    }

    void pop() {
        if (indicador) {
            while (pila1.size() != 0) {
                pila2.push(pila1.top());
                pila1.pop();
            }
            indicador = false;
            pila2.pop();
            return;
        }

        if (pila2.size() == 1) {
            pila2.pop();
            indicador = true;
        } else {
            pila2.pop();
        }
    }

    int top() {
        if (indicador) {
            while (pila1.size() != 0) {
                pila2.push(pila1.top());
                pila1.pop();
                indicador = false;
            }
            return pila2.top();
        }
        return pila2.top();
    }

};


int main() {
    cola cola1;

    cola1.push(1);
    cola1.push(2);
    cola1.push(3);
    cola1.push(4);

    cout << cola1.top();
    cola1.pop();
    cola1.push(5);
    cout << cola1.top();
    cola1.push(6);
    cola1.push(7);
    cola1.pop();
    cout << cola1.top();
    cola1.pop();
    cout << cola1.top();
    cola1.pop();
    cout << cola1.top();
    cola1.push(8);
    cola1.pop();
    cout << cola1.top();
    cola1.pop();
    cout << cola1.top();
    cola1.pop();
    cout << cola1.top();
    return 0;
}
