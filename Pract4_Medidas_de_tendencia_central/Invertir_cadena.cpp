#include <iostream>
#include <string>
#include <stack>

using namespace std;

// código apto solo cuando la palabra no termina en " "
string invertir(string cadena) {
    string palabra = "";
    stack<string> miPila;

    for (char c : cadena) {
        if (c != ' ') {
            palabra += c;
        } else {
            miPila.push(palabra);
            palabra.clear();
        }
    }

    while (!miPila.empty()) {
        palabra += " " + miPila.top();
        miPila.pop();
    }

    return palabra;
}

int main() {

    cout << invertir("asi habla yoda");

    return 0;
}
