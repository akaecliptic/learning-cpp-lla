#pragma once 

#include <vector>
#include "models.h"
#include "parser.h"

std::string RemoveSpecialChars(std::string input);

class Logic {
    public:
        static const int MAX_ROUND = 3;
    private:
        int roundLength;
        std::vector<VerbBlock> pool;
        int currentRound;
        int correct;
    public:
        Logic(TenseType tense, int amount);
        void Display();
        bool Guess(std::string answer);
        int Evaluate();
        VerbBlock GetCurrentBlock() const;
        std::vector<VerbBlock> GetPool() const;
        bool HasMoreRounds() const;
};
