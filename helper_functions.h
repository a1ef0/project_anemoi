#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <cln/integer.h>

namespace anemoi {

static cln::cl_I MINUS_ONE = cln::cl_I(-1);

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
        throw std::runtime_error("Anemoi error: cannot pow negative number");
    }
    if (exp == MINUS_ONE && cln::gcd(base, mod) == 1) {
        exp = mod - 2;
    } else if (gcd(base, mod) != 1) {
        throw std::runtime_error("Anemoi error: cannot find multiplicative inverse, gcd is not 1");
    }
    if (exp < 0) {
        base = anemoi::pow(base, MINUS_ONE, mod);
    }
    while (exp > 0) {
        if (cln::mod(exp, 2) == 1) {
            result = cln::mod((result * base), mod);
        }
        base = cln::mod(cln::square(base), mod);
        exp = cln::floor1(exp, 2);
    }
    auto tmp = cl_I_to_long(result);
    return result;
}

}

#endif // HELPER_FUNCTIONS_H
