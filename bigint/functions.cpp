#include "functions.h"
#include "auxillary.h"

bigint biginteger::gcd(bigint a, bigint b){
    while (a != 0 && b != 0){
        if (a > b){
            a = a % b;
        }
        else{
            b = b % a;
        }
    }
    return a+b;
}

bigint biginteger::pow(bigint base, bigint exp){
    bigint result = 1;
    while (exp > 0){
        if (exp % 2 == 1){
            result *= base;
        }
        base *= base;
        exp /= 2;
    }
    return result;
}

bigint biginteger::pow(bigint base, bigint exp, bigint mod){
    bigint result = 1;
    if (base < 0){
        throw std::runtime_error("cannot pow negative number");
    }
    if (exp < 0){
        exp = exp + base * (abs(exp) / base);
    }
    if (exp == -1){
        exp = mod - 2;
    }
    while (exp > 0){
        if (exp % 2 == 1){
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result % mod;
}

bool biginteger::miller_rabin(bigint& n, bigint& a){
    if (n % 2 == 0 || gcd(n, a) > 1){
        return false;
    }
    else {
        bigint k = 0;
        bigint q = n - 1;
        while (1){
            if (q % 2 == 0){
                q = q / 2;
                k++;
            }
            else break;
        }
        a = biginteger::pow(a, q, n);

        if (a % n == 1)
            return true;

        for (bigint i = 0; i < k; ++i){
            if (a % n == n - 1){
                return true;
            }
            a = biginteger::pow(a, 2, n);
        }
        return false;
    }
    return false;
}
