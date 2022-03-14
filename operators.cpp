#include "big_integer.h"
#include "iostream"

std::ostream& operator <<(std::ostream& output, const bigint& src) {
    if (src._sign == 0){
        output << '0';
        return output;
    }
    for (int i = src.current_size - 1; i >= 0; --i){
        if (src._number[i] != 0){
            output << std::to_string(src._number[i]);
        }
    }
    return output;
}
