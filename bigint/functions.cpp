#include "functions.h"
#include "auxiliary.h"

#include <random>

bigint biginteger::gcd(const bigint& a, const bigint& b) {
    bigint _a = a;
    bigint _b = b;
    while (_a != bigint::zero && _b != bigint::zero){
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
    bigint result = bigint::two;
    bigint _base = base;
    bigint _exp = exp;
    while (_exp > bigint::zero){
        if (_exp % bigint::two == bigint::one){
            result *= _base;
        }
        _base *= _base;
        _exp /= bigint::two;
    }
    return result;
}



bigint biginteger::pow(const bigint& base, const bigint& exp, const bigint& mod) {
    bigint result = bigint::one;
    bigint _base = base;
    bigint _exp = exp;
    if (base < bigint::zero){
        throw std::runtime_error("cannot pow negative number");
    }
    if (exp < bigint::zero){
        _exp = _exp + base * (abs(_exp) / base);
    }
    if (exp == -1){
        _exp = mod - bigint::two;
    }
    while (_exp > bigint::zero){
        if (_exp % bigint::two == bigint::one){
            result = std::move(mul_mod(result, _base, mod));
        }
        _base = std::move(mul_mod(_base, _base, mod));
        _exp /= bigint::two;
    }
    return result % mod;
}

inline bool biginteger::miller_rabin(const bigint& d, const bigint& n, size_t bits) {
    bigint _d = d;
    bigint a = bigint::two + biginteger::random(bits) % (n - 4);
    bigint x = std::move(pow(a, d, n));
    if (x == bigint::one || x == n - bigint::one) {
        return true;
    }

    while (_d != n - bigint::one) {
        x = std::move(mul_mod(x, x, n));
        _d = _d * bigint::two;
        if (x == bigint::one) {
            return false;
        }
        if (x == n - bigint::one) {
            return true;
        }
    }

    return false;
}

bigint biginteger::factorial(const bigint& n) {
    bigint res = bigint::one;
    for (bigint i = bigint::one; i <= n; ++i){
        res *= i;
    }
    return res;
}

bool biginteger::is_prime(const bigint& number, size_t k, size_t bits) {
    if (number <= bigint::one || number == 4) {
        return false;
    }
    if (number == bigint::two || number == 3) {
        return true;
    }
    bigint d = number - bigint::one;
    while (d % bigint::two == bigint::zero) {
        d /= bigint::two;
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
    while (!is_prime(result, 50, bits)) {
        result = biginteger::random(bits);
    }
    return result;
}
