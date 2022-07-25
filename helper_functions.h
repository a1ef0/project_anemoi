#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <cln/integer.h>

namespace anemoi {

template <class T>
T pow(T base, T exp) {
    T result = 1;
    if (base < 0) {
        throw std::runtime_error("cannot pow negative number");
    }
    if (exp < 0) {
        exp += base * (cln::floor1(abs(exp), base));
    }
    while (exp > 0) {
        if (mod(exp, 2) == 1) {
            result = (result * base);
        }
        base = cln::square(base);
        exp = cln::floor1(exp, 2);
    }
    return result;
}

template <class T>
T pow(T base, T exp, const T& mod) {
    T result = 1;
    if (base < 0) {
        throw std::runtime_error("cannot pow negative number");
    }
    if (exp < 0) {
        exp += base * (cln::floor1(abs(exp), base));
    }
    if (exp == -1 && gcd(base, mod) == 1) {
        exp = mod - 2;
    } else if (gcd(base, mod) != 1) {
        throw std::runtime_error("cannot find multiplicative inverse, gcd is not 1");
    }
    while (exp > 0) {
        if (mod(exp, 2) == 1) {
            result = (result * base);
        }
        base = cln::square(base);
        exp = cln::floor1(exp, 2);
    }
    return result;
}

}

#endif // HELPER_FUNCTIONS_H
