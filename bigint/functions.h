#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#pragma once
#include "bigint.h"
template <typename T>
signed sgn(T src) {
    return (T(0) < src) - (src < T(0));
}
/*
template <typename T>
T abs(T src){
    return (1 - 2*(src < 0)) * src;
}
*/
template <typename T>
T abs(T src){
    if (src < 0){
        return -src;
    }
    return src;
}

std::vector<uint> pad(const std::vector<uint>& src, int n);

std::vector<uint> unpad(const std::vector<uint>& src, int min_size);

#endif // FUNCTIONS_H
