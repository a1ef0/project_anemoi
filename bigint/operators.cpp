#include "big_integer.h"

std::ostream& operator <<(std::ostream& output, const bigint& src) {
    if (src._sign == 0){
        output << "0x0";
        return output;
    }
    else if (src._sign == -1){
        output << '-';
    }
    output << "0x";
    for (int i = 0; i < src._current_size; ++i){
        if (src._number[i] != 0 || i == src._current_size - 1){
            output << std::hex << src._number[i];
        }
    }
    return output;
}

bool operator>=(const bigint& first, const bigint& second){
    if (first._sign < second._sign || first._current_size < second._current_size){
        return false;
    }
    if (first._current_size > second._current_size){
        return true;
    }
    for (int i = 0; i < first._current_size; ++i){
        if (first._number[i] < second._number[i]){
            return false;
        }
    }
    return true;
}



bigint operator+(const bigint& src){

}
