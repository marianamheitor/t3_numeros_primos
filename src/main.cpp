#include <random>
#include <chrono>

#include "pseudorandom_generator.h"
#include "primality_checker.h"
#include "table_generator.h"


int main(int argc, char* argv[])
{
    std::vector<unsigned int> num_bits = {40, 56, 80, 128, 168, 224, 256, 512, 1024, 2048, 4096};
    
    // https://www.geeksforgeeks.org/how-to-generate-random-number-in-range-in-cpp/
    // Para gerar uma seed aleatória a cada execução
    std::random_device random_devide;
    unsigned int seed_value = random_devide();

    PseudorandomGenerator number_generator = PseudorandomGenerator(seed_value);
    PrimalityChecker primaliry_verifier = PrimalityChecker();
    TableGenerator table = TableGenerator();

    std::vector<std::string> num_gen_column = {"Algoritmo", "Tamanho do número", "Tempo para gerar"};
    std::vector<std::vector<std::string>> num_gen_table;

    std::vector<std::string> prime_num_column = {"Algoritmo", "Tamanho do número", "Número primo gerado", "Tempo para gerar"};
    std::vector<std::vector<std::string>> prime_num_table;

    mpz_class number;
    for (auto bits : num_bits)
    {
        // Park-Miller + Miller-Rabin
        for (int i=0; i<5; i++)
        {
            auto start_prime = std::chrono::high_resolution_clock::now();

            auto start_gen = std::chrono::high_resolution_clock::now();
            number = number_generator.park_miller(bits);
            auto end_gen = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_gen-start_gen);
            num_gen_table.push_back({"Park-Miller", std::to_string(bits)+ " bits", std::to_string(duration.count())+" ms"});

            while (!primaliry_verifier.miller_rabin(number))
            {
                start_gen = std::chrono::high_resolution_clock::now();
                number = number_generator.park_miller(bits);
                end_gen = std::chrono::high_resolution_clock::now();

                duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_gen-start_gen);
                num_gen_table.push_back({"Park-Miller", std::to_string(bits)+ " bits", std::to_string(duration.count())+" ms"});
            }

            auto end_prime = std::chrono::high_resolution_clock::now();

            duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_prime-start_prime);
            prime_num_table.push_back({"Miller-Rabin", std::to_string(bits)+ " bits", number.get_str(10), std::to_string(duration.count())+" ms"});
        }
        std::cout << "Park-Miller com Miller-Rabin com " << bits << " bits finalizado.\n";

        // Xorshift + Miller-Rabin
        for (int i=0; i<5; i++)
        {
            auto start_prime = std::chrono::high_resolution_clock::now();

            auto start_gen = std::chrono::high_resolution_clock::now();
            number = number_generator.xorshift(bits);
            auto end_gen = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_gen-start_gen);
            num_gen_table.push_back({"Xorshift", std::to_string(bits)+ " bits", std::to_string(duration.count())+" ms"});
            
            while (!primaliry_verifier.miller_rabin(number))
            {
                start_gen = std::chrono::high_resolution_clock::now();
                number = number_generator.xorshift(bits);
                end_gen = std::chrono::high_resolution_clock::now();

                duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_gen-start_gen);
                num_gen_table.push_back({"Xorshift", std::to_string(bits)+ " bits", std::to_string(duration.count())+" ms"});
            }

            auto end_prime = std::chrono::high_resolution_clock::now();

            duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_prime-start_prime);
            prime_num_table.push_back({"Miller-Rabin", std::to_string(bits)+ " bits", number.get_str(10), std::to_string(duration.count())+" ms"});
        }
        std::cout << "Xorshift com Miller-Rabin com " << bits << " bits finalizado.\n";

        // Coloca sementes originais ao gerador
        number_generator.set_seed(seed_value);

        // Park-Miller + Solovay-Strassem
        for (int i=0; i<5; i++)
        {
            auto start_prime = std::chrono::high_resolution_clock::now();

            auto start_gen = std::chrono::high_resolution_clock::now();
            number = number_generator.park_miller(bits);
            auto end_gen = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_gen-start_gen);
            num_gen_table.push_back({"Park-Miller", std::to_string(bits)+ " bits", std::to_string(duration.count())+" ms"});
            
            while (!primaliry_verifier.solovay_strassem(number))
            {
                start_gen = std::chrono::high_resolution_clock::now();
                number = number_generator.park_miller(bits);
                end_gen = std::chrono::high_resolution_clock::now();

                duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_gen-start_gen);
                num_gen_table.push_back({"Park-Miller", std::to_string(bits)+ " bits", std::to_string(duration.count())+" ms"});
            }

            auto end_prime = std::chrono::high_resolution_clock::now();

            duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_prime-start_prime);
            prime_num_table.push_back({"Solovay-Strassem", std::to_string(bits)+ " bits", number.get_str(10), std::to_string(duration.count())+" ms"});
        }
        std::cout << "Park-Miller com Solovay-Strassem com " << bits << " bits finalizado.\n";

        for (int i=0; i<5; i++)
        {
            auto start_prime = std::chrono::high_resolution_clock::now();

            auto start_gen = std::chrono::high_resolution_clock::now();
            number = number_generator.xorshift(bits);
            auto end_gen = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_gen-start_gen);
            num_gen_table.push_back({"Xorshift", std::to_string(bits)+ " bits", std::to_string(duration.count())+" ms"});
            
            while (!primaliry_verifier.solovay_strassem(number))
            {
                start_gen = std::chrono::high_resolution_clock::now();
                number = number_generator.xorshift(bits);
                end_gen = std::chrono::high_resolution_clock::now();

                duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_gen-start_gen);
                num_gen_table.push_back({"Xorshift", std::to_string(bits)+ " bits", std::to_string(duration.count())+" ms"});
            }

            auto end_prime = std::chrono::high_resolution_clock::now();

            duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_prime-start_prime);
            prime_num_table.push_back({"Solovay-Strassem", std::to_string(bits)+ " bits", number.get_str(10), std::to_string(duration.count())+" ms"});
        }
        std::cout << "Xorshift com Solovay-Strassem com " << bits << " bits finalizado.\n";
    }

    table.create_table("pseudorandom_number", num_gen_column, num_gen_table);
    table.create_table("prime_number", prime_num_column, prime_num_table);

    return 0;
}
