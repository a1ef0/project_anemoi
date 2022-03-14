#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <iostream>
#include <vector>

class bigint{
private:
    signed _sign;
    std::vector<size_t> _number;
    const int _base = 10;
    const int _base_log = 1;
    const int DEFAULT_SIZE = 10;
    int current_size;
public:
    bigint();
    bigint(int src);
    bigint(short src);
    bigint(char src);
    bigint(long long src);
    bigint(size_t src);
    bigint(const std::string& src);
    friend std::ostream& operator<<(std::ostream &output, const bigint& src);
};

#endif // BIG_INTEGER_H
