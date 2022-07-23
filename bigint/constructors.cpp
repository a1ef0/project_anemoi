#include "auxiliary.h"

bigint bigint::zero = bigint(0);
bigint bigint::one = bigint(1);
bigint bigint::two = bigint(2);

bigint::bigint(signed sign, anemoi::vec<uint> number, int current_size) {
    _sign = sign;
    _number = number;
    _current_size = current_size;
}

bigint::bigint() {
    _sign = 0;
    _number = anemoi::vec<uint>(DEFAULT_SIZE);
    _current_size = DEFAULT_SIZE;
}

bigint::bigint(long long src) : bigint() {
    _sign = sgn(src);
    src = std::abs(src);
    _number[DEFAULT_SIZE - 1] = src & 0xffffffff;
    _number[DEFAULT_SIZE - 2] = (src >> 32);
}

bigint::bigint(const bigint& src) {
    _sign = src._sign;
    _number = src._number;
    _current_size = src._current_size;
}

bigint::bigint(bigint&& src) {
    _sign = src._sign;
    _number = std::move(src._number);
    _current_size = src._current_size;
}

bigint::bigint(const std::string& src) : bigint() {
    int cur = 0, size = src.size();
    const char* src_ = src.c_str();
    while (cur < size){
        *this *= 10;
        *this = *this + (src_[cur] - 48);
        cur++;
    }
}
