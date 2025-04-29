#ifndef PSEUDORANDOM_GENERATOR_H
#define PSEUDORANDOM_GENERATOR_H

#include <iostream>
#include <cmath>

#include <gmpxx.h>


class PseudorandomGenerator
{
public:
    PseudorandomGenerator(uint32_t seed);
    ~PseudorandomGenerator() = default;

    mpz_class park_miller(int num_bits);
    mpz_class xorshift(int num_bits);

    void set_seed(uint32_t new_seed);
private:
    // Atributos do Park-Miller
    const uint32_t a = 16807;        // Constante multiplicadora; um número primo grande
    const uint32_t m = pow(2, 31)-1; // Módulo -> (2^31)-1
    uint32_t pm_seed;                // Semente/Estado
    
    // Atributos do Xorshift
    uint32_t xs_seed;                // Semente/Estado
};

#endif
