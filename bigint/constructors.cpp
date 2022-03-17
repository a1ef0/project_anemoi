#include "big_integer.h"

template <typename T> int sgn(T src) {
    return (T(0) < src) - (src < T(0));
}

bigint::bigint(){
    _sign = 0;
    _number.resize(DEFAULT_SIZE, 0);
    current_size = DEFAULT_SIZE;
}

bigint::bigint(bool src){
    _sign = src;
    _number.resize(DEFAULT_SIZE, 0);
    current_size = DEFAULT_SIZE;
    _number[DEFAULT_SIZE - 1] = src;
}

bigint::bigint(char src){
    _sign = sgn(src);
    _number.resize(DEFAULT_SIZE, 0);
    current_size = DEFAULT_SIZE;
    _number[DEFAULT_SIZE - 1] = abs(src);
}

bigint::bigint(short src){
    _sign = sgn(src);
    _number.resize(DEFAULT_SIZE, 0);
    current_size = DEFAULT_SIZE;
    _number[DEFAULT_SIZE - 1] = abs(src);
}

bigint::bigint(int src){
    _sign = sgn(src);
    _number.resize(DEFAULT_SIZE, 0);
    current_size = DEFAULT_SIZE;
    _number[DEFAULT_SIZE - 1] = abs(src);
}

bigint::bigint(float src){
    int tmp = src;
    _sign = sgn(tmp);
    _number.resize(DEFAULT_SIZE, 0);
    current_size = DEFAULT_SIZE;
    _number[DEFAULT_SIZE - 1] = abs(tmp);
}

bigint::bigint(uint src){
    _sign = 1;
    _number.resize(DEFAULT_SIZE, 0);
    current_size = DEFAULT_SIZE;
    _number[DEFAULT_SIZE - 1] = src;
}

bigint::bigint(long long src){
    _sign = sgn(src);
    _number.resize(DEFAULT_SIZE, 0);
    current_size = DEFAULT_SIZE;
    _number[DEFAULT_SIZE - 1] = abs(src) & 0xffffffff;
    _number[DEFAULT_SIZE - 2] = (abs(src) >> 32);
}
