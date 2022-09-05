#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "TokenTypeExtractor.h"

class Lexer {
private:
    std::string source;

    // Testing delimiter using fstream
    std::fstream *fileStream;
public:
    Lexer(std::string in) {
        source = in;
    }
    Lexer(std::fstream *fileStream) {
        this->fileStream = fileStream;
    }
    void splitWord(std::vector<Token>&, std::string&);
    std::vector<std::string> delimitBySpace();
    std::vector<std::string> delimitBySpaceUsingFS();
    std::vector<Token> tokenize();
};

