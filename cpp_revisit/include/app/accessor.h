#pragma once

#include <vector>
#include <random>

#include "../libs/sqlite/sqlite3.h"

#include "model.hpp"

#define QUERY_ERROR -2

namespace Accessor
{
    static std::random_device generator("mt19937");

    enum Tense 
    { 
        BSC = 0, SUB, IMP, CON, PER
    };

    struct QueryUnit 
    {
        Tense tense;
        int amount;
    };

    struct ExecArguments 
    {
        QueryUnit& unit;
        std::vector<Model::Block>& pool;
    };

    class SQLiteConnection 
    {
        private:
            sqlite3* database;
            char* errorMessage;
        public:
            SQLiteConnection();
            ~SQLiteConnection();
            sqlite3* GetDatabase();
            char* GetErrorMessage();
        private:
            void CloseConnection();
    };

    typedef int (*SQLiteCallback)(void* passed, int count, char** data, char** columns);

    int RunQuery(QueryUnit&, std::vector<Model::Block>&, SQLiteCallback);
    void LoadData(std::vector<Model::Block>&, Accessor::QueryUnit&);
    std::string MakeQuery(const QueryUnit&);

    const std::vector<std::string> GetTenseList(Tense);
};
