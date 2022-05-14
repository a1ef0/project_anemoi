#include "bigint.h"
#include "auxiliary.h"
#include <iomanip>
#include <bitset>

std::ostream& operator <<(std::ostream& output, const bigint& src) {
    if (src._sign == 0){
        output << "0";
        return output;
    }
    if (src._sign == -1){
        output << '-';
    }
    std::string result;
    bigint _src = src;
    while (_src != bigint::zero) {
        result = char((_src % 10)._number[bigint::DEFAULT_SIZE - 1] + 48) + result;
        _src /= 10;
    }
    output << result;
    return output;
}

bool operator>=(const bigint& first, const bigint& second) {
    if (first._sign < second._sign || first._current_size < second._current_size){
        return false;
    }
    if (first._current_size > second._current_size){
        return true;
    }
    for (int i = 0; i < first._current_size; ++i){
        if (first._number[i] > second._number[i]){
            return true;
        }
        if (first._number[i] < second._number[i]){
            return false;
        }
    }
    return true;
}

bool operator==(const bigint& first, const bigint& second) {
    if (first._sign != second._sign || first._current_size != second._current_size){
        return false;
    }
    for (int i = 0; i < first._current_size; ++i){
        if (first._number[i] != second._number[i]){
            return false;
        }
    }
    return true;
}

bool operator!=(const bigint& first, const bigint& second) {
    return !(first == second);
}

bool operator<=(const bigint& first, const bigint& second) {
    return (!(first >= second) || first == second);
}

bool operator<(const bigint& first, const bigint& second) {
    return !(first >= second);
}

bool operator>(const bigint& first, const bigint& second) {
    return (first >= second && first != second);
}

bigint operator ""_bi(const char* src) {
    return bigint(std::string(src));
}

bigint operator-(const bigint& first) {
    return bigint(-first._sign, first._number, first._current_size);
}

bigint operator+(const bigint& first) {
    return first;
}

inline std::vector<uint> _add(const std::vector<uint>& first, const std::vector<uint>& second, int& current_size) {
    std::vector<uint> result(current_size);
    uint tmp = 0;
    size_t tmp_t = 0, carry = 0;
    for (int i = current_size - 1; i >= 0; --i){
        tmp = first[i] + second[i] + carry;
        tmp_t = first[i] + second[i] + carry;
        result[i] = tmp;
        carry = tmp_t - (size_t) tmp;
    }
    if (carry > 0){
        result = std::move(pad(result, 1));
        result[0] = carry;
        current_size++;
    }
    return result;
}

std::vector<uint> _sub(const std::vector<uint>& first, const std::vector<uint>& second, int& current_size, int min_size) {
    std::vector<uint> result(current_size);
    std::vector<uint> first_t = first;

    for (int i = current_size - 1; i > 0; --i){
        if (first_t[i] >= second[i]){
            result[i] = first_t[i] - second[i];
        }
        else {
            first_t[i-1]--;
            result[i] = uint(-1) - second[i] + first_t[i] + 1;
        }
    }
    result = std::move(unpad(result, min_size));
    current_size = result.size();
    return result;
}

bigint operator+(const bigint& first, const bigint& second) {
    int current_size = std::max(first._current_size, second._current_size);
    std::vector<uint> result;

    if (first == bigint::zero){
        return second;
    }
    else if (second == bigint::zero){
        return first;
    }

    int pad_first = (second._current_size - first._current_size) * (second._current_size - first._current_size > 0);
    int pad_second = (first._current_size - second._current_size) * (first._current_size - second._current_size > 0);

    bigint first_t = bigint(first._sign,
                            pad(first._number, pad_first),
                            second._current_size);

    bigint second_t = bigint(second._sign,
                             pad(second._number, pad_second),
                             first._current_size);

    if (first_t > bigint::zero && second_t > bigint::zero){
        result = std::move(_add(first_t._number, second_t._number, current_size));
        return bigint(1, result, current_size);
    }
    if (first_t > bigint::zero && second_t < bigint::zero){
        if (abs(first_t) == abs(second_t)){
            return bigint::zero;
        }
        if (abs(first_t) > abs(second_t)){
            result = std::move(_sub(first_t._number, second_t._number, current_size, bigint::DEFAULT_SIZE));
            return bigint(1, result, current_size);
        }
        else if (abs(first_t) < abs(second_t)){
            result = std::move(_sub(second_t._number, first_t._number, current_size, bigint::DEFAULT_SIZE));
            return bigint(-1, result, current_size);
        }
    }
    if (first_t < bigint::zero && second_t > bigint::zero){
        if (abs(first_t) == abs(second_t)){
            return bigint::zero;
        }
        if (abs(first_t) > abs(second_t)){
            result = std::move(_sub(first_t._number, second_t._number, current_size, bigint::DEFAULT_SIZE));
            return bigint(-1, result, current_size);
        }
        if (abs(first_t) < abs(second_t)){
            result = std::move(_sub(second_t._number, first_t._number, current_size, bigint::DEFAULT_SIZE));
            return bigint(1, result, current_size);
        }
    }
    else {
        result = std::move(_add(first_t._number, second_t._number, current_size));
        return bigint(-1, result, current_size);
    }
    return -1;
}

bigint operator-(const bigint& first, const bigint& second){
    return first + (-second);
}

bigint& bigint::operator=(const bigint& src){
    this->_sign = src._sign;
    this->_number = src._number;
    this->_current_size = src._current_size;
    return *this;
}


bigint& bigint::operator=(const bigint&& src){
    this->_sign = src._sign;
    this->_number = std::move(src._number);
    this->_current_size = src._current_size;
    return *this;
}


bigint& bigint::operator++(){
    *this = *this + 1;
    return *this;
}

bigint bigint::operator++(int){
    bigint tmp = *this;
    ++*this;
    return tmp;
}

bigint& bigint::operator--(){
    *this = *this - 1;
    return *this;
}

bigint bigint::operator--(int){
    bigint tmp = *this;
    --*this;
    return tmp;
}

bigint bigint::operator+=(const bigint& term){
    *this = *this + term;
    return *this;
}

bigint bigint::operator-=(const bigint& term){
    *this = *this - term;
    return *this;
}

void _add_carry(std::vector<uint>& number, uint carry, int idx){
    uint tmp = 0;
    size_t tmp_t = 0;
    for (int i = idx; i > 0; --i){
        tmp = number[i] + carry;
        tmp_t = (size_t) number[i] + carry;
        number[i] = tmp;
        carry = tmp_t - tmp;
    }
    if (carry > 0){
        number = std::move(pad(number, 1));
        number[0] = carry;
    }
}
//TODO: all int -> size_t
/*
 * For now, let it keep as it is. For cryptographic purposes, we do not use any
 * huge numbers (1e500 and bigger), I geuss. If I have any performance issues, I will
 * implement Karatsuba algorithm. But for now, I do not want any additional pain in the ass.
 */
bigint operator*(const bigint& first, const bigint& second){
    signed sign = sgn(first._sign * second._sign);
    size_t current_size = first._current_size + second._current_size + 2;
    std::vector<uint> result(current_size, 0);
    uint log = (bigint::_base_log + 1);
    if (first == 0 || second == 0) {
        return 0;
    }
    if (first == 1) {
        return second;
    }
    if (second == 1) {
        return first;
    }
    if (second == 2) {
        uint bit = 0, _bit = 0;
        bigint first_t = first;
        for (int i = first_t._current_size - 1; i >= 0; --i) {
            if (i == 0) {
                _bit = (first_t._number[i] & 0x80000000) > 0;
                if ((first_t._number[i] << 1) < first_t._number[i]) {
                    first_t._number[i] = first_t._number[i] << 1;
                    first_t._number[i] = first_t._number[i] | bit;
                    first_t._number = std::move(pad(first_t._number, 1));
                    first_t._number[0] = _bit;
                    return first_t;
                } else {
                    first_t._number[i] = first_t._number[i] << 1;
                    first_t._number[i] = first_t._number[i] | bit;
                    return first_t;
                }
            }
            _bit = (first_t._number[i] & 0x80000000) > 0;
            first_t._number[i] = first_t._number[i] << 1;
            first_t._number[i] = first_t._number[i] | bit;
            bit = _bit;
        }
        return first_t;
    }
    size_t carry;
    uint lo, hi;
    for (int i = first._current_size - 1, ii = 0; i >= 0; --i, ++ii){
        uint cur = first._number[i];
        for (int j = second._current_size - 1, jj = 0; j >= 0; --j, ++jj){
            lo = cur * second._number[j];
            hi = (((size_t) cur * second._number[j]) >> log);
            uint tmp = result[current_size - ii - jj - 1];
            result[current_size - ii - jj - 1] = tmp + lo;
            carry = (((size_t) tmp + lo) >> log) + hi;
            _add_carry(result, carry, current_size - ii - jj - 2);
        }
    }
    result = std::move(unpad(result, bigint::DEFAULT_SIZE));
    return bigint(sign, result, result.size());
}

bigint bigint::operator*=(const bigint& second){
    *this = *this * second;
    return *this;
}

bigint operator/(const bigint& first, const bigint& second) {
    bigint dividend = abs(first);
    bigint divisor = abs(second);
    if (second == 2) {
        int bit = 0, _bit = 0;
        for (int i = 0; i < dividend._current_size; ++i) {
            if (i == dividend._current_size - 1) {
                if (dividend == 1) {
                    dividend._number[i] = 0;
                    dividend._sign = 0;
                    continue;
                }
            }
            _bit = dividend._number[i] & 1;
            dividend._number[i] = dividend._number[i] >> 1;
            dividend._number[i] = dividend._number[i] | (bit << 31);
            bit = _bit;
        }
        return dividend;
    }
    if (dividend < divisor || first == 0){
        return bigint(0);
    }
    if (second == 0){
        throw std::runtime_error("division by zero");
    }
    signed sign = sgn(first._sign * second._sign);
    bigint quotient, remainder;
    size_t n = number_of_bits(first);
    for (int i = n - 1; i >= 0; --i) {
        remainder = remainder << 1;
        remainder = remainder | ((dividend & (1_bi << i)) >> i);
        if (remainder >= divisor) {
            remainder = remainder - divisor;
            quotient = quotient | (1_bi << i);
        }
    }
    quotient._sign = sign;
    return quotient;
}

bigint bigint::operator/=(const bigint& second){
    *this = *this / second;
    return *this;
}

bigint operator%(const bigint& first, const bigint& second){
    if (second == 2) {
        return first._number[first._current_size - 1] & 1;
    }
    if (first == 0){
        return bigint(0);
    }
    if (second == 0){
        throw std::runtime_error("division by zero");
    }
    if (first < second){
        return first;
    }
    return first - (first / second) * second;
}

bigint bigint::operator%=(const bigint& second){
    *this = *this % second;
    return *this;
}

bigint operator|(const bigint& first, const bigint& second) {
    std::vector<uint> result;
    bigint first_t = first;
    bigint second_t = second;
    if (first_t._current_size < second_t._current_size) {
        std::swap(first_t, second_t);
    }
    size_t n = first_t._current_size - second_t._current_size;
    second_t._number = std::move(pad(second_t._number, n));
    n = first_t._current_size;
    for (size_t i = 0; i < n; ++i) {
        result.push_back(first_t._number[i] | second_t._number[i]);
    }
    return bigint(1, result, result.size());
}

bigint operator&(const bigint& first, const bigint& second) {
    std::vector<uint> result;
    bigint first_t = first;
    bigint second_t = second;
    if (first_t._current_size < second_t._current_size) {
        std::swap(first_t, second_t);
    }
    size_t n = first_t._current_size - second_t._current_size;
    second_t._number = std::move(pad(second_t._number, n));
    n = first_t._current_size;
    for (size_t i = 0; i < n; ++i) {
        result.push_back(first_t._number[i] & second_t._number[i]);
    }
    result = std::move(unpad(result, 2));
    return bigint(1, result, result.size());
}

bigint operator<<(const bigint& number, size_t n) {
    bigint _number = number;
    for (size_t i = 0; i < n; ++i) {
        _number *= 2;
    }
    return _number;
}

bigint operator>>(const bigint& number, size_t n) {
    bigint _number = number;
    for (size_t i = 0; i < n; ++i) {
        _number /= 2;
    }
    return _number;
}

bigint bigint::operator |=(const bigint& second) {
    *this = *this | second;
    return *this;
}

bigint bigint::operator &=(const bigint& second) {
    *this = *this & second;
    return *this;
}

bigint bigint::operator <<=(size_t n) {
    *this = *this << n;
    return *this;
}

bigint bigint::operator >>=(size_t n) {
    *this = *this >> n;
    return *this;
}
//TODO: переписать на <<
