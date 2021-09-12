#pragma once
#include "lexeme.h"
#include <regex>

struct pattern_t {
   std::regex regex;
   LexemeType type;
   pattern_t(std::string const& pattern, LexemeType type) {
      this->regex = std::regex(pattern);
      this->type = type;
   }
};