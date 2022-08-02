#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <cln/integer.h>
#include <cln/real.h>
#include <set>
#include <vector>
#include <map>

namespace anemoi {

const cln::cl_I MINUS_ONE = cln::cl_I(-1);

cln::cl_I pow(cln::cl_I base, cln::cl_I exp) {
    cln::cl_I result = 1;
    if (base < 0) {
        throw std::runtime_error("cannot pow negative number");
    }
    if (exp < 0) {
        exp += base * (cln::floor1(abs(exp), base));
    }
    while (exp > 0) {
        if (mod(exp, 2) == 1) {
            result = (result * base);
        }
        base = cln::square(base);
        exp = cln::floor1(exp, 2);
    }
    return result;
}

cln::cl_I pow(cln::cl_I base, cln::cl_I exp, const cln::cl_I& mod) {
    cln::cl_I result = 1;
    if (base < 0) {
        throw std::runtime_error("Anemoi error: cannot pow negative number");
    }
    if (exp < 0 && cln::gcd(base, mod) == 1) {
        exp = cln::abs(exp) * (mod - 2);
    } else if (cln::gcd(base, mod) != 1) {
        throw std::runtime_error("Anemoi error: cannot find multiplicative inverse, gcd is not 1");
    }
    while (exp > 0) {
        if (cln::mod(exp, 2) == 1) {
            result = cln::mod((result * base), mod);
        }
        base = cln::mod(cln::square(base), mod);
        exp = cln::floor1(exp, 2);
    }
    return result;
}


std::set<cln::cl_I> slow_factorize(cln::cl_I number) {
    std::set<cln::cl_I> factors;
    cln::cl_I i = 1;
    while (cln::square(i) <= number) {
        if (cln::mod(number, i) == 0) {
            factors.insert(i);
            factors.insert(cln::floor1(number, i));
        }
        i++;
    }
    return factors;
}

cln::cl_I ord(cln::cl_I element, cln::cl_I mod, std::set<cln::cl_I>(*factorize)(cln::cl_I number)) {
    std::set<cln::cl_I> factors = factorize(mod - 1);
    for (auto& exp : factors) {
        if (pow(element, exp, mod) == 1) {
            return exp;
        }
    }
    return -1;
}

cln::cl_I shanks_babystep_giantstep(cln::cl_I g, cln::cl_I h, cln::cl_I p) {
    //Ceiling for computing map values
    cln::cl_I n = 1 + cln::round1(cln::sqrt(ord(g, p, anemoi::slow_factorize)));

    long long t = cln::cl_I_to_long(n);

    std::map<cln::cl_I, cln::cl_I> lookup;

    //Baby steps
    for (cln::cl_I i = 0; i < n; ++i) {
        lookup[anemoi::pow(g, i, p)] = i + 1;
    }

    //Inverse computation for the sake of optimistation
    cln::cl_I inv = anemoi::pow(g, -n, p);
    t = cln::cl_I_to_long(inv);

    //Giant step
    for (cln::cl_I i = 0; i < n; ++i) {
        auto tmp = cln::mod(h * anemoi::pow(inv, i, p), p);

        if (lookup[tmp] > 0) {
            return lookup[tmp] - 1 + i * n;
        }
    }

    //No solutions found
    return -1;
}

}

#endif // HELPER_FUNCTIONS_H
