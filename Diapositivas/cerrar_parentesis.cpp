#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool cierre_parentesis(string cadena) {
    int pila = 0;
    for (char c : cadena) {
        if (c == '(') {
            pila++;
        }
        
        if (c == ')') {
            pila--;    
        }
    }
    return (pila == 0);    
}

bool parentesis(const string &expression) {
    stack<char> s;

    for (char ch : expression) {
        if (ch == '(' || ch == '[' || ch == '{') {
            s.push(ch);
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (s.empty()) {
                return false;  // No hay paréntesis de apertura correspondientes
            }
            
            char top = s.top();
            s.pop();
            
            if ((ch == ')' && top != '(') ||
                (ch == ']' && top != '[') ||
                (ch == '}' && top != '{')) {
                return false;  // Paréntesis desequilibrados
            }
        }
    }

    return s.empty();  // Si quedan paréntesis sin cerrar, no están equilibrados
}

int main() {
    string x = "(4(2)3";
    cout << cierre_parentesis(x);

    return 0;
}
