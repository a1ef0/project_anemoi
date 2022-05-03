#include "functions.h"
#include "auxiliary.h"

#include <random>

bigint biginteger::gcd(const bigint& a, const bigint& b) {
    bigint _a = a;
    bigint _b = b;
    while (_a != 0 && _b != 0){
        if (_a > _b){
            _a = _a % _b;
        }
        else{
            _b = _b % _a;
        }
    }
    return std::move(_a + _b);
}

bigint biginteger::pow(const bigint& base, const bigint& exp) {
    bigint result = 1;
    bigint _base = base;
    bigint _exp = exp;
    while (_exp > 0){
        if (_exp % 2 == 1){
            result *= _base;
        }
        _base *= _base;
        _exp /= 2;
    }
    return std::move(result);
}



bigint biginteger::pow(const bigint& base, const bigint& exp, const bigint& mod) {
    bigint result = 1;
    bigint _base = base;
    bigint _exp = exp;
    if (base < 0){
        throw std::runtime_error("cannot pow negative number");
    }
    if (exp < 0){
        _exp = _exp + base * (abs(_exp) / base);
    }
    if (exp == -1){
        _exp = mod - 2;
    }
    while (_exp > 0){
        if (_exp % 2 == 1){
            result = (result * _base) % mod;
        }
        _base = (_base * _base) % mod;
        _exp /= 2;
    }
    return std::move(result % mod);
}

bool biginteger::miller_rabin(const bigint& n, const bigint& a) {
    bigint _n = n;
    bigint _a = a;
    if (_n % 2 == 0){
        return false;
    }
    else {
        bigint k;
        bigint q = _n - 1;
        while (q % 2 == 0){
            q = q / 2;
            k++;
        }
        _a = biginteger::pow(_a, q, _n);
        if (_a % _n == 1)
            return true;

        for (bigint i = 0; i < k; ++i){
            if (_a % _n == _n - 1){
                return true;
            }
            mul_mod(_a, _a, _n);
        }
        return false;
    }
}

bigint biginteger::factorial(const bigint& n) {
    bigint res = 1;
    for (bigint i = 1; i <= n; ++i){
        res *= i;
    }
    return res;
}

bool biginteger::is_prime(const bigint& number) {
    if (number < 2) {
        return false;
    }
    if (number == 2) {
        return true;
    }
    for (int i = 0; i < 100; ++i) {
        if (biginteger::gcd(number, i + 10) == 1) {
            if (biginteger::miller_rabin(number, i + 10) == false) {
                return false;
            }
        }
    }
    return true;
}

//TODO: somehow remove dependency on 32, but probably it will not be needed
bigint biginteger::random(size_t bits) {
    bigint result;
    std::random_device engine;
    size_t uint_bits = 32;
    if (uint residue = bits % uint_bits){
        result = uint(engine()) >> (uint_bits - residue);
    }
    uint digits = bits / uint_bits;
    for (size_t i = 0; i < digits; ++i) {
        result *= ((size_t) 1 << uint_bits);
        result += uint(engine());
    }
    return result;
}

bigint biginteger::get_prime(size_t bits) {
    bigint result = biginteger::random(bits);
    while (!is_prime(result)) {
        result = biginteger::random(bits);
    }
    return result;
}
