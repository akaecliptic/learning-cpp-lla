#include "../include/app/accessor.h"

namespace Accessor 
{
    const static char* DATABASE_LOCATION = "../data.db";
    const static std::vector<std::string> VIEW_NAMES = { "view_base", "view_subjunctive", "view_imperative", "view_continuous", "view_perfect" };

    void LoadData(std::vector<Model::Block>& pool, Accessor::QueryUnit& unit) 
    {
        RunQuery(
            unit,
            pool, 
            [](void* passed, int count, char** data, char** cols) {
                ExecArguments args = *((ExecArguments*) passed);
                
                //The first 4 columns are: verb | translation | is_irregular | is_reflexsive
                //Every following 7 columns are: yo | tu | usted | nosotros | vosotros | ustedes | vos

                if ( count < 4 ) return QUERY_ERROR;

                int maxOffset = ((count - 4) / 7) - 1;
                std::uniform_int_distribution<int> distrib(0, maxOffset);
                int offset = distrib(generator);

                std::vector<std::string> tenseList = GetTenseList(args.unit.tense);
                for (int i = 0; i < 3; i++)        
                {
                    Model::Block block;


                    block.infinitive = data[0];         // verb
                    block.translation = data[1];        // translation
                    block.irregular = (bool) data[2];   // irregular
                    block.reflexsive = (bool) data[3];  // reflexsive

                    block.tense = tenseList[offset];

                    block.verbs[0] = { cols[4], data[4 + (offset * 7)]};
                    block.verbs[1] = { cols[5], data[5 + (offset * 7)]};
                    block.verbs[2] = { cols[6], data[6 + (offset * 7)]};
                    block.verbs[3] = { cols[7], data[7 + (offset * 7)]};
                    block.verbs[4] = { cols[8], data[8 + (offset * 7)]};
                    block.verbs[5] = { cols[9], data[9 + (offset * 7)]};
                    block.verbs[6] = { cols[10], data[10 + (offset * 7)]};
                    
                    args.pool.push_back(block);

                    if(++offset >= maxOffset) offset = 0;
                }

                return 0;
            }
        );
    }

    int RunQuery(QueryUnit& unit, std::vector<Model::Block>& pool, SQLiteCallback callback)
    {
        SQLiteConnection connection;
        sqlite3* database = connection.GetDatabase();
        char* errorMessage = connection.GetErrorMessage();
        std::string query = MakeQuery(unit);

        ExecArguments args = { unit, pool };

        int status = sqlite3_exec(database, query.c_str(), callback, &args, &errorMessage);

        if( status )
        {
            printf("Failed to Query Database:\nMessage - %s\nCode - %d", errorMessage, status);
        }

        return status;
    }

    std::string MakeQuery(const QueryUnit& unit)
    {
        std::string query = "SELECT * FROM " + VIEW_NAMES[(int) unit.tense] + " ORDER BY RANDOM() LIMIT " +  std::to_string(unit.amount) + ";";
        return query;
    }

    const std::vector<std::string> GetTenseList(Tense tense)
    {
        switch(tense) 
        {
            case SUB:
                return { "subjunctive", "subjunctive - imperfect", "subjunctive - future" };
            case IMP:
                return { "imperative", "imperative - negative" };
            case CON:
                return { "continuous", "continuous - preterite", "continuous - imperfect", "continuous - conditional" };
            case PER:
                return { 
                    "perfect", "perfect - preterite", "perfect - imperfect", "perfect - conditional", "perfect - future", 
                    "perfect - subjunctive", "perfect - subjunctive - imperfect", "perfect - subjunctive - future" 
                };
            case BSC: 
            default:
                return { "present", "preterite", "imperfect", "conditional", "future" };
        }
    }

    SQLiteConnection::SQLiteConnection() : errorMessage(0)
    {
        int resultCode = sqlite3_open(DATABASE_LOCATION, &database);

        if( resultCode != SQLITE_OK )
        {
            errorMessage = (char*) sqlite3_errmsg(database);
            printf("Failed to Open Database:\nMessage - %s", errorMessage);
            CloseConnection();
        }
    }

    SQLiteConnection::~SQLiteConnection()
    {
        CloseConnection();
    }

    sqlite3* SQLiteConnection::GetDatabase()
    {
        return database;
    }

    char* SQLiteConnection::GetErrorMessage()
    {
        return errorMessage;
    }

    void SQLiteConnection::CloseConnection()
    {
        sqlite3_free(errorMessage);
        sqlite3_close(database);
    }
};
