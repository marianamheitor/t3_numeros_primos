#ifndef TABLE_GENERATOR_H
#define TABLE_GENERATOR_H

#include <iostream>
#include <fstream>
#include <vector>


class TableGenerator
{
public:
    TableGenerator() = default;
    ~TableGenerator() = default;

    void create_table(std::string type, std::vector<std::string> column, std::vector<std::vector<std::string>> data);
};

#endif
