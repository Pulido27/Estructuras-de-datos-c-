#include <iostream>

using namespace std;


class Nodo {
public:
	Nodo* right = nullptr;
	Nodo* left = nullptr;
	int value;
	
	Nodo(int value) {
		this->value = value;
	}
}

class BinaryTree {
private:
	Nodo* root = nullptr;
	
	BinaryTree() {
	}
	
	void push(int value) {
		if (root == nullptr) {
			root = new Nodo(int value);
			return;
		}
		
		Nodo* current = root;
		while(true) {
			Nodo*& NextNodo = (value > current) ? current->right : current->left;
			if(NextNodo == nullptr){
				NextNodo = new Nodo(value);
				return;
			}
			current = NexNodo
		}
		
	}
	
	
};



int main() {
	
	return 0;
}
