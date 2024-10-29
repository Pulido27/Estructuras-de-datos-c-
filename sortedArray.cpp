#include <iostream>
#include <vector>

using namespace std;

int findPivot(vector<int> v, int left, int right, int value){
 
    while(true){

        int middle = left + (right-left)/2;

        if(v[middle] > v[middle + 1]){
            return middle;
        }

        if(v[left] < v[middle]){
            left = middle;
        }else{
            right = middle;
        }
    }
}

int getIndex(vector<int> v, int value){
    int pivot = findPivot(v, 0, v.size() - 1, value);
    int distance = v[pivot] - value;
     if((pivot - distance) >= 0){
        return (pivot - distance);
     }else{
        return (v.size() + (pivot - distance));
     }    
    
    return 0;
}

int binarySearch(vector<int>& v, int value){
    int left = 0;
    int right = v.size() - 1;
    
    while(left<=right){
        int middle = left + (right-left)/2;
        
        if(v[middle] == value){
            return middle;
        }
        
        if(v[middle]<value){
            left = middle + 1;
        }else{
            right = middle - 1;
        }
    }
    
    return -1;
}

int main(){
    vector<int> v = {4,5,6,7,8,1,2,3};

    int a;
    for(int i : v){
        
        a = getIndex(v,i);
        cout << a <<endl;
    }
    return 0;
}