#include <iostream>
#include <string>

using namespace std;

class trie {
public:
    enum class tipo {
        nodo = 0,
        fin = 1,
    };

private:
    struct nodo {
        char c;
        nodo* hijos[26];
        tipo accion;

        nodo() : c('\0'), accion(tipo::nodo) {
            for (int i = 0; i < 26; i++) {
                hijos[i] = nullptr;  // Inicializar todos los hijos a nullptr
            }
        }

        nodo(char c) : c(c), accion(tipo::nodo) {
            for (int i = 0; i < 26; i++) {
                hijos[i] = nullptr;  // Inicializar todos los hijos a nullptr
            }
        }

        ~nodo() {
            for (int i = 0; i < 26; i++) {
                delete hijos[i];  // Eliminar los hijos si existen
            }
        }
    };

    struct nodo raiz;

    bool _imprimir(struct nodo* n, int x) {
        bool flag = false;
		
		if (!n) {
            return false;
        }

        cout << n->c;
        
        if (n->accion == tipo::fin) {
            cout << endl;
            flag = true;
        }

        for (int i = 0; i < 26; i++) {
            if (n->hijos[i]) {    	
            	if (!flag) {
					cout << " ";
				}else{
					for(int i = 0; i < x; i++){
						cout << " ";
					}	
				}
               flag = _imprimir(n->hijos[i], x + 2);                 
            }
        }
        return true;
    }
    
    int _longitud (struct nodo* n, int x) {
        bool flag = false;
		
		if (!n) {
            return false;
        }
        
        if (n->accion == tipo::fin) {
            x++;
        }

        for (int i = 0; i < 26; i++) {
            if (n->hijos[i]) {
               x = _longitud(n->hijos[i], x);                 
            }
        }
        return x;    	
	}
	
	void _listar(struct nodo* n, string palabra) {
        if (!n) {
            return;
        }

        palabra.push_back(n->c);

        if (n->accion == tipo::fin) {
            cout << palabra << endl;
        }

        for (int i = 0; i < 26; i++) {
            if (n->hijos[i]) {
                _listar(n->hijos[i], palabra);
            }
        }

        palabra.pop_back(); // Retroceder para eliminar la última letra al finalizar la recursión
    }

public:
    void agregar(string p) {
        struct nodo* n = &raiz;

        for (int i = 0; i < p.length(); i++) {
            char letra = p[i];
            int i_letra = letra - 'a';

            if (n->hijos[i_letra] == nullptr) {
                n->hijos[i_letra] = new struct nodo(letra);
            }

            n = n->hijos[i_letra];
        }

        n->accion = tipo::fin;
    }

    void imprimir() {
    	bool residuo;
    	for(int i =0; i<26; i++){
    		if(raiz.hijos[i]){
        		residuo = _imprimir(raiz.hijos[i], 2);
			}
		}	
    }
    
	bool buscar(string p){
        struct nodo* n = &raiz;

        for (int i = 0; i < p.length(); i++) {
            char letra = p[i];
            int i_letra = letra - 'a';

            if (n->hijos[i_letra] == nullptr) {
            	return false;
            }

            n = n->hijos[i_letra];
        }
		
		return (n->accion==tipo::fin) ? true : false; 
	}
	
	int longitud () {
		return _longitud(&raiz,0);
	}
    
    void listar () {
		string palabra;
		_listar(&raiz, palabra);
	}
	
	void autocompletar (string cadena) {
		struct nodo* n = &raiz;

        for (int i = 0; i < cadena.length(); i++) {
            char letra = cadena[i];
            int i_letra = letra - 'a';

            if (n->hijos[i_letra] == nullptr) {
            	return;
            }

            n = n->hijos[i_letra];
        }
        cadena.pop_back();
		_listar(n, cadena);
	}
	
	void insertarTexto(string texto) {
		string palabra = "";
		for (int i = 0; i < texto.length(); i++) {
			char letra = tolower(texto[i]);
			if (letra >= 'a' && letra <= 'z') {
				palabra += letra;
			}
			else {
				if (!palabra.empty()) {
					agregar(palabra);
					palabra = "";
				}
			}
		}
		if (!palabra.empty()) {
			agregar(palabra);
		}
	}
	
};

int main() {
    trie t;
    
    
    t.insertarTexto();
	t.listar();    

	return 0;	
}
