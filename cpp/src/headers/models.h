#pragma once

#include <iostream>
#include <string>

struct VerbBlock {
  std::string infinitive;
  std::string conjugation;
  std::string pronoun;
  std::string tense;
  bool isIrregular;
  bool isReflexsive;
};

struct VerbContext {
  std::string verb;
  std::string translation;
  bool isIrregular;
  bool isReflexsive;
};

std::ostream& operator<<(std::ostream &stream, const VerbBlock &block);
