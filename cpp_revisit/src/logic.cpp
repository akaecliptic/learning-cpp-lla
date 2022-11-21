#include "../include/app/logic.h"

namespace Logic 
{
    void StartMenu(int& status, Accessor::QueryUnit& unit)
    {
        std::string tense;
        std::string amount;

        do {
            PrintTensePrompt();
            std::getline(std::cin, tense);

            if(HasExit(tense))
            {
                status = EXIT_REQUEST;
                return;
            }

            if(IsTenseValid(tense))
            {
                try {
                    unit.tense = (Accessor::Tense) std::stoi(tense);
                } catch(std::invalid_argument) {
                    status = FAILED_PARSE;
                    return;
                }

                break;
            }
        } while (true);
        
        do {
            PrintAmountPrompt();
            std::getline(std::cin, amount);

            if(HasExit(amount))
            {
                status = EXIT_REQUEST;
                return;
            }

            if(IsAmountValid(amount))
            {
                try {
                    unit.amount = std::stoi(amount);
                } catch(std::invalid_argument) {
                    status = FAILED_PARSE;
                    return;
                }

                break;
            }
        } while (true);
    }

    void PrintInstructions()
    {
        std::cout << "Hello.\n";
        std::cout << "This is simple game of guessing the verb conjugate.\n";
        std::cout << "Each round has 3 guesses for a verb.\n";
        std::cout << "You can simply type 'exit' at any time to quite the game.\n" << std::endl;
    }

    void PrintTensePrompt()
    {
        std::cout << "Please choose a number from the options below:\n";
        std::cout << "Base = 0 | Subjunctive = 1 | Imperative = 2 | Continuous = 3 | Perfect = 4" << std::endl;
    }

    void PrintAmountPrompt()
    {
        std::cout << "Please choose the amount of rounds to play (Between 1 and " + std::to_string(Game::MAX_ROUND) + ". There are 3 questions per round):\n";
    }

    bool HasExit(std::string& str)
    {
        return (str == "exit");
    }

    void ReadGuess(int& status, std::string& line)
    {
        do {
            std::getline(std::cin, line);

            if(HasExit(line)){
                status = EXIT_REQUEST;
                break;
            }

            if(line.size() > 0) break;
        } while (true);
    }

    bool IsTenseValid(const std::string input)
    {
        int value = -1;

        try{
            value = std::stoi(input);
        }catch(std::invalid_argument){
            return false;
        }

        return ( value >= 0 ) && ( value <= 4 );
    }

    bool IsAmountValid(const std::string input)
    {
        int value = -1;

        try{
            value = std::stoi(input);
        }catch(std::invalid_argument){
            return false;
        }

        return ( value >= 1 ) && ( value <= Game::MAX_ROUND );
    }

    void PrepareRound(const std::vector<Model::Block>& pool, std::vector<Model::Guess>& rounds)
    {
        std::uniform_int_distribution<int> distrib(0, 6);

        for (int i = 0; i < pool.size(); i++)
        {
            int select = distrib(Accessor::generator);

            Model::Guess guess = {
                pool[i].infinitive, 
                pool[i].translation,
                pool[i].tense,
                pool[i].verbs[select].pronoun,
                pool[i].verbs[select].conjugation,
                "",
                0
            };

            rounds.push_back(guess);
        }

        std::shuffle(rounds.begin(), rounds.end(), Accessor::generator);
    }

    void PrintVerb(std::string str)
    {
        _setmode(_fileno(stdout), _O_U8TEXT);
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring wide = converter.from_bytes(str);
        std::wcout << wide;
        _setmode(_fileno(stdout), _O_TEXT);
    }

    bool CompareAnswer(const std::string& answer, const std::string& guess)
    {
        static std::unordered_map<wchar_t, wchar_t> specials = {
            { L'á', L'a' }, { L'é', L'e' }, { L'í', L'i' },
            { L'ó', L'o' }, { L'ú', L'u' }, { L'ñ', L'n' }
        };

        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring wAnswer = converter.from_bytes(answer);
        std::wstring wGuess = converter.from_bytes(guess);

        if (wAnswer == wGuess) return true;

        for( int i = 0; i < wAnswer.size(); i++ )
        {
            if(i > wGuess.size() - 1) return false;

            if(wAnswer[i] == wGuess[i]) continue;

            auto it = specials.find(wAnswer[i]);
            
            if(it == specials.end() || (*it).second != wGuess[i]) return false;
        }

        return true;
    }

    Game::Game()
        : status(0), currentRound(0), score(0), totalRounds(0)
    { }

    int Game::Start()
    {
        PrintInstructions();

        Accessor::QueryUnit unit;
        std::vector<Model::Block> pool;

        StartMenu(status, unit);

        if(status == EXIT_REQUEST) return status;

        Accessor::LoadData(pool, unit);
        Logic::PrepareRound(pool, rounds);

        totalRounds = rounds.size();

        while(HasMoreRounds())
        {
            DisplayRound();

            std::string guess;
            ReadGuess(status, guess);

            if(status == EXIT_REQUEST) return status;

            Guess(guess);
        }

        Tally();
        return status;
    }

    void Game::DisplayRound()
    {
        Model::Guess working = rounds[currentRound];
        std::cout << "\nRound " << currentRound << "\n";
        std::cout << working.tense << " | " << working.pronoun << " - ";
        PrintVerb(working.infinitive);
        std::cout << " | " << working.translation << "\n";
        std::cout << "Please guess: " << std::endl;
    }

    bool Game::Guess(std::string guess)
    {
        bool isCorrect = CompareAnswer(rounds[currentRound].answer, guess);

        if(isCorrect) ++score;

        rounds[currentRound].guess = guess;
        ++currentRound;

        return isCorrect;
    }

    void Game::Tally()
    {
        std::cout << "\nYour Final Score is: " << score << "/" << totalRounds << "\n\n";
        std::cout << "Goodbye" << std::endl;
    }

    Model::Guess Game::GetCurrentRound()
    {
        return rounds[currentRound];
    }

    const std::vector<Model::Guess>& Game::GetRounds()
    {
        return rounds;
    }

    bool Game::HasMoreRounds()
    {
        return currentRound < totalRounds;
    }
};
