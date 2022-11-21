#pragma once

#include <iostream>
#include <string>

namespace Model
{
    struct Guess
    {
        std::string infinitive;
        std::string translation;

        std::string tense;
        std::string pronoun;
        std::string answer;

        std::string guess;
        bool correct;
    };

    struct Verb
    {
        std::string pronoun;
        std::string conjugation;
    };

    struct Block 
    {
        std::string infinitive;
        std::string translation;

        bool irregular;
        bool reflexsive;

        std::string tense;
        Verb verbs[7];
    };

    static std::string PrintVerbs(const Verb* verbs)
    {
        std::string out = "";

        for (int i = 0; i < 7; i++)
        {
            out += verbs[i].pronoun + "|" + verbs[i].conjugation + " ";
        }
        
        return out;
    }

    static std::ostream& operator<<(std::ostream &stream, const Block &block) 
    {
        return stream << block.infinitive << " {\n" 
                        << " translation: " << block.translation << "\n"
                        << " isIrregular: " << block.irregular << "\n"
                        << " isReflexsive: " << block.reflexsive << "\n"
                        << " tense: " << block.tense << "\n"
                        << " verbs: " << PrintVerbs(block.verbs) << "\n"
                        << "}";
    }
};
