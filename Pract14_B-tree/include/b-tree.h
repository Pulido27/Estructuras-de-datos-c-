#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

const int Max_size = 5;

using namespace std;

class Node {
public:
    vector<int> keys;  // Vector para almacenar las claves
    vector<Node*> children;  // Vector para almacenar punteros a los hijos
    bool leaf;  // Indica si el nodo es una hoja

    // Constructor
    Node(bool _leaf = true) : leaf(_leaf) {}

    // Función para dividir un hijo
    void splitChild(int*& middle, Node*& newNode) {
        newNode = new Node();
        newNode->leaf = leaf;
        int pos = keys.size()/2;
        middle = new int(keys[pos]);

        for (int i = pos + 1; i < Max_size; i++) {
            newNode->keys.push_back(keys[i]);
        }

        keys.resize(pos);

        if (!leaf) {
            
            for (int j = pos + 1; j < Max_size + 1; j++) {
                newNode->children.push_back(children[j]);
            }
            
            children.resize(pos + 1);
        }
    }

    void printNode(){
        for(int i=0; i < keys.size(); i++) {
            cout << keys[i] << " ";
        }
        cout<<endl;
    }
};

// Clase que representa el B-tree
class BTree {
private:
    Node* root;  // Puntero a la raíz del árbol

    void _insert(Node*& currentNode, int value, int*& middle, Node*& newNode) {
        
        if (currentNode->leaf) {
            int i = 0;
            while (i < currentNode->keys.size() && currentNode->keys[i] < value ) {
                i++;
            }
            currentNode->keys.insert(currentNode->keys.begin() + i, value);

            if (currentNode->keys.size() == Max_size) {
                currentNode->splitChild(middle, newNode);
            }

        } else {
            int i = 0;
            while (i < currentNode->keys.size() && currentNode->keys[i] < value) {
                i++;
            }

            _insert(currentNode->children[i], value, middle, newNode);

            if (middle != nullptr) {

                currentNode->keys.insert(currentNode->keys.begin() + i, *middle);
                currentNode->children.insert(currentNode->children.begin() + i + 1, newNode);

                middle = nullptr;
                newNode = nullptr;

                if (currentNode->keys.size() == Max_size) {
                    currentNode->splitChild(middle, newNode);
                }
            }
        }
    }

    pair<int, bool>  _search(Node* currentNode, int& value, int level = 1) {
        int i = 0;
        //cout << "level: " << level <<endl;
        // Si el nodo es una hoja, busca la clave directamente en las claves del nodo
        if (currentNode->leaf) {
            while (i < currentNode->keys.size()) {
                if (currentNode->keys[i] == value) {
                    pair<int, bool> myPair(level,true);
                    return myPair;
                }
                i++;
            }
            pair<int, bool> myPair(0,false);
            return myPair;
        } else {
            // Para nodos internos, busca la posición correcta para seguir el subárbol adecuado
            while (i < currentNode->keys.size() && value > currentNode->keys[i]) {
                i++;
            }
            // Si la clave coincide con una clave en el nodo, devuelve true
            if (i < currentNode->keys.size() && currentNode->keys[i] == value) {
                pair<int, bool> myPair(level,true);
                return myPair;
            }
            // De lo contrario, busca recursivamente en el hijo correspondiente
            return _search(currentNode->children[i], value, level + 1);
        }
    }

    void _traverse(Node* currentNode){
        if (currentNode->leaf) {
            currentNode->printNode();
        } else {
            int i = 0;
            while (i < currentNode->children.size()) {
                _traverse(currentNode->children[i]);
                i++;
            }
        }
    }

public:
    // Constructor
    BTree() {
        root = new Node(true);
    }

    // Función para insertar una clave en el B-tree
    void insert(int value){
        int* middle = nullptr;
        Node* newNode = nullptr;

        _insert(root, value, middle, newNode);

        if (middle != nullptr) {
                Node* NewRoot = new Node(false);
                NewRoot->keys.push_back(*middle);
                NewRoot->children.push_back(root);
                NewRoot->children.push_back(newNode);
                root = NewRoot;
        }
    }

    bool search(int value) {
        pair<int, bool> result;
        result = _search(root, value);
        return result.second;
    }   

    int getLevel(int lastValue){
        pair<int, bool> level;
        level = _search(root, lastValue);
        return level.first;
    }

    void print() {
        _traverse(root);
    }
};