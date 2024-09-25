#include <iostream>

using namespace std;
//siendo n1 y n2 el número de elementos que tienen no el espacio de estos
void unir(int a[], int n1, int b[], int n2) {
    
    int j = 1;
    int i = 1;
    int k = 1;
    
    while (i <= n1 && j <= n2) {
        if (a[n1 - i] > b[n2 - j]) {
            a[n1 + n2 - k] = a[n1 - i];
            i++;
        } else {
            a[n1 + n2 - k] = b[n2 - j];
            j++;
        }
        k++;
    }
    
    while (i <= n1) {
        a[n1 + n2 - k] = a[n1 - i];
        i++;
        k++; 
    }
    
    while (j <= n2) {
        a[n1 + n2 - k] = b[n2 - j];
        j++;
        k++; 
    }
}

int main() {
    
    int vec[] = {1, 3, 5, 6, 7};
    int arr[] = {1, 5, 6};
    
    unir(vec, 2, arr, 3);
    
    for (int i = 0; i < 5; i++) {
        cout << vec[i] << endl;
    }    
    return 0;
}
