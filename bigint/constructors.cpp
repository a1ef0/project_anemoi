#include "functions.h"
#include "big_integer.h"

bigint::bigint(){
    _sign = 0;
    _number.resize(DEFAULT_SIZE, 0);
    _current_size = DEFAULT_SIZE;
}

bigint::bigint(bool src) : bigint(){
    _sign = src;
    _number[DEFAULT_SIZE - 1] = src;
}

bigint::bigint(char src) : bigint(){
    _sign = sgn(src);
    _number[DEFAULT_SIZE - 1] = abs(src);
}

bigint::bigint(short src) : bigint(){
    _sign = sgn(src);
    _number[DEFAULT_SIZE - 1] = abs(src);
}

bigint::bigint(int src) : bigint(){
    _sign = sgn(src);
    _number[DEFAULT_SIZE - 1] = abs(src);
}

bigint::bigint(float src) : bigint(){
    int tmp = src;
    _sign = sgn(tmp);
    _number[DEFAULT_SIZE - 1] = abs(tmp);
}

bigint::bigint(uint src) : bigint(){
    _sign = 1;
    _number[DEFAULT_SIZE - 1] = src;
}

bigint::bigint(long long src) : bigint(){
    _sign = sgn(src);
    _number[DEFAULT_SIZE - 1] = abs(src) & 0xffffffff;
    _number[DEFAULT_SIZE - 2] = (src >> 32);
}

bigint::bigint(size_t src) : bigint(){
    _sign = 1;
    _number[DEFAULT_SIZE - 1] = src & 0xffffffff;
    _number[DEFAULT_SIZE - 2] = (src >> 32);
}

bigint::bigint(bigint& src){
    _sign = src._sign;
    _number = src._number;
    _current_size = src._current_size;
}

bigint::bigint(bigint&& src){
    _sign = src._sign;
    _number = std::move(src._number);
    _current_size = src._current_size;
}
