#ifndef BIGINT_H
#define BIGINT_H
//TODO: make _base, _base_log and DEFAULT_SIZE static not to confuse myself and others
#include <iostream>
#include <vector>

class bigint{
private:
    signed _sign;
    std::vector<uint> _number;
    const uint _base = (1 << 31);
    const size_t __base = (size_t) 1 << 32;
    const int _base_log = 31;
    const int DEFAULT_SIZE = 16;
    int _current_size;
    bigint(signed sign, std::vector<uint> number, int current_size);
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
    bigint operator%(const bigint&);
    bigint operator+=(const bigint&);
    bigint operator-=(const bigint&);
    bigint operator*=(const bigint&);
    bigint operator/=(const bigint&);
    bigint operator%=(const bigint&);
    bigint& operator=(const bigint&);
    bigint& operator++();
    bigint operator++(int);
    bigint& operator--();
    bigint operator--(int);
};
bigint operator "" _bi (const char* src);

#endif // BIGINT_H
