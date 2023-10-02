#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Person{
public:
	string nombre;
	vector<Person*> amigos;
	
	Person(string n = " ") {
		nombre = n;
	}
	
	void pushFriend(Person* p) {
		amigos.push_back(p);
	}
};

bool acquaintances(Person a, Person b) {
	if (a.amigos.size() > b.amigos.size()) {
    	swap(a, b);
	}

	queue<Person*> queue1;
	queue1.push(&a);
	Person* temp;

	while (!queue1.empty()) {
		temp = queue1.front();
    		queue1.pop();
    	
    	while(temp->nombre == "visitado") {
    		temp = queue1.front();
    		queue1.pop();
		}
    	
    	//cout<<"temp: "<< temp->nombre <<endl;

    	if ((*temp).nombre == b.nombre) {
    		cout << "Si se conocen" << endl;
        	return true;
    	}
    
    	temp->nombre = "visitado";

    	for (auto item : temp->amigos) {
        	if (item->nombre != "visitado") {
        		//cout << "item: " << item->nombre << endl;
        		queue1.push(item);	
			}
    	}
	}
	cout << "No se conocen" << endl;
	return false;
}


int main(){
	Person oscar("oscar");
	Person alberto("alberto");
	Person isaac("isaac");
	Person maria("maria");
	Person ted("ted");
	Person flor("flor");
	Person luis("luis");
	Person mariana("mariana");
	Person dante("dante");
	Person felipe("felipe");
	Person enrique("enrique");
	Person victor("victor");
	
	oscar.pushFriend(&flor);
	oscar.pushFriend(&luis);
	oscar.pushFriend(&mariana);
	oscar.pushFriend(&alberto);
	
	flor.pushFriend(&oscar);
	luis.pushFriend(&oscar);
	mariana.pushFriend(&oscar);
	alberto.pushFriend(&oscar);
	
	dante.pushFriend(&victor);
	victor.pushFriend(&dante);
		
	acquaintances(oscar,victor);
	
	return 0;
}
