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
    return _a + _b;
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
    return result;
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
            result = std::move(mul_mod(result, _base, mod));
        }
        _base = std::move(mul_mod(_base, _base, mod));
        _exp /= 2;
    }
    return result % mod;
}

inline bool biginteger::miller_rabin(const bigint& d, const bigint& n, size_t bits) {
    bigint _d = d;
    bigint a = 2 + biginteger::random(bits) % (n - 4);
    bigint x = std::move(pow(a, d, n));
    if (x == 1 || x == n - 1) {
        return true;
    }

    while (_d != n - 1) {
        x = std::move(mul_mod(x, x, n));
        _d *= 2;
        if (x == 1) {
            return false;
        }
        if (x == n - 1) {
            return true;
        }
    }

    return false;
}

bigint biginteger::factorial(const bigint& n) {
    bigint res = 1;
    for (bigint i = 1; i <= n; ++i){
        res *= i;
    }
    return res;
}

bool biginteger::is_prime(const bigint& number, size_t k, size_t bits) {
    if (number <= 1 || number == 4) {
        return false;
    }
    if (number == 2 || number == 3) {
        return true;
    }
    bigint d = number - 1;
    while (d % 2 == 0) {
        d /= 2;
    }

    for (int i = 0; i < k; ++i) {
        if (!miller_rabin(d, number, bits)){
            return false;
        }
    }
    return true;
}

bool biginteger::is_prime(const bigint& number, size_t k) {
    return is_prime(number, k, 32);
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

bigint biginteger::random() {
    const size_t DEFAULT_SIZE = 32;
    return random(DEFAULT_SIZE);
}

bigint biginteger::get_prime(size_t bits) {
    bigint result = biginteger::random(bits);
    //result += (result % 2 == 0);
    while (!is_prime(result, 50, bits)) {
        result = biginteger::random(bits);
    }
    return result;
}
