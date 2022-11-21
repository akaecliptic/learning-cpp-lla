#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>
#include "models.h"
#include "../../libs/sqlite/sqlite3.h"

/* ENUMS */

enum TenseType {
    BASE = 0, SUBJUNCTIVE, IMPERATIVE, CONTINUOUS, PERFECT
};

/* NAMESPACES */

namespace View {
    std::string Random(const int amount);
    std::string Random1();
};

namespace UtilDAO {
    std::map<int, std::string> TensePrompt();

    struct ExecCallbackArguments {
        int tenseCount;
        int limit;
        std::vector<VerbBlock>& pool;
    };
};

/* STRUCTS */

struct QueryUnit {
    TenseType tense;
    int amountToQuery;

    std::string ToQuery();
    int TenseCount();
};

/* FUNCTIONS */

//"If the SQL is a query, then for each row in the query result the xCallback() function is called" - sqlite3 source code
//"If the callback function to sqlite3_exec() returns non-zero, then sqlite3_exec() will return SQLITE_ABORT" - sqlite3 source code
//With Parameters being: A parameter passed by sqlite3_exec() | Number of results | Result data | Column from Results
//Function pointer <RETURN_TYPE>(*<FUNCTION_NAME>)(<FORMAL_PARAMETERS>)
typedef int (*SQLiteCallback)(void* passed, int count, char** data, char** columns);
int RunQuery(QueryUnit queryUnit, std::vector<VerbBlock>& pool, SQLiteCallback callback);
std::map<std::string, std::string> GetTenseMap(TenseType tense);
