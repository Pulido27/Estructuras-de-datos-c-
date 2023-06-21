#include <iostream>
#include <list>
using namespace std;

const int MAX_SIZE = 5;

class Fifolifo {
private:
    int data[MAX_SIZE];
    int count;

public:
    Fifolifo() {
        count = 0;
    }

    void push(int value) {
        if (count == MAX_SIZE) {
            cout << "Error: La lista está llena." << endl;
            return;
        }

        for(int i = count; i>0 ; i--){
        	data[i]=data[i-1];
		}
		data[0] = value;
        count++;
    }

    void append(int value) {
        if (count == MAX_SIZE) {
            cout << "Error: La lista está llena." << endl;
            return;
        }
		
		
		data[count]=value;
        count++;
    }

    int pop_front() {
        if (count == 0) {
            cout << "Error: La lista está vacía." << endl;
            return -1; // -1 simbolizando null 
        }

        int value = data[0];
        for(int i=0; i<count-1; i++){
        	data[i]=data[i+1];
		}
		data[count-1]=-1; //-1 simbolizando null
        count--;
        return value;
    }

    int pop_back() {
        if (count == 0) {
            cout << "Error: La lista está vacía." << endl;
            return -1; // Otra opción podría ser lanzar una excepción en lugar de retornar un valor especial.
        }

        int value = data[count-1];
        data[count-1]=-1; // -1 simbolizando null
        count--;
        return value;
    }

    int size() {
        return count;
    }
};

int main(){
	
	Fifolifo list1; 
	
	//llenar el objeto con numeros 
	list1.append(1);
	list1.append(2);
	list1.append(3);
	list1.append(4);
	list1.append(5);

	
	//invertirlos
	Fifolifo list2;
	
	while (list1.size() > 0) {
  	list2.push(list1.pop_front());
	}
	
	//ordenar la lista

    while (list2.size() > 0) {
        int min = list2.pop_front();
        int size = list2.size();

        for (int i = 0; i < size; i++) {
            int num = list2.pop_front();
            if (num < min) {
                list2.append(min);
                min = num;
            } else {
                list2.append(num);
            }
        }

        list1.append(min);
    }

    // Imprimir los elementos de la lista
    while (list1.size() > 0) {
        cout << list1.pop_front() << " ";
    }
    cout << endl;
	
	 // Usando la biblioteca estándar (std::list)

    // Guardar una lista de 10 números
    list<int> numbers;
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);
    numbers.push_back(4);
    numbers.push_back(5);
    numbers.push_back(6);
    numbers.push_back(7);
    numbers.push_back(8);
    numbers.push_back(9);
    numbers.push_back(10);

    // Invertir la lista
    numbers.reverse();

    // Ordenar la lista
    numbers.sort();

    // Imprimir los elementos de la lista
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
	
	
	

