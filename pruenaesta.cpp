#include <iostream>

using namespace std;


class Fifolifo{
private:
	int* data = nullptr;
	int max_size;
	int rear = 0;
	int count = 0;
	int front;
	
	Fifolifo(int size) {
		max_size = size;
		data = new int[mas_size];
		front = max_size - 1;
	}
	
	~Fifolifo(){
		delete data[];
	}
	
	void push(int value) {
		if (count == max_size) {
			cout << "esta lleno" <<endl;
			return;
		}
		
		front = front + 1 % max_size;
		data[front] = value;
		count++;
	}
	
	void append(int value) {
		if(count == max_size){
			cout << "esta lleno" <<endl;
			return;
		}
		
		rear = rear - 1 % max_size;
		data[rear] = value;
		count++;
	}
	
	
	
};
	

