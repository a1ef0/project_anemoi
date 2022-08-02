#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <cln/integer.h>
#include <cln/real.h>
#include <set>
#include <map>

/**
 * The namespace itself contains all needed primitives & functions and acts like the standalone library.
 */
namespace anemoi {

const cln::cl_I MINUS_ONE = cln::cl_I(-1);

/**
 * @brief pow   - performs the exponentiation
 * @param base  - integer base for exponentiation
 * @param exp   - integer exponent for exponentiation
 * @return base ^ exp (not XOR, but exponentiation)
 */
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

/**
 * @brief pow   - performs the exponentiation given modulo mod
 * @param base  - integer base for exponentiation
 * @param exp   - integer exponent for exponentiation
 * @param p     - modulo, on which the operation is performed
 * @return base ^ exp (mod p)
 */
cln::cl_I pow(cln::cl_I base, cln::cl_I exp, const cln::cl_I& p) {
    cln::cl_I result = 1;
    if (base < 0) {
        throw std::runtime_error("Anemoi error: cannot pow negative number");
    }
    if (exp < 0 && cln::gcd(base, p) == 1) {
        exp = cln::abs(exp) * (p - 2);
    } else if (cln::gcd(base, p) != 1) {
        throw std::runtime_error("Anemoi error: cannot find multiplicative inverse, gcd is not 1");
    }
    while (exp > 0) {
        if (cln::mod(exp, 2) == 1) {
            result = cln::mod((result * base), p);
        }
        base = cln::mod(cln::square(base), p);
        exp = cln::floor1(exp, 2);
    }
    return result;
}

/**
 * @brief slow_factorize    - performs integer factorisation on a given positive number
 * @param number            - number to be factored
 * @return set of factors
 */
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

/**
 * @brief ord       - returns order of element in given group (in this case it is F^*_p)
 * @param element   - element to be found order of
 * @param mod       - modulo of given Field
 * @return order of element
 */
cln::cl_I ord(cln::cl_I element, cln::cl_I mod, std::set<cln::cl_I>(*factorize)(cln::cl_I number)) {
    std::set<cln::cl_I> factors = factorize(mod - 1);
    for (auto& exp : factors) {
        if (pow(element, exp, mod) == 1) {
            return exp;
        }
    }
    return -1;
}

/**
 * @brief shanks_babystep_giantstep - solves DLP for a given base, modulus and logarithm.
 * @param g                         - base
 * @param h                         - logarithm
 * @param p                         - modulus
 * @return integer solution to DLP
 */
cln::cl_I shanks_babystep_giantstep(cln::cl_I g, cln::cl_I h, cln::cl_I p) {
    //Ceiling for computing map values
    cln::cl_I n = 1 + cln::round1(cln::sqrt(ord(g, p, anemoi::slow_factorize)));
    std::map<cln::cl_I, cln::cl_I> lookup;

    //Baby steps
    for (cln::cl_I i = 0; i < n; ++i) {
        lookup[anemoi::pow(g, i, p)] = i + 1;
    }

    //Inverse computation for the sake of optimistation
    cln::cl_I inv = anemoi::pow(g, -n, p);

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
