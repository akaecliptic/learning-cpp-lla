#include "../headers/dao.h"

std::string View::Random(const int amount){
    return "ORDER BY RANDOM() LIMIT " + std::to_string(amount) + ";";
}

std::string View::Random1(){
    return "ORDER BY RANDOM() LIMIT 25;";
}
