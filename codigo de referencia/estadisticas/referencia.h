#pragma once
#include <unordered_map>
#include <queue>


struct referencia_number_stream {
    std::unordered_map<int, int>                                      frequencies;
    std::priority_queue<int, std::vector<int>, std::greater<int>>     upper;
    std::priority_queue<int, std::vector<int>, std::less<int>>        lower;
    long long int                                                     sum;
    long                                                              c;

    int moda()
    {
        std::pair<int, int> moda;
        for( auto& kv: frequencies ) {
            if ( moda.second < kv.second ) {
                moda = kv;
            }
        }
        return moda.first;
    }

    int mediana()
    {
        int tmp = 0;
        
        if(upper.size() > lower.size()){
            tmp = upper.top();
        } else if(lower.size() > upper.size()){
            tmp = lower.top();
        } else {
            tmp = (upper.top() + lower.top()) /2;
        }

        return tmp;
    }

    float promedio()
    {
        if(c==0) return 0.0;
        return sum/c;
    }

    void add(int i)
    {
        sum+=i;
        c++;

        if(frequencies.count(i) == 1 ) {
            frequencies[i] = frequencies[i]++;
        } else {
            frequencies[i] = 1;
        }

        if (lower.size() == 0 || i <= lower.top()){
            lower.push(i);
        } else if (upper.size() == 0 || i > upper.top()) {
            upper.push(i);
        }

        //la listas deben de estar balanceadas, para numero impar de elementos, se le da prioridad a la lista baja.
        int balance = upper.size() - lower.size();
        if (balance == 0) return;
        if (balance > 0) {
            //hay mas elementos en la lista de arriba
            while(upper.size() > lower.size()) {
                lower.push(upper.top());
                upper.pop();
            }
        } else {
            //hay mas elementos en la lista de abajo
            while(lower.size() > upper.size()) {
                upper.push(lower.top());
                lower.pop();
            }
        }
    }
};