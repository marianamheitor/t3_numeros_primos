#ifndef PRIMALITY_CHECKER_H
#define PRIMALITY_CHECKER_H

#include <iostream>
#include <random>

#include <gmpxx.h>

#include "constants.h"


class PrimalityChecker
{
public:
    PrimalityChecker() = default;
    ~PrimalityChecker() = default;

    bool miller_rabin(mpz_class number, int accuracy=ACCURACY_PRIMALITY);
    bool solovay_strassem(mpz_class number, int accuracy=ACCURACY_PRIMALITY);
};

#endif
