#pragma once

#include <iostream>
#include "logic.h"

//PROMPTS
static void PrintTensePrompt(){
    auto promptMap = UtilDAO::TensePrompt();
    std::string options = "| ";

    std::cout << "Please choose a number from the options below:\n";
    for(const auto& [key, value] : promptMap){
        options += std::to_string(key) + " = " + value + " | ";
    }
    std::cout << options + "\n";
}

static void PrintRoundPrompt(){
    std::cout << "Please choose a number of rounds between 1 and " + std::to_string(Logic::MAX_ROUND) + ":\n";
}

static void PrintExitPrompt(){
    const std::string exitStrings[] = { "exit;", "kill;" };
    std::string options = "'exit;' or 'kill;'";
    std::cout << "Type: " + options + " to close the app at any time.\n";
}

//INPUT CHECKS
static bool HasExit(const std::string line){
    const std::string exitStrings[] = { "exit;", "kill;" };

    //string.compare() returns 0 if equal, using == for personal clarity
    for( const auto& keywords : exitStrings){
        if(line == keywords) return true;
    }

    return false;
}

static bool IsTenseValid(const std::string input){
    auto tenses = UtilDAO::TensePrompt();
    int value = -1;

    try{
        value = std::stoi(input);
    }catch(std::invalid_argument){
        return false;
    }

    auto search = tenses.find(value);
    return search != tenses.end();
}

static bool IsRoundValid(const std::string input){
    int value = -1;

    try{
        value = std::stoi(input);
    }catch(std::invalid_argument){
        return false;
    }

    return (( value > 0 ) && ( value <= Logic::MAX_ROUND ));
}

// READERS
int TenseReader(bool& isRunning){
    std::string line;
    bool looping = true;

    do {
        PrintTensePrompt();
        std::getline(std::cin, line);

        isRunning = !HasExit(line);
        looping = !IsTenseValid(line);
    } while (looping && isRunning);

    try {
        return std::stoi(line);
    }catch(std::invalid_argument){
        return -1;
    }
}

int RoundReader(bool& isRunning){
    std::string line;
    bool looping = true;

    do {
        PrintRoundPrompt();
        std::getline(std::cin, line);

        isRunning = !HasExit(line);
        looping = !IsRoundValid(line);
    } while (looping && isRunning);

    try {
        return std::stoi(line);
    }catch(std::invalid_argument){
        return -1;
    }
}

int GuessReader(bool& isRunning, Logic& logic){
    std::string line;
    bool looping = true;

    do {
        VerbBlock current = logic.GetCurrentBlock();
        logic.Display();
        std::getline(std::cin, line);

        isRunning = !HasExit(line);
        bool result = logic.Guess(line);

        std::cout << (result ? "correct" : "incorrect");
        if(result){
            std::cout << " +1\n" << std::endl;
        }else{
            std::cout << " | correct answer is '" << current.conjugation << "'\n" << std::endl;
        }

        looping = logic.HasMoreRounds();
    } while (looping && isRunning);

    return logic.Evaluate();
}
