#pragma once
#include <string>

enum LexemeType {
   RESERVED,
   IDENTIFIER,
   INT,
   FLOAT,
   OPERATOR,
   COMMENT
};

struct lexeme_t {
   std::string value;
   LexemeType type;
   lexeme_t(std::string val, LexemeType t) : value(val), type(t) {}
};