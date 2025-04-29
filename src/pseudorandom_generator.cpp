#include "pseudorandom_generator.h"


PseudorandomGenerator::PseudorandomGenerator(uint32_t seed)
{
    this->pm_seed = seed;
    this->xs_seed = seed;
}

// https://www.researchgate.net/publication/332575342_FPGA_Implementation_of_Park-Miller_Algorithm_to_Generate_Sequence_of_32-Bit_Pseudo_Random_Key_for_Encryption_and_Decryption_of_Plain_Text
mpz_class PseudorandomGenerator::park_miller(int num_bits)
{
    // Definição de constantes do algoritmo
    uint32_t q = this->m / this->a;
    uint32_t r = this->m % this->a;

    int bits = 0;
    mpz_class generated_number = 0;

    // Loop até atingir a quantidade de bits desejada
    while (bits < num_bits)
    {
        // Definição de hi e lo
        uint32_t hi = this->pm_seed / q;
        uint32_t lo = this->pm_seed % q;
        // Cálculo de t
        uint32_t t = (this->a * lo) - (r * hi);

        // Novo valor de pm_seed, dependendo do resultado de t
        if (t > 0)
        {
            this->pm_seed = t;
        }
        else
        {
            this->pm_seed = t + this->m;
        }

        // Adicição dos 32 bits ao resultado e deslocamento de 32 bits
        generated_number <<= 32;
        generated_number |= this->pm_seed;
        bits += 32;
    }
    
    // Ajuste para caso num_bits não seja múltiplo de 32
    // Ou seja, ultrapassou o valor de bits
    if (bits > num_bits)
    {
        generated_number >>= (bits-num_bits);
    }
    
    return generated_number;
}

// https://en.wikipedia.org/wiki/Xorshift
mpz_class PseudorandomGenerator::xorshift(int num_bits)
{
    int bits = 0;
    mpz_class generated_number = 0;

    // Loop até atingir a quantidade de bits desejada
    while (bits < num_bits)
    {
        uint32_t aux_seed = this->xs_seed;
        aux_seed ^= aux_seed << 13; // xor + deslocamento de 13 bits à esquerda
        aux_seed ^= aux_seed >> 17; // xor + deslocamento de 17 bits à direita
        aux_seed ^= aux_seed << 5;  // xor + deslocamento de 5 bits à esquerda
    
        this->xs_seed = aux_seed;

        // Adicição dos 32 bits ao resultado e deslocamento de 32 bits
        generated_number <<= 32;
        generated_number |= this->xs_seed;
        bits += 32;
    }

    // Ajuste para caso num_bits não seja múltiplo de 32
    // Ou seja, ultrapassou o valor de bits
    if (bits > num_bits)
    {
        generated_number >>= (bits-num_bits);
    }

    return generated_number;
}

void PseudorandomGenerator::set_seed(uint32_t new_seed)
{
    this->pm_seed = new_seed;
    this->xs_seed = new_seed;
}
