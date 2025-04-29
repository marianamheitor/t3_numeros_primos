#include "table_generator.h"


// https://medium.com/@ryan_forrester_/how-to-create-csv-file-using-c-d227c2b765f9
void TableGenerator::create_table(std::string type, std::vector<std::string> column, std::vector<std::vector<std::string>> data)
{
    std::ofstream file("docs/" + type + ".csv");

    // Abre um arquivo .csv
    if (!file.is_open())
    {
        std::cout << "Erro ao abrir arquivo " << type << ".csv\n";
        exit(EXIT_FAILURE);
    }

    // Define o nome das colunas
    for (int i=0; i<column.size(); i++)
    {
        file << column[i];
        if (i != column.size()-1)
        {
            file << ',';
        }
        
    }
    file << '\n';

    // Adiciona os dados obtidos em sua respectiva coluna
    for (int i=0; i<data.size(); i++)
    {
        for (int j=0; j<data[i].size(); j++)
        {
            file << data[i][j];
            if (j != data[i].size()-1)
            {
                file << ',';
            }
        }
        file << '\n';
    }

    // Fecha o arquivo
    file.close();
    std::cout << "Tabela criada com sucesso.\n";
}
