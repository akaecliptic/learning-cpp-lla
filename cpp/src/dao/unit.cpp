#include "../headers/dao.h"

/* TOP LEVEL FUNCTIONS */

static std::map<std::string, std::string> GetBase(){
    return {
        {    "presentIndicative",              "present"                              },
        {    "preteritIndicative",             "preterite"                            },
        {    "imperfectIndicative",            "imperfect"                            },
        {    "conditionalIndicative",          "conditional"                          },
        {    "futureIndicative",               "future"                               }
    };
}

static std::map<std::string, std::string> GetSubjunctive(){
    return {
        {    "presentSubjunctive",             "subjunctive"                          },
        {    "imperfectSubjunctive",           "subjunctive - imperfect"              },
        {    "futureSubjunctive",              "subjunctive - future"                 }
    };
}

static std::map<std::string, std::string> GetImperative(){
    return {
        {    "imperative",                     "imperative"                           },
        {    "negativeImperative",             "imperative - negative"                }
    };
}

static std::map<std::string, std::string> GetContinuous(){
    return {
        {    "presentContinuous",              "continuous"                           },
        {    "preteritContinuous",             "continuous - preterite"               },
        {    "imperfectContinuous",            "continuous - imperfect"               },
        {    "conditionalContinuous",          "continuous - conditional"             },
        {    "negativeImperative",             "imperative - negative"                }
    };
}

static std::map<std::string, std::string> GetPerfect(){
    return {
        {    "presentPerfect",                 "perfect"                              },
        {    "preteritPerfect",                "perfect - preterite"                  },
        {    "pastPerfect",                    "perfect - imperfect"                  },
        {    "conditionalPerfect",             "perfect - conditional"                },
        {    "futurePerfect",                  "perfect - future"                     },
        {    "presentPerfectSubjunctive",      "perfect - subjunctive"                },
        {    "pastPerfectSubjunctive",         "perfect - subjunctive - imperfect"    },
        {    "futurePerfectSubjunctive",       "perfect - subjunctive - future"       }
    };
}

/* DEFINITIONS */
std::map<std::string, std::string> GetTenseMap(TenseType tense) {
    switch (tense){
        case BASE:
            return GetBase();
        case SUBJUNCTIVE:
            return GetSubjunctive();
        case IMPERATIVE:
            return GetImperative();
        case CONTINUOUS:
            return GetContinuous();
        case PERFECT:
            return GetPerfect();
        default:
            return GetBase();
    }
}

std::string QueryUnit::ToQuery(){
    std::string tenses = "";
    for(const auto& [key, value] : GetTenseMap(tense)){
        tenses += "t." + key + ", ";
    }

    return "SELECT " + tenses + "v.* FROM table_verbs v LEFT JOIN table_tenses t ON v.verb = t.verb " + View::Random1();
}

int QueryUnit::TenseCount(){
    return GetTenseMap(tense).size();
}
