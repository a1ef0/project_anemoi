#include "auxiliary.h"

std::vector<uint> pad(const std::vector<uint>& src, int n){
    std::vector<uint> dst(n, 0);
    int size = src.size();
    for (int i = 0; i < size; ++i){
        dst.push_back(src[i]);
    }
    return dst;
}

std::vector<uint> unpad(const std::vector<uint>& src, int min_size){
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
    return dst;
}
