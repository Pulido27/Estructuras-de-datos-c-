#pragma once
#include <unordered_map>
#include <vector>
#include <string>

struct referencia {
    struct node;
    struct node{
        char c = 0;
        std::unordered_map<char, node> data;
        //esta es una optimizacion para velocidad pero que consume mucha memoria
        std::vector<std::string> contains;
    };

    node root;

    void agregar(std::string p)
    {
        node* n = &root;
        for(int i=0; i<p.length(); i++){
            char t = p[i];
            if(!n->data.count(t)){
                //node no existe, crear uno
                n->data[t];
            }
            n = &n->data[t];
            n->c=t;
            n->contains.push_back(p);
        }
    }
    std::vector<std::string> completar(std::string p)
    {
        node* n = &root;
        for(int i=0; i<p.length(); i++){
            char t = p[i];
            if(!n->data.count(t)){
                //no hay palabras con ese prefijo
                return {};
            }
            n = &n->data[t];
        }
        return n->contains;
    }
};