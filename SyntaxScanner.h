#include <iostream>
#include "lexeme.h"
#include <fstream>
#include <unordered_set>
#include "pattern.h"
#include <regex>

const char* RES_WORDS_FILEPATH = "./resources/reserved_words.txt";
const char* OPERATOR_FILEPATH = "./resources/operators.txt";

class SyntaxScanner {
   public:
      SyntaxScanner();
      void scan(std::string filename);
private:
   void load_reserved_words();
   std::unordered_set<std::string> reserved_words;
   std::unordered_set<std::string> operators;
   std::vector<lexeme_t> lexemes;
   std::vector<pattern_t> patterns; 
   void load_patterns();
   void load_from_file(std::string filename, std::unordered_set<std::string>& container);
   void scan(std::ifstream file);
   lexeme_t classify_word(std::string word);
};

SyntaxScanner::SyntaxScanner() {
   // Load reserved words
   load_from_file(RES_WORDS_FILEPATH, reserved_words);
   // Load operators
   load_from_file(OPERATOR_FILEPATH, operators);
   if (reserved_words.size() == 0) 
      std::cout << "Error: Could not load reserved words." << std::endl;
   else 
      std::cout << "Reserved words loaded from file " << RES_WORDS_FILEPATH << std::endl;
   load_patterns(); 

}

void SyntaxScanner::load_from_file(std::string filename, std::unordered_set<std::string>& container) {
   std::ifstream file(filename);
   std::string line;
   while (std::getline(file, line)) {
      container.insert(line);
   }
}

void SyntaxScanner::load_patterns() {
   // Symbols, reserved words and comments 
   // are implemented programmatically, not as regex patterns.
   patterns = {
      // Int regex
      pattern_t(R"(-?[1-9]\d*|0)", LexemeType::INT),
      // Identifier
      pattern_t(R"([^{}()\[\]&#'";,]+)", LexemeType::IDENTIFIER),
      // Float
      pattern_t(R"(-?\d+(\.\d+)?((e|E)-?\d+(\.\d+)?)?)", LexemeType::FLOAT),
   };
}

void SyntaxScanner::scan(std::ifstream file) {
   // Iterate over characters in file
   std::string line;
   std::string word = "";
   std::string html_body = "";

   while (std::getline(file, line)) {
      int counter = 0;
      for (char c : line) {
         if (c == ' ' || c == '\n') {
            html_body += c;
            lexeme_t lex = classify_word(word);
         }
         else {
            word += c;
         }
         counter++;
      }
   }
}

lexeme_t SyntaxScanner::classify_word(std::string word) {
   // Check if word is reserved word
   if (reserved_words.find(word) != reserved_words.end()) {
      return lexeme_t(word, LexemeType::RESERVED);
   }
   // Check if word is an operator
   if (operators.find(word) != operators.end()) {
      return lexeme_t(word, LexemeType::OPERATOR);
   }
   // Check against patterns
   for (pattern_t pattern : patterns) {
     bool match = std::regex_match(word, pattern.regex); 
   }

}
