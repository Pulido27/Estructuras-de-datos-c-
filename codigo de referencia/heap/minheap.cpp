#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>

using namespace std;

template <typename T>
class MinPQArray {
    T* storage;
    int tail        = 0;
    int capacity    = 0;

protected:
/*
            0
        1       2
    3      4 5      6
*/
    int parent(int index){
        return (index-1)/2;
    }
    int left(int index){
        return index * 2 + 1;
    }
    int right(int index){
        return index * 2 + 2;
    }

    void print(int index = 0){
        cout<<index<<" : ";
        for (int i = 0; i < tail+1; i++) {
            cout<<storage[i]<<";";
        }
        cout<<endl;
    }

    void rebalance(int index){
        //during rebalancing we need to make sure tail points to the last element
        if(index > tail) return;
        //check children
        //print(index);
        int l = left(index);
        int r = right(index);
        int smallest = index;
        if(l<tail && storage[l] < storage[index])
            smallest = l;
        if(r<tail && storage[r] < storage[smallest])
            smallest = r;
        if(smallest != index){
            swap(storage[smallest], storage[index]);
            rebalance(smallest);
        }
        //print(index);
    }

public:
    MinPQArray() = delete;
    MinPQArray(int capacity) {
        this->capacity = static_cast<int>(pow(2,capacity));
        storage = new T[this->capacity];
    }

    ~MinPQArray(){
        delete [] storage;
    }

    void push(const T& data) {
        if(tail >= capacity) return;
        storage[tail] = data;
        int index = tail++;
        cout<<"push "<<data<<endl;
        
        while(index > 0) {
            print(index);
            if (storage[index] < storage[parent(index)]) {
                swap(storage[index], storage[parent(index)]);
            }
            index = parent(index);
        }
    }

    T pop(){
        T tmp=storage[0];
        tail--;
        //cout<<"pop "<<tmp<<endl;
        storage[0] = storage[tail];
        rebalance(0);
        return tmp;
    }

    size_t size(){
        return tail-1;
    }

};

int main(){
    MinPQArray<int> v(10);
    
    srand(2);
    for(int i = 0; i<10; i++){
        v.push(rand());
    }
    cout<<"pop"<<endl;
    while (v.size()){
        cout<<v.pop()<<endl;
    }


    return 0;
}