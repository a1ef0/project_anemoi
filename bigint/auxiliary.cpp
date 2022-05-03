#include "auxiliary.h"

std::vector<uint> pad(const std::vector<uint>& src, int n) {
    std::vector<uint> dst(n, 0);
    int size = src.size();
    for (int i = 0; i < size; ++i){
        dst.push_back(src[i]);
    }
    return std::move(dst);
}

std::vector<uint> unpad(const std::vector<uint>& src, int min_size) {
    int current_size = src.size();
    int first_nonzero = 0;
    std::vector<uint> dst;
    for (int i = 0; i < current_size - min_size; ++i){
        if (src[i] == 0){
            first_nonzero = i + 1;
        }
        else break;
    }
    for (int i = first_nonzero; i < current_size; ++i){
        dst.push_back(src[i]);
    }
    return std::move(dst);
}

bigint mul_mod(const bigint& first, const bigint& second, const bigint& modulo) {
    bigint x = 0;
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
