#include "headers/parser.h"
#include <iostream>

static std::random_device randomDevice = std::random_device {}; 
static std::mt19937 randomGenerator = std::default_random_engine { randomDevice() };

static void MakeGuess();
static std::vector<VerbBlock> GetBlocks(const std::string input, const std::string tense, const VerbContext context);
static VerbBlock ToBlock(const nlohmann::json input, const std::string tense, const VerbContext context);

static std::vector<VerbBlock> GetBlocks(const std::string input, const std::string tense, const VerbContext context){
    using nlohmann::json;
    std::vector<VerbBlock> blocks;

    if(!json::accept(input)) return blocks;
    json inputJson = json::parse(input);
    if(!inputJson.is_array()) return blocks;
    
    blocks.reserve(inputJson.size());
    for( json j : inputJson){
        VerbBlock b = ToBlock(j, tense, context);
        blocks.push_back(b);
        // std::cout << b << std::endl;
    }

    return blocks;
}

static VerbBlock ToBlock(const nlohmann::json input, const std::string tense, const VerbContext context){
    const std::string infinitive = context.verb;
    const std::string pronoun = input["pronoun"].get<std::string>();
    const std::string conjugation = input["word"].get<std::string>();
    const bool isIrregular = input["isIrregular"].get<bool>();
    const bool isReflexsive = context.isReflexsive;

    return { infinitive, conjugation, pronoun, tense, isIrregular, isReflexsive };
}

void Parser::Parse(const int amount);

void Parser::LoadData(std::vector<VerbBlock>& pool, TenseType tense, int amount){
    QueryUnit unit = { tense, amount };
    //Becuase the way the database is structured and how this function is called
    //This is very inefficient...
    RunQuery(unit, pool, [](void* passed, int count, char** data, char** columns) {
        UtilDAO::ExecCallbackArguments callbackArguments = ((UtilDAO::ExecCallbackArguments*) passed)[0];

        std::string verb, translation;
        bool isIrregular, isReflexsive;

        for(int i = callbackArguments.tenseCount; i < count; i++){
            //Having auto col = columns[i]; was causing an error at == comparison that I still don't understand
            //Needs more looking into
            std::string col = columns[i];
            std::string val = data[i];

            if( col == "verb" ){
                verb = val;
            }else if( col == "translation" ) {
                translation = val;
            } else if( col == "is_irregular" ) {
                isIrregular = std::stoi( val );
            } else {
                isReflexsive = std::stoi( val );
            }
        }

        for(int i = 0; i < callbackArguments.tenseCount; i++){
            std::vector<VerbBlock> block = GetBlocks(data[i], columns[i], { verb, translation, isIrregular, isReflexsive });

            std::vector<VerbBlock>::iterator it = callbackArguments.pool.end();
            callbackArguments.pool.insert(it, block.begin(), block.begin() + 2);
        }

        int limit = (callbackArguments.limit * 5);
        std::shuffle(callbackArguments.pool.begin(), callbackArguments.pool.end(), randomGenerator);
        callbackArguments.pool.erase(callbackArguments.pool.begin() + limit, callbackArguments.pool.end());
        
        return 0;
    });
}
