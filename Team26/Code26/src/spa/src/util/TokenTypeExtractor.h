#pragma  once
#ifndef SPA_TOKENTYPEEXTRACTOR_H
#define SPA_TOKENTYPEEXTRACTOR_H
#include <unordered_map>
#include "Token.h"

class TokenTypeExtractor {
public:
    static std::unordered_map<std::string, TokenType> terminalTokenMap;
    static std::unordered_map<std::string, TokenType> nonTerminalTokenMap;

    static Token createTerminal(std::string s);
    static Token createNonTerminal(std::string s);
    static Token createConst(std::string s);
};
#endif