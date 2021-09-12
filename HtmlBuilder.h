#include <string>
#include <fstream>
#include <iostream>
#include <vector>

std::string const FILE_NAME = "output/index.html";
std::string const first_part = 
R"""(<html lang="en">
<head>
   <meta charset="UTF-8">
   <meta http-equiv="X-UA-Compatible" content="IE=edge">
   <meta name="viewport" content="width=device-width, initial-scale=1.0">
   <link rel="stylesheet" href="style.css">
   <title>SyntaxSC</title>
</head>
<body>)""";

class HtmlBuilder {
public:
   static void write_html(std::vector<std::string>& html_words) {
      std::string finalstring = first_part;
      for (std::string& word : html_words) {
         if (word == "</br>") {
            finalstring += "\n";
         }
         finalstring += word;
      }
      finalstring += "</body></html>";
      std::ofstream outfile(FILE_NAME);
      outfile << finalstring;
      outfile.close();
   }
};