#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>

using namespace std;

struct index {
    int Word;
    int Bit;
};

class Bitset {
public:
    vector<uint64_t> data;

    index getIndex(int i) {
        index indexes;
        indexes.Word = i/64;
        indexes.Bit = i%64;
        return indexes;
    }

//public:
    
    Bitset(double n = 64.0) {
        int size = ceil(n/64.0);
        data.assign(size,0);
    }

    void set(int value) {
        index i = getIndex(value);
        data[i.Word] |= 1ULL << i.Bit;
    }

    void reset(int value) {
        index i = getIndex(value);
        data[i.Word] &= ~(1ULL << i.Bit);
    }

    void flip(int value) {
        index i = getIndex(value);
        data[i.Word] ^= 1ULL << i.Bit;
    }
    
    bool test(int value) {
        index i = getIndex(value);
        bool is_set = data[i.Word] & (1ULL << i.Bit);
        return is_set;
    }

    void resize(double n = 64.0) {
        int size = ceil(n/64.0);
        data.resize(size);
    }

    int size() {
        return data.size();
    }
};