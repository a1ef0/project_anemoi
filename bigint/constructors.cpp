#include "functions.h"
#include "bigint.h"

bigint::bigint(signed sign, std::vector<uint> number, int current_size){
    _sign = sign;
    _number = number;
    _current_size = current_size;
}

bigint::bigint(){
    _sign = 0;
    _number.resize(DEFAULT_SIZE, 0);
    _current_size = DEFAULT_SIZE;
}

bigint::bigint(long long src) : bigint(){
    _sign = sgn(src);
    _number[DEFAULT_SIZE - 1] = abs(src) & 0xffffffff;
    _number[DEFAULT_SIZE - 2] = (abs(src) >> 32);
}

bigint::bigint(const bigint& src){
    _sign = src._sign;
    _number = src._number;
    _current_size = src._current_size;
}

bigint::bigint(bigint&& src){
    _sign = src._sign;
    _number = std::move(src._number);
    _current_size = src._current_size;
}

//TODO: add here std::string constructor (available only after % and / operators made)
