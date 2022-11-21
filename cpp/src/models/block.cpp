#include "../headers/models.h"

std::ostream& operator<<(std::ostream &stream, const VerbBlock &block) {
  return stream << block.conjugation << " {\n" 
                << " tense: " << block.tense << "\n"
                << " pronoun: " << block.pronoun << "\n"
                << " infinitive: " << block.infinitive << "\n"
                << " isIrregular: " << block.isIrregular << "\n"
                << " isReflexsive: " << block.isReflexsive << "\n"
                << "}";
}
