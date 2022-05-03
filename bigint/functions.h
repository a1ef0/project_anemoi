#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "bigint.h"

namespace biginteger {

    bigint pow(const bigint&, const bigint&);
    bigint pow(const bigint&, const bigint&, const bigint&);
    bigint gcd(const bigint&, const bigint&);
    bool miller_rabin(const bigint&, const bigint&);
    bool is_prime(const bigint&);
    bigint factorial(const bigint&);
    bigint random(size_t);
    bigint get_prime(size_t);
}
#endif // FUNCTIONS_H
