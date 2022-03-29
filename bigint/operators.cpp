#include "bigint.h"
#include "auxillary.h"
#include <iomanip>
std::ostream& operator <<(std::ostream& output, const bigint& src) {
    if (src._sign == 0){
        output << "0x";
        return output;
    }
    else if (src._sign == -1){
        output << '-';
    }
    output << "0x";
    for (int i = 0; i < src._current_size; ++i){
        if (src._number[i] != 0 || i == src._current_size - 1){
            output << std::setfill('0') << std::setw(8)
                   << std::hex << src._number[i];
        }
    }
    return output;
}

bool operator>=(const bigint& first, const bigint& second){
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

bool operator==(const bigint& first, const bigint& second){
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

bool operator!=(const bigint& first, const bigint& second){
    return !(first == second);
}

bool operator<=(const bigint& first, const bigint& second){
    return (!(first >= second) || first == second);
}

bool operator<(const bigint& first, const bigint& second){
    return !(first >= second);
}

bool operator>(const bigint& first, const bigint& second){
    return (first >= second && first != second);
}

bigint operator ""_bi(const char* src){
    return bigint(std::string(src));
}

bigint operator-(const bigint& first){
    return bigint(-first._sign, first._number, first._current_size);
}

bigint operator+(const bigint& first){
    return first;
}

inline std::vector<uint> _add(const std::vector<uint>& first, const std::vector<uint>& second, int& current_size){
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
    return result;
}

inline std::vector<uint> _sub(const std::vector<uint>& first, const std::vector<uint>& second, int& current_size, int min_size){
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
    return result;
}

bigint operator+(const bigint& first, const bigint& second){
    int current_size = std::max(first._current_size, second._current_size);
    //int min_size = std::min(first._current_size, second._current_size);
    std::vector<uint> result;

    if (first == 0){
        return second;
    }
    else if (second == 0){
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

    if (first_t > 0 && second_t > 0){
        result = _add(first_t._number, second_t._number, current_size);
        return bigint(1, result, current_size);
    }
    if (first_t > 0 && second_t < 0){
        if (abs(first_t) == abs(second_t)){
            return bigint(0);
        }
        if (abs(first_t) > abs(second_t)){
            result = _sub(first_t._number, second_t._number, current_size, bigint::DEFAULT_SIZE);
            return bigint(1, result, current_size);
        }
        else if (abs(first_t) < abs(second_t)){
            result = _sub(second_t._number, first_t._number, current_size, bigint::DEFAULT_SIZE);
            return bigint(-1, result, current_size);
        }
    }
    if (first_t < 0 && second_t > 0){
        if (abs(first_t) == abs(second_t)){
            return bigint(0);
        }
        if (abs(first_t) > abs(second_t)){
            result = _sub(first_t._number, second_t._number, current_size, bigint::DEFAULT_SIZE);
            return bigint(-1, result, current_size);
        }
        if (abs(first_t) < abs(second_t)){
            result = _sub(second_t._number, first_t._number, current_size, bigint::DEFAULT_SIZE);
            return bigint(1, result, current_size);
        }
    }
    else {
        result = _add(first_t._number, second_t._number, current_size);
        return bigint(-1, result, current_size);
    }
    //it should not reach this statement
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
    return bigint(sign, result, result.size());
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
    if (first < second){
        return bigint(0);
    }
    signed sign = sgn(first._sign * second._sign);
    bigint divident, quotient, tmp;
    for (int i = 0; i < first._current_size; ++i){
        divident = divident * bigint::__base + first._number[i];
        uint lo = 0, hi = uint(-1);
        uint be = hi / 2;
        tmp = divident - second * be;
        while ((tmp < 0 || tmp >= second) && hi - lo != 1){
            if (tmp < 0){
                hi = be;
            }
            else {
                lo = be;
            }
            be = lo + (hi - lo)/2;
            tmp = divident - second * be;
        }
        quotient = quotient * bigint::__base + be;
        divident = tmp;
    }
    quotient._sign = sign;
    return quotient;
}

bigint bigint::operator/=(const bigint& second){
    *this = *this / second;
    return *this;
}

bigint bigint::operator%(const bigint & second){
    bigint tmp = (*this / second) * second;
    return *this - tmp;
}

bigint bigint::operator%=(const bigint& second){
    *this = *this % second;
    return *this;
}
