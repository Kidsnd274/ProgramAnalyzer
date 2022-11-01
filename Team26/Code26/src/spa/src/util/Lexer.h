#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "TokenTypeExtractor.h"

class Lexer {
private:
    std::string source;
public:
    explicit Lexer(std::string in) {
        source = in;
    }
    void splitWord(std::vector<SPToken>&, std::string&);
    std::vector<std::string> delimitBySpace();
    std::vector<SPToken> tokenize();
};
