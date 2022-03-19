#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "big_integer.h"

template <typename T> signed sgn(T& src) {
    return (T(0) < src) - (src < T(0));
}

template <typename T> T abs(T src){
    return (1 - 2*(src < 0)) * src;
}

#endif // FUNCTIONS_H
