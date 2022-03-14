#include "big_integer.h"

template <typename T> int sgn(T src) {
    return (T(0) < src) - (src < T(0));
}

bigint::bigint(){
    _sign = 0;
    current_size = DEFAULT_SIZE;
    _number = std::vector<size_t>(DEFAULT_SIZE, 0);
}

bigint::bigint(int src){
    _sign = sgn(src);
    current_size = DEFAULT_SIZE;
    _number = std::vector<size_t>(DEFAULT_SIZE, 0);
    _number[0] = src;
}


bigint::bigint(short src){
    _sign = sgn(src);
    current_size = DEFAULT_SIZE;
    _number = std::vector<size_t>(DEFAULT_SIZE, 0);
    _number[0] = src;
}


bigint::bigint(char src){
    _sign = sgn(src);
    current_size = DEFAULT_SIZE;
    _number = std::vector<size_t>(DEFAULT_SIZE, 0);
    _number[0] = src;
}


bigint::bigint(long long src){
    _sign = sgn(src);
    current_size = DEFAULT_SIZE;
    _number = std::vector<size_t>(DEFAULT_SIZE, 0);
    int i = 0;
    while (src > 0){
        _number[i] = src % _base;
        src /= _base;
        i++;
    }
}

bigint::bigint(size_t src){
    _sign = sgn(src);
    _number = std::vector<size_t>(DEFAULT_SIZE, 0);
    current_size = DEFAULT_SIZE;
    int i = 0;
    while (src > 0){
        _number[i] = src % _base;
        src /= _base;
        i++;
    }
}

bigint::bigint(const std::string& src){
    int _size = src.size();
    _number.resize(_size / _base_log + 1);

}
