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
   void print_html();
private:
   void load_reserved_words();
   std::unordered_set<std::string> reserved_words;
   std::unordered_set<std::string> operators;
   std::vector<lexeme_t> lexemes;
   std::vector<pattern_t> patterns; 
   void load_patterns();
   void load_from_file(std::string filename, std::unordered_set<std::string>& container);
   lexeme_t classify_word(std::string word);
   std::string lexeme_to_html(lexeme_t lexeme, size_t spaces);
   std::string word_to_html(std::string word, size_t spaces);
   std::vector<std::string> words_html;
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
      // Int 
      pattern_t(R"(-?[1-9]\d*|0)", LexemeType::INT),
      // Float
      pattern_t(R"(-?\d+(\.\d+)?((e|E)-?\d+(\.\d+)?)?)", LexemeType::FLOAT),
      // Identifier
      pattern_t(R"([^{}()\[\]&#'";,]+)", LexemeType::IDENTIFIER),
   };
}

void SyntaxScanner::scan(std::string filename) {
   std::ifstream file(filename);
   // Iterate over characters in file
   std::string line;
   std::string word = "";

   while (std::getline(file, line)) {
      int counter = 0;
      int spaces = 0;
      for (char c : line) {
         // If character is comment symbol, add rest of line and skip to next line
         if (c == ';') {
            std::string comment_line = line.substr(counter);
            lexeme_t lexeme(comment_line, LexemeType::COMMENT);
            std::string comment_html = lexeme_to_html(lexeme, spaces); 
            words_html.push_back(comment_html);
            break;
         }

         bool is_op = operators.find(std::string(1, c)) != operators.end();
         if (isspace(c)) {
            if (word != "") {
               lexeme_t lexeme = classify_word(word);
               std::string word_html = lexeme_to_html(lexeme, spaces);
               words_html.push_back(word_html);
               word = "";
            }
            spaces++;
         }

         else if (is_op) {
            if (word != "") {
               // Manages cases where the - operator is used as part of an identifier
               // e.g. "a-b"
               // Scheme is weird
               if (c == '-') {
                  word += c;
                  continue;
               }
               lexeme_t lexeme = classify_word(word);
               std::string word_html = lexeme_to_html(lexeme, spaces);
               words_html.push_back(word_html);
               word = "";
            }
            lexeme_t oplex(std::string(1, c), LexemeType::OPERATOR);
            std::string word_html = lexeme_to_html(oplex, 0);
            words_html.push_back(word_html);
         }
         else 
            word += c;
         counter++;
      }
      // Add last word
      if (word != "") {
         lexemes.push_back(classify_word(word));
         word = "";
      }
      words_html.push_back(std::string("<br/>"));
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
      if (match) 
         return lexeme_t(word, pattern.type);
   }
   // If not anything else, it is an error
   return lexeme_t(word, LexemeType::ERROR);
}

std::string SyntaxScanner::lexeme_to_html(lexeme_t lexeme, size_t spaces) {
   std::string html = "";
   std::cout << lexeme.value << "\n";
   html += R"(<font class=")" + lexeme.typeString() + R"(">)";
   // Add spaces
   for (size_t i = 0; i < spaces; i++) 
      html += ' ';   
   html += lexeme.value;
   html += "</font>";
   // std::cout << html << std::endl;
   return html;
}

void SyntaxScanner::print_html() {
   for (std::string word : words_html) {
      std::cout << word;
      if (word == "<br/>")
         std::cout << std::endl;
   }
}

