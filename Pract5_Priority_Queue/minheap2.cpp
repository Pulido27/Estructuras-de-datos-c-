#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


template<typename T>
class Minheap{
public:
	T* almacenamiento;
	int cola = 0;
	int capacidad = 0;
	
protected:
	int parent(int index){
        return (index-1)/2;
    }
    int left(int index){
        return index * 2 + 1;
    }
    int right(int index){
        return index * 2 + 2;
    }
    
    void rebalancear(int index) {
    	int der = right(index);
    	int izq = left(index);
    	int menor = index;
    	
    	if(der < cola && almacenamiento[der] < almacenamiento[index]) { 
    		menor = der;
		}
		
		if(izq < cola && almacenamiento[izq] < almacenamiento[menor]) {
			menor = izq;
		}
		
		if(menor != index) {
			swap(almacenamiento[menor],almacenamiento[index]);
			rebalancear(menor);
		}
	}
	
public:
	Minheap() = delete;
	Minheap(int capacidad) {
		this->capacidad = static_cast<int>(pow(2, capacidad) );
		almacenamiento = new T[this->capacidad];
	}
	
	~Minheap() {
        delete [] almacenamiento;
    }
    
    void push(T dato) { 
    	if(cola >= capacidad) return;
    	almacenamiento[cola] = dato;
    	int index = cola;
		cola++;
		bool continuar = true;
		
		while(index > 0) {
			if(almacenamiento[index] < almacenamiento[parent[index]]){
				swap(almacenamiento[index], almacenamiento[parent(index)]);
				index = parent(index);
			}else{
				break;
			}
		}
	}
	
	T pop(){
        T tmp = almacenamiento[0];
        cola--;
        almacenamiento[0] = almacenamiento[cola];
        rebalancear(0);
        return tmp;
    }
	
};

int main() {
	return 0;
}
