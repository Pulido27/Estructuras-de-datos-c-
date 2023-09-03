#include <iostream>
#include <string>

using namespace std;

// Función para expandir desde el centro y encontrar el palíndromo más grande
string expandirDesdeCentro(const string& cadena, int izquierda, int derecha) {
    int n = cadena.length();
    while (izquierda >= 0 && derecha < n && cadena[izquierda] == cadena[derecha]) {
        izquierda--;
        derecha++;
    }
    return cadena.substr(izquierda + 1, derecha - izquierda - 1);
}

// Función para encontrar el palíndromo más grande en la cadena
string palindromoMasGrande(const string& cadena) {
    int n = cadena.length();
    string palindromoMaximo = "";

    for (int i = 0; i < n; i++) {
        string palindromo1 = expandirDesdeCentro(cadena, i, i); // Para cadenas de longitud impar
        string palindromo2 = expandirDesdeCentro(cadena, i, i + 1); // Para cadenas de longitud par

        // Comparar y actualizar el palíndromo más grande encontrado
        if (palindromo1.length() > palindromoMaximo.length()) {
            palindromoMaximo = palindromo1;
        }

        if (palindromo2.length() > palindromoMaximo.length()) {
            palindromoMaximo = palindromo2;
        }
    }

    return palindromoMaximo;
}

int main() {
    string cadena = "xxanitalavalatinayyy";

    string resultado = palindromoMasGrande(cadena);
    cout << "El palindromo mas grande es: " << resultado << endl;

    return 0;
}
