#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

template <typename T>
class CacheMemory{
private:
    int capacity;
    list<T> storage;
    unordered_map<T, typename list<T>::iterator> address;
    
public:
    CacheMemory(int value = 10) {
        capacity = value;
    }
    
    void push(T value) {
        if(address.count(value) == 1){
            storage.erase(address[value]);
            storage.push_front(value);
            address[value] = storage.begin();
        }
        else if (storage.size() < capacity) {
            storage.push_front(value);
            address[value] = storage.begin();    
        }
        else{
            storage.pop_back();
            storage.push_front(value);
            address[value] = storage.begin();
        }
    }
    
    T find(T value) {
        if(address.count(value) == 1) {
            return *(address[value]);
        }
        return T{};
    }
    
    void display(int value = -1) {
        if (value == -1) {
            value = storage.size();
        }
        int count = 0;
        for (const auto &val : storage) {
            cout << val << " ";
            count++;
            if (count >= value) {
                cout << endl;
                break;
            }
        }
    }
};

int main() {
    
    CacheMemory<int> cache(5);
    
    cache.push(10);
    cache.push(11);    
    cache.push(12);
    cache.display();
    
    cout << cache.find(10) << endl;
    cout << cache.find(11) << endl;
    cout << cache.find(12) << endl;
    cout << cache.find(13) << endl;
    cache.display();
    
    cache.push(10);
    cout << cache.find(10) << endl;
    cout << cache.find(11) << endl;
    cout << cache.find(12) << endl;
    cout << cache.find(13) << endl;
    cache.display();
    
    cache.push(13);
    cache.push(14);
    cache.push(15);
    cache.display();
    return 0;
}

