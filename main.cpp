#include "SyntaxScanner.h"
#include <fstream>

int main() {
   SyntaxScanner scanner;
   scanner.scan("./testfile.sc");
   scanner.print_html();
}