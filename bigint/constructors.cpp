#include "auxillary.h"

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
    _number[DEFAULT_SIZE - 1] = std::abs(src) & 0xffffffff;
    _number[DEFAULT_SIZE - 2] = (std::abs(src) >> 32);
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

bigint::bigint(const std::string& src) : bigint(){
    int cur = 0, size = src.size();
    const char* src_ = src.c_str();
    while (cur < size){
        *this *= 10;
        *this = *this + (src_[cur] - 48);
        cur++;
    }
}
