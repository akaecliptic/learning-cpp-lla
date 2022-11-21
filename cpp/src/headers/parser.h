#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include "models.h"
#include "dao.h"
#include "../../libs/json/json.hpp"

namespace Parser {
    void Parse(const int amount);
    void LoadData(std::vector<VerbBlock>& pool, TenseType tense, int amount);
}
