#include "Lexer.h"
#include <sstream>

void Lexer::splitWord(std::vector<std::string> &res, std::string &toParse) {
    int i = 0;
    while(i < toParse.size()) {
        char c = toParse[i];
        //Guard clause to filter out unwanted characters
        if(c == '\t' || c == '\n' || c == '\r') {
            i++;
            continue;
        }

        if(std::isalnum(c)) {
            int j = i;
            while(j < toParse.size() && std::isalnum(toParse[j])) {
                j++;
            }
            res.push_back(toParse.substr(i, j-i));
            i = j;
        } else if((c == '<' || c == '>' || c == '=' || c == '!') && (i + 1 < toParse.size() && toParse[i+1] == '=')){
            res.push_back(toParse.substr(i, 2));
            i = i + 2;
        } else if((c == '|' || c == '&') && (i + 1 < toParse.size() && toParse[i+1] == c)){
            res.push_back(toParse.substr(i, 2));
            i = i + 2;
        } else {
            //in case of junk unaccepted characters, just add it into the list first and deal with it later to ensure progress.
            res.push_back(toParse.substr(i, 1));
            i++;
        }
    }

    return;
}

std::vector<std::string> Lexer::delimitBySpace() {
    std::stringstream stream(source);
    std::vector<std::string> result;
    std::string rawInput;

    while(std::getline(stream, rawInput, ' ')) {
        if(rawInput == "") continue;
        result.push_back(rawInput);
    }

    return result;
}

std::vector<std::string> Lexer::tokenize() {
    std::vector<std::string> firstPass = delimitBySpace();
    std::vector<std::string> result;

    for(auto &s : firstPass) {
        splitWord(result, s);
    }

    return result;
}

