#include "headers/logic.h"

//GLOBALS
static std::map<char, char> SPECIAL_CHARS = {
    { 'á', 'a' },
    { 'é', 'e' },
    { 'í', 'i' },
    { 'ó', 'o' },
    { 'ú', 'u' },
    { 'ñ', 'n' },
};

//This needs a better implementation that utilises character encoding
//Also needs much better / safer valid character checking and invalid pruning
//Will keep as is for now
std::string RemoveSpecialChars(std::string input){
    std::string toReturn = "";

    for(int i = 0; i < input.size(); i++){
        std::map<char, char>::iterator it = SPECIAL_CHARS.find(input[i]);

        if(it != SPECIAL_CHARS.end()){
            toReturn += (*it).second;
            continue;
        }

        if(it == SPECIAL_CHARS.end() && input[i] < 0) continue;

        toReturn += input[i];
    }

    return toReturn;
}

Logic::Logic(TenseType tense, int amount){
    Parser::LoadData(pool, tense, amount);
    roundLength = pool.size();
    currentRound = 0;
    correct = 0;
}

std::vector<VerbBlock> Logic::GetPool() const {
    return pool;
}

void Logic::Display(){
    VerbBlock current = pool[currentRound];
    std::cout << "Round | " << (currentRound + 1) << " of " << roundLength << " |" << std::endl;
    std::cout << "Guess | " << current.infinitive << " - " << current.tense <<  " - "  << current.pronoun << " |" << std::endl;
}

bool Logic::Guess(std::string answer){
    VerbBlock current = pool[currentRound];
    const bool check = (answer == RemoveSpecialChars(current.conjugation));
    
    if(check) correct++;

    currentRound++;
    
    return check;
}

VerbBlock Logic::GetCurrentBlock() const {
    return pool[currentRound];
}

bool Logic::HasMoreRounds() const {
    return currentRound < roundLength; 
}

int Logic::Evaluate(){
    return correct;
}
