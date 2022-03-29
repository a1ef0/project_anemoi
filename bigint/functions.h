#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "bigint.h"

namespace biginteger {

    bigint pow(bigint, bigint);
    bigint pow(bigint, bigint, bigint);
    bigint gcd(bigint, bigint);
    bool miller_rabin(bigint&, bigint&);
}
#endif // FUNCTIONS_H
