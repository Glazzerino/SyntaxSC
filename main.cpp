#include "SyntaxScanner.h"
#include <fstream>
#include <chrono>
int main() {
   // Get execution time
   auto start = std::chrono::high_resolution_clock::now();
   SyntaxScanner scanner;
   scanner.scan("./testfile.sc");
   scanner.generate_html();
   std::cout << "Done!" << std::endl;
   auto end = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> diff = end - start;
   std::cout << "Execution time: " << diff.count() << " s" << std::endl;
}