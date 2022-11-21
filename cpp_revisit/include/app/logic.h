#pragma once

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <fcntl.h>
#include <io.h>
#include <locale>
#include <codecvt>

#include "accessor.h"

#define FAILED_PARSE -1
#define EXIT_REQUEST 1

namespace Logic 
{
    void StartMenu(int&, Accessor::QueryUnit&);

    void PrintInstructions();
    void PrintTensePrompt();
    void PrintAmountPrompt();

    bool HasExit(std::string&);
    void ReadGuess(int&, std::string&);
    bool IsTenseValid(const std::string input);
    bool IsAmountValid(const std::string input);

    void PrepareRound(const std::vector<Model::Block>&, std::vector<Model::Guess>&);
    void PrintVerb(std::string);
    bool CompareAnswer(const std::string&, const std::string&);

    class Game
    {
        public:
            static const int MAX_ROUND = 5;
        private:
            int status;
            
            int score;
            int currentRound;
            int totalRounds;

            std::vector<Model::Guess> rounds;
        public:
            Game();
            int Start();
            void DisplayRound();
            bool Guess(std::string);
            void Tally();
            Model::Guess GetCurrentRound();
            const std::vector<Model::Guess>& GetRounds();
            bool HasMoreRounds();
    };
};
