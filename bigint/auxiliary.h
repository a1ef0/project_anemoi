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

/**
 * @brief pad Pads specified number of elements to the front of the std::vector
 * @param src The std::vector that neede to be padded
 * @param n number of elements to be added to the front of the std::vector
 * @return
 */
std::vector<uint> pad(const std::vector<uint>& src, int n);
std::vector<uint> unpad(const std::vector<uint>&, int);
bigint mul_mod(const bigint&, const bigint&, const bigint&);
size_t number_of_bits(const bigint&);

#endif // AUXILIARY_H
