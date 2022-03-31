#ifndef AUXILIARY_H
#define AUXILIARY_H
#include "bigint.h"
template <typename T>
signed sgn(T src) {
    return (T(0) < src) - (src < T(0));
}

template <typename T>
T abs(T src){
    if (src < 0){
        return -src;
    }
    return src;
}

std::vector<uint> pad(const std::vector<uint>&, int);

std::vector<uint> unpad(const std::vector<uint>&, int);

#endif // AUXILIARY_H
