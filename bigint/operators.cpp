#include "bigint.h"
#include "functions.h"

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
            output << std::hex << src._number[i];
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
//TODO: __add here correct constructor for std::string
bigint operator ""_bi(const char* src){
    return bigint(0);
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
    for (int i = current_size - 1; i > 0; --i){
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

inline std::vector<uint> sub(const std::vector<uint>& first, const std::vector<uint>& second, int& current_size, int min_size){
    std::vector<uint> result(current_size);
    std::vector<uint> first_t = first;

    for (int i = current_size - 1; i > 0; --i){
        if (first_t[i] > second[i]){
            result[i] = first_t[i] - second[i];
        }
        else {
            first_t[i-1]--;
            result[i] = (1 << 31) - second[i] + first_t[i];
        }
    }
    result = unpad(result, min_size);
    current_size = result.size();
    return result;
}

bigint operator+(const bigint& first, const bigint& second){
    int current_size = std::max(first._current_size, second._current_size);
    int min_size = std::min(first._current_size, second._current_size);
    std::vector<uint> result;
    if (first == 0){
        return second;
    }
    else if (second == 0){
        return first;
    }
    if (first._current_size == second._current_size){
        if (first > 0 && second > 0){
            result = _add(first._number, second._number, current_size);
            return bigint(1, result, current_size);
        }
        if (first > 0 && second < 0){
            if (abs(first) == abs(second)){
                return bigint(0);
            }
            if (abs(first) > abs(second)){
                result = sub(first._number, second._number, current_size, first.DEFAULT_SIZE);
                return bigint(1, result, current_size);
            }
            else if (abs(first) < abs(second)){
                result = sub(second._number, first._number, current_size, first.DEFAULT_SIZE);
                return bigint(-1, result, current_size);
            }
        }
        if (first < 0 && second > 0){
            if (abs(first) == abs(second)){
                return bigint(0);
            }
            if (abs(first) > abs(second)){
                result = sub(first._number, second._number, current_size, first.DEFAULT_SIZE);
                return bigint(-1, result, current_size);
            }
            if (abs(first) < abs(second)){
                result = sub(second._number, first._number, current_size, first.DEFAULT_SIZE);
                return bigint(1, result, current_size);
            }
        }
        else {
            result = _add(first._number, second._number, current_size);
            return bigint(-1, result, current_size);
        }
    }
}
