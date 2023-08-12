#pragma once
#include <random>
#include <vector>
#include <string>
#include <cstring>

//funcion que regresa todas las mutaciones de una palabra cambiando una letra a la vez.
std::vector<std::string> variantes(const std::string& palabra) {
    std::vector<std::string> ret;
    char* tmp = new char [palabra.size() + 1];
    for(int i=0; i < palabra.size(); i++){
        strcpy(tmp, palabra.c_str());
        for(char j = 'a'; j < 'z'; j++) {
            tmp[i] = j;
            ret.push_back(tmp);
        }
    }
    return ret;
}

/*
    Esta clase implementa un generador de numeros pseudoaleatoreos
    despues de llamar reset() la sequencia de numeros es identica a 
    la ejecucion anterior.
*/
class generator
{
    std::minstd_rand0 g;
    int seed;
public:
    generator(int seed=42) :
    g(seed), seed(seed) {}

    void reset(){g.seed(42);}
    long n(){return g();}
};

/*
    implementacion de BitVector
    normalmente uno usaria std::vector<bool> pero esta implementacion incluye
    la funcion find_unset para encontrar el primer bit que no este en uso.
*/
class BitVector{
    int*    container;
    int     size;
public:
    
    BitVector(int size) {
        int tmp = (size>>5) + 1;
        this->size=size;
        container = new int[tmp];
        memset(container, 0, tmp<<2);
    }

    ~BitVector(){
        delete [] container;
    }

    int* data(){
        return container;
    }

    bool get(int n){
        if(n<0 && n>size) return false;
        int tmp = container[n>>5];
        return (tmp >> n%32) & 1;
    }

    void set(int n){
        if(n<0 && n>size) return;
        container[n>>5] |= 1<<(n%32);
    }

    // regresa el primer bit en 0 desde la posicion indicada
    //-1 si no encuentra bits.
    int find_unset(int start)
    {
        if(start>=size) return -1;
        int idx = start>>5;
        int bit = start%32;
        if(container[idx]!=-1){
            for(int i = bit; i<32; i++){
                if(!get(start + i-bit)){
                    return start + i-bit;
                }
            }
        }
        while(container[idx]==-1){
            idx++;
            bit = 0;
            if(idx>(size>>5) + 1){
                return -1;
            }
        }
        int tmp = (idx<<5)+bit;
        while(tmp < size && get(tmp)){
            tmp++;
        }
        if(tmp<size) return tmp;
        return -1;
    }
};