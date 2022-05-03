#include "bigint.h"
#include "auxiliary.h"
#include <iomanip>
#include <bitset>
/*
std::ostream& operator <<(std::ostream& output, const bigint& src) {
    if (src._sign == 0){
        output << "0x0";
        return output;
    }
    else if (src._sign == -1){
        output << '-';
    }
    output << "0x";
    for (int i = 0; i < src._current_size; ++i){
        if (src._number[i] != 0 || i == src._current_size - 1){
            output << std::setfill('0') << std::setw(8)
                   //<< std::bitset<32>(src._number[i]);
                      << std::hex << src._number[i];
        }
    }
    return output;
}
*/

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
    while (_src != 0) {
        result = char((_src % 10)._number[bigint::DEFAULT_SIZE -1] + 48) + result;
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
    return std::move(bigint(-first._sign, first._number, first._current_size));
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
        result = pad(result, 1);
        result[0] = carry;
        current_size++;
    }
    return std::move(result);
}

inline std::vector<uint> _sub(const std::vector<uint>& first, const std::vector<uint>& second, int& current_size, int min_size) {
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
    result = unpad(result, min_size);
    current_size = result.size();
    return std::move(result);
}

bigint operator+(const bigint& first, const bigint& second) {
    int current_size = std::max(first._current_size, second._current_size);
    //int min_size = std::min(first._current_size, second._current_size);
    std::vector<uint> result;

    if (first == 0){
        return std::move(second);
    }
    else if (second == 0){
        return std::move(first);
    }

    int pad_first = (second._current_size - first._current_size) * (second._current_size - first._current_size > 0);
    int pad_second = (first._current_size - second._current_size) * (first._current_size - second._current_size > 0);

    bigint first_t = bigint(first._sign,
                            pad(first._number, pad_first),
                            second._current_size);

    bigint second_t = bigint(second._sign,
                             pad(second._number, pad_second),
                             first._current_size);

    if (first_t > 0 && second_t > 0){
        result = _add(first_t._number, second_t._number, current_size);
        return std::move(bigint(1, result, current_size));
    }
    if (first_t > 0 && second_t < 0){
        if (abs(first_t) == abs(second_t)){
            return std::move(bigint(0));
        }
        if (abs(first_t) > abs(second_t)){
            result = _sub(first_t._number, second_t._number, current_size, bigint::DEFAULT_SIZE);
            return std::move(bigint(1, result, current_size));
        }
        else if (abs(first_t) < abs(second_t)){
            result = _sub(second_t._number, first_t._number, current_size, bigint::DEFAULT_SIZE);
            return std::move(bigint(-1, result, current_size));
        }
    }
    if (first_t < 0 && second_t > 0){
        if (abs(first_t) == abs(second_t)){
            return std::move(bigint(0));
        }
        if (abs(first_t) > abs(second_t)){
            result = _sub(first_t._number, second_t._number, current_size, bigint::DEFAULT_SIZE);
            return std::move(bigint(-1, result, current_size));
        }
        if (abs(first_t) < abs(second_t)){
            result = _sub(second_t._number, first_t._number, current_size, bigint::DEFAULT_SIZE);
            return std::move(bigint(1, result, current_size));
        }
    }
    else {
        result = _add(first_t._number, second_t._number, current_size);
        return std::move(bigint(-1, result, current_size));
    }
    return -1;
}

bigint operator-(const bigint& first, const bigint& second){
    return std::move(first + (-second));
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
    std::vector<uint> carry_number(number.size());
    uint tmp = 0;
    size_t tmp_t = 0;
    for (int i = idx; i > 0; --i){
        tmp = number[i] + carry;
        tmp_t = (size_t) number[i] + carry;
        number[i] = tmp;
        carry = tmp_t - tmp;
    }
    if (carry > 0){
        number = pad(number, 1);
        number[0] = carry;
    }
}
/*
 * For now, let it keep as it is. For cryptographic purposes, we do not use any
 * huge numbers (1e500 and bigger), I geuss. If I have any performance issues, I will
 * implement Karatsuba algorithm. But for now, I do not want any additional pain in the ass.
 */
bigint operator*(const bigint& first, const bigint& second){
    signed sign = sgn(first._sign * second._sign);
    int current_size = first._current_size + second._current_size + 2;
    std::vector<uint> result(current_size, 0);
    uint log = (bigint::_base_log + 1);
    if (first == 0 || second == 0){
        return bigint(0);
    }
    if (first == 1){
        return second;
    }
    if (second == 1){
        return first;
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
    result = unpad(result, bigint::DEFAULT_SIZE);
    return std::move(bigint(sign, result, result.size()));
}

bigint bigint::operator*=(const bigint& second){
    *this = *this * second;
    return *this;
}

bigint operator/(const bigint& first, const bigint& second){
    bigint first_t = abs(first);
    bigint second_t = abs(second);
    if (first == 0){
        return bigint(0);
    }
    if (second == 0){
        throw std::runtime_error("division by zero");
    }
    if (first_t < second_t){
        return bigint(0);
    }
    signed sign = sgn(first._sign * second._sign);
    bigint divident, quotient, remainder;
    for (int i = 0; i < first_t._current_size; ++i){
        divident = divident * bigint::__base + first_t._number[i];
        uint lo = 0, hi = uint(-1);
        uint be = hi / 2;
        remainder = divident - second_t * be;
        while ((remainder < 0 || remainder >= second_t) && hi - lo != 1){
            if (remainder < 0){
                hi = be;
            }
            else {
                lo = be;
            }
            be = lo + (hi - lo)/2;
            remainder = divident - second_t * be;
        }
        quotient = quotient * bigint::__base + be;
        divident = remainder;
    }
    quotient._sign = sign;
    return std::move(quotient);
}

bigint bigint::operator/=(const bigint& second){
    *this = *this / second;
    return *this;
}

bigint operator%(const bigint& first, const bigint& second){
    /*
    bigint tmp = (first / second) * second;
    return std::move(first - tmp);
    */

    if (first == 0){
        return bigint(0);
    }
    if (second == 0){
        throw std::runtime_error("division by zero");
    }
    if (first < second){
        return std::move(first);
    }
    bigint divident, remainder;
    for (int i = 0; i < first._current_size; ++i){
        divident = divident * bigint::__base + first._number[i];
        uint lo = 0, hi = uint(-1);
        uint be = hi / 2;
        remainder = divident - second * be;
        while ((remainder < 0 || remainder >= second) && hi - lo != 1){
            if (remainder < 0){
                hi = be;
            }
            else {
                lo = be;
            }
            be = lo + (hi - lo) / 2;
            remainder = divident - second * be;
        }
        divident = remainder;
    }
    return std::move(remainder);
}

bigint bigint::operator%=(const bigint& second){
    *this = *this % second;
    return *this;
}

bool odd(const bigint& src) {
    return src._number[src._current_size - 1] & 1;
}
