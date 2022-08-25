#pragma once

#include <string>
#include <vector>
class Lexer {
private:
    std::string source;
public:
    Lexer(std::string in) {
        source = in;
    }
    void splitWord(std::vector<std::string>&, std::string&);
    std::vector<std::string> delimitBySpace();
    std::vector<std::string> tokenize();
};

