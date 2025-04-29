#include "primality_checker.h"


// https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
// https://www.cs.cornell.edu/courses/cs4820/2010sp/handouts/MillerRabin.pdf
bool PrimalityChecker::miller_rabin(mpz_class number, int accuracy)
{
    // Números 2 e 3 são primos por padrão
    if (number == 2 || number == 3)
    {
        return true;
    }
    // Se o número é par, então não é primo
    if (number <= 1 || number % 2 == 0)
    {
        return false;
    }

    // Fatora number-1 como 2^s * t, sendo t ímpar
    // Ou seja, number-1 = 2^s * t
    int s = 0;
    mpz_class t = number-1;
    while (t % 2 == 0)
    {
        s++;
        t /= 2;
    }

    // Gerador de um número aleatório para um intervalo
    // https://stackoverflow.com/questions/11755482/random-number-generation-in-c-using-gmp
    // https://gmplib.org/manual/C_002b_002b-Interface-Random-Numbers
    gmp_randclass rng(gmp_randinit_mt);
    rng.seed(time(nullptr));

    for (int i=0; i<accuracy; i++)
    {
        // Pega um número aleatório no intervalo [2...n-1]
        mpz_class random_num = rng.get_z_range(number-2)+2;
        
        // Faz a exponenciação modular -> random_num^t mod number
        // https://gmplib.org/manual/Integer-Exponentiation
        mpz_class x;
        mpz_powm(x.get_mpz_t(), random_num.get_mpz_t(), t.get_mpz_t(), number.get_mpz_t());
        if (x == 1 || x == number-1)
        {
            continue;
        }

        bool keep = false;
        for (int j=0; j<s-1; j++)
        {
            x = (x * x) % number; // exponenciação modular (x, 2, number)
            if (x == 1)
            {
                return false;
            }
            if (x == number-1)
            {
                keep = true;
                continue;
            }
        }

        if (!keep)
        {
            return false;
        }
    }

    return true;
}

// https://en.wikipedia.org/wiki/Solovay%E2%80%93Strassen_primality_test
bool PrimalityChecker::solovay_strassem(mpz_class number, int accuracy)
{
    // Números 2 e 3 são primos por padrão
    if (number == 2 || number == 3)
    {
        return true;
    }
    // Se o número é par, então não é primo
    if (number <= 1 || number % 2 == 0)
    {
        return false;
    }

    // Gerador de um número aleatório para um intervalo
    // https://stackoverflow.com/questions/11755482/random-number-generation-in-c-using-gmp
    // https://gmplib.org/manual/C_002b_002b-Interface-Random-Numbers
    gmp_randclass rng(gmp_randinit_mt);
    rng.seed(time(nullptr));

    for (int i=0; i<accuracy; i++)
    {
        // Pega um número aleatório no intervalo [2...n-1]
        mpz_class random_num = rng.get_z_range(number-2)+2;;
        
        // Calcula o símbolo de Jacobi
        // https://gmplib.org/manual/Number-Theoretic-Functions
        int jacobi_num = mpz_jacobi(random_num.get_mpz_t(), number.get_mpz_t());
        mpz_class exp = (number-1)/2;
        mpz_class mod_exp;
        mpz_powm(mod_exp.get_mpz_t(), random_num.get_mpz_t(), exp.get_mpz_t(), number.get_mpz_t());

        if (jacobi_num == 0 || mod_exp != (jacobi_num + number) % number)
        {
            return false;
        }
    }

    return true;
}
