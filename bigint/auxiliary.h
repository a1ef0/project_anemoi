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
anemoi::vec<uint> pad(const anemoi::vec<uint>& src, int n);
anemoi::vec<uint> unpad(const anemoi::vec<uint>&, int);
bigint mul_mod(const bigint&, const bigint&, const bigint&);
size_t number_of_bits(const bigint&);

#endif // AUXILIARY_H
