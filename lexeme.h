#pragma once
#include <string>

enum LexemeType {
   RESERVED,
   IDENTIFIER,
   INT,
   FLOAT,
   OPERATOR,
   COMMENT,
   ERROR
};

struct lexeme_t {
   std::string value;
   LexemeType type;
   lexeme_t(std::string val, LexemeType t) : value(val), type(t) {}
   std::string typeString() {
      switch (type) {
         case RESERVED:
            return "reserved";
         case IDENTIFIER:
            return "identifier";
         case INT:
            return "int";
         case FLOAT:
            return "float";
         case OPERATOR:
            return "operator";
         case COMMENT:
            return "comment";
         case ERROR:
            return "error";
         default:
            return "unknown";
      }
   }
};