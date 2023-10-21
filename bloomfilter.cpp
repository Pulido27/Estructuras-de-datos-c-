#include <iostream>
#include <unordered_set>
#include <hash>

using namespace std;

// al menos 100 alabras
//50% de probabilidad
//acepta strings
///https://hur.st/bloomfilter/?n=100&p=50&m=&k=3

struct llaves {
    int a;
    int b;
    int c;
    
    llaves(int a, int b,int c) :
    a(a), b(b), c(c){}
};

class bloomfilter{
    void insert(string a){
        llaves = calcula_llaves(a);
        almacen.insert(llaves.a);
        almacen.insert(llaves.b);
        almacen.insert(llaves.c);
    }

public:    
    unordered_set<bool> almacen;
    
    llaves calcula_llaves(string txt){
    
        char sal = "1";
        int llave1 = hash(txt + sal) % tabla_size;
        int llave2 = llave1;
        int llave3 = 0;

        while(llave1 == llave2) {
            sal++;            
            llave2 = hash(txt + sal) % tabla_size;
            
        }
        
        llave3 = llave2;
        while (llave1 == llave3 || llave2 == llave3){
            sal++
            llave3 = hash(txt + sal) % tabla_size;
        }
        

        return {llave1, llave2, llave3};
    }    
    
    void agregar(string a){
        insert(a);
    }
    
    bool buscar(string a) {
        
        llave llaves = calcula_llaves(a);
        
        if ( almacen.count(llaves.a) && almacen.count(llaves.b) && almacen(llaves.c) ) {
            return true;
        }
        return false;
    }
};

int main() {

    return 0;
}
