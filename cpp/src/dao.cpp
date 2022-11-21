#include "headers/dao.h"

/* GLOBALS */

const static char* DATABASE_LOCATION = "../database.db";

/* DECLERATIONS */

class SQLiteConnection {
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

/* TOP LEVEL FUNCTIONS */

int RunQuery(QueryUnit queryUnit, std::vector<VerbBlock>& pool, SQLiteCallback callback){
    SQLiteConnection connection;
    sqlite3* database = connection.GetDatabase();
    //Code was originally const char* query = queryUnit.ToQuery().c_str();
    //That access a dangling pointer, causing a headache of work.
    //Don't do this please.
    std::string query = queryUnit.ToQuery();
    //Decided to pass the tenseCount as an argument to sqlite3_exec()
    //It seems lambdas with captures don't work with basic non-functional typedef
    UtilDAO::ExecCallbackArguments tenseCount = { queryUnit.TenseCount(), queryUnit.amountToQuery, pool };
    char* errorMessage = connection.GetErrorMessage();
    
    int status = sqlite3_exec(database, query.c_str(), callback, &tenseCount, &errorMessage);

    if( status ){
        //TODO: Add proper logging if error;
        printf("Message - %s\nCode - %d", errorMessage, status);
    }

    return status;
}

/* DEFINITIONS */

SQLiteConnection::SQLiteConnection() : errorMessage(0){
    int resultCode = sqlite3_open(DATABASE_LOCATION, &database);

    if( resultCode != SQLITE_OK ){
        errorMessage = (char*) sqlite3_errmsg(database);
        //TODO: Print error message if reached sqlite3_errmsg(db);
        CloseConnection();
    }
}

SQLiteConnection::~SQLiteConnection(){
    CloseConnection();
}

sqlite3* SQLiteConnection::GetDatabase(){
    return database;
}

char* SQLiteConnection::GetErrorMessage(){
    return errorMessage;
}

void SQLiteConnection::CloseConnection(){
    sqlite3_free(errorMessage);
    sqlite3_close(database);
}

std::map<int, std::string> UtilDAO::TensePrompt(){
    return {
        { TenseType::BASE , "Base" },
        { TenseType::SUBJUNCTIVE , "Subjunctive" },
        { TenseType::IMPERATIVE , "Imperative" },
        { TenseType::CONTINUOUS , "Continuous" },
        { TenseType::PERFECT , "Perfect" }
    };
}
