#include "auxiliary.h"


anemoi::vec<uint> pad(const anemoi::vec<uint>& src, int n) {
    anemoi::vec<uint> dst(n);
    int size = src.size;
    for (int i = 0; i < size; ++i){
        dst[i] = src[i];
        //dst.push_back(src[i]);
    }

    return dst;
}

anemoi::vec<uint> unpad(const anemoi::vec<uint>& src, int min_size) {
    int current_size = src.size;
    int first_nonzero = 0;
    for (int i = 0; i < current_size - min_size; ++i){
        if (src[i] == 0){
            first_nonzero = i + 1;
        }
        else break;
    }
    anemoi::vec<uint> dst(current_size - first_nonzero);
    for (int i = first_nonzero; i < current_size; ++i){
        dst[i] = src[i];
        //dst.push_back(src[i]);
    }
    return dst;
}

bigint mul_mod(const bigint& first, const bigint& second, const bigint& modulo) {
    bigint x = bigint::zero;
    bigint y = first % modulo;
    bigint _second = second;
    while (_second > 0) {
        if (_second % 2 == 1) {
            x = (x + y) % modulo;
        }
        y = (y * 2) % modulo;
        _second = _second / 2;
    }
    return x % modulo;
}

size_t number_of_bits(const bigint& number) {
    size_t result = 0;
    bigint _number = number;
    while (_number > 0){
        result++;
        _number /= 2;
    }
    return result;
}
