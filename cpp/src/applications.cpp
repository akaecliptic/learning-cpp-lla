#include "headers/applications.h"
#include "headers/helper.hpp"

/* DEFINITIONS */
ConsoleApplication::ConsoleApplication(){
    isRunning = true;
}

int ConsoleApplication::Run() {
    PrintExitPrompt();
    int status = 0;

    TenseType tense = (TenseType) TenseReader(isRunning);
    if(!isRunning) return status; 

    int rounds = RoundReader(isRunning);
    if(!isRunning) return status;

    Logic logic(tense, rounds);

    int tally = GuessReader(isRunning, logic);

    std::cout << "You got " << tally << " answers correct" << std::endl;
    
    return status;
}
