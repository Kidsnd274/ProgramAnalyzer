#include "Lexer.h"
#include <sstream>

void Lexer::splitWord(std::vector<Token> &res, std::string &toParse) {
    int i = 0;
    while(i < toParse.size()) {
        char c = toParse[i];
        //Guard clause to filter out unwanted characters
        if(c == '\t' || c == '\n' || c == '\r') {
            i++;
            continue;
        }

        if(std::isdigit(c)) {
            int j = i;
            while(j < toParse.size() && std::isdigit(toParse[j])) {
                j++;
            }
            Token token = Token::createConstToken(toParse.substr(i, j-i));
            res.push_back(token);
            i = j;
        } else if(std::isalnum(c)) {
            int j = i;
            while(j < toParse.size() && std::isalnum(toParse[j])) {
                j++;
            }
            Token token = Token::createNonTerminal(toParse.substr(i, j-i));
            res.push_back(token);
            i = j;
        } else if((c == '<' || c == '>' || c == '=' || c == '!') && (i + 1 < toParse.size() && toParse[i+1] == '=')){
            Token token = Token::createTerminal(toParse.substr(i, 2));
            res.push_back(token);
            i = i + 2;
        } else if((c == '|' || c == '&') && (i + 1 < toParse.size() && toParse[i+1] == c)){
            Token token = Token::createTerminal(toParse.substr(i, 2));
            res.push_back(token);
            i = i + 2;
        } else {
            //in case of junk unaccepted characters, just add it into the list first and deal with it later to ensure progress.
            Token token = Token::createTerminal(toParse.substr(i, 1));
            res.push_back(token);
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

std::vector<std::string> Lexer::delimitBySpaceUsingFS() {
    std::vector<std::string> result;
    std::string rawInput;

    while (std::getline(*fileStream, rawInput, ' ')) {
        if (rawInput == "") continue;
        result.push_back(rawInput);
    }

    return result;
}

std::vector<Token> Lexer::tokenize() {
    std::vector<std::string> firstPass = delimitBySpace();
    std::vector<Token> result;

    for(auto &s : firstPass) {
        splitWord(result, s);
    }

    return result;
}

