#include <iostream>

using namespace std;

#define lado 257

int matrix[lado][lado];

void inicializar_matrix() {
    for(int i = 0; i < lado; i++) {		
        for(int j = 0; j < lado; j++) {
            matrix[i][j] = j + i * lado; // Cambio en el orden de los índices	
        }	
    }
}

long long suma2() {
    long long sum = 0;
    for(int i = 0; i < lado; i++) {	
        for(int j = 0; j < lado; j++) {
            sum += matrix[i][j];
            //cout << "i: " << i << " j: " << j << " matrix: " << matrix[i][j] << " sum: " << sum << endl;               	
        }	
    }
    return sum;
}


int main(){
    inicializar_matrix();



    return 0;
}