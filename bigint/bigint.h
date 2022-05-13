#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <vector>
//TODO: probably add bigint::Zero, bigint::One, bigint::Two

using uint = unsigned int;

class bigint {
private:
    signed _sign;
    std::vector<uint> _number;
    static const int _base_log = 31;
    static constexpr uint _base = (1 << _base_log);
    static const int DEFAULT_SIZE = 2;
    int _current_size;
    bigint(signed sign, std::vector<uint> number, int current_size);
    static constexpr size_t __base = (size_t) 1 << (_base_log + 1);
public:
    bigint();
    bigint(long long);
    bigint(const std::string&);
    bigint(const bigint&);
    bigint(bigint&&);
    friend std::ostream& operator<<(std::ostream &, const bigint&);
    friend bool operator>(const bigint&, const bigint&);
    friend bool operator>=(const bigint&, const bigint&);
    friend bool operator<(const bigint&, const bigint&);
    friend bool operator<=(const bigint&, const bigint&);
    friend bool operator==(const bigint&, const bigint&);
    friend bool operator!=(const bigint&, const bigint&);
    friend bigint operator+(const bigint&, const bigint&);
    friend bigint operator-(const bigint&, const bigint&);
    friend bigint operator*(const bigint&, const bigint&);
    friend bigint operator/(const bigint&, const bigint&);
    friend bigint operator-(const bigint&);
    friend bigint operator+(const bigint&);
    friend bigint operator%(const bigint&, const bigint&);
    friend bigint operator|(const bigint&, const bigint&);
    friend bigint operator&(const bigint&, const bigint&);
    friend bigint operator<<(const bigint&, size_t);
    friend bigint operator>>(const bigint&, size_t);
    bigint operator |=(const bigint&);
    bigint operator &=(const bigint&);
    bigint operator <<=(size_t);
    bigint operator >>=(size_t);
    bigint operator+=(const bigint&);
    bigint operator-=(const bigint&);
    bigint operator*=(const bigint&);
    bigint operator/=(const bigint&);
    bigint operator%=(const bigint&);
    bigint& operator=(const bigint&);
    bigint& operator=(const bigint&&);
    bigint& operator++();
    bigint operator++(int);
    bigint& operator--();
    bigint operator--(int);
};
bigint operator "" _bi (const char* src);

#endif // BIGINT_H
