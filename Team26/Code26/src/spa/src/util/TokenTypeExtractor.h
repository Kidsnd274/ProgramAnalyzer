#pragma once
#ifndef SPA_TOKENTYPEEXTRACTOR_H
#define SPA_TOKENTYPEEXTRACTOR_H

#include <string>
#include <unordered_map>
#include "SPToken.h"
#include "sp/SyntaxErrorException.h"

class TokenTypeExtractor {
public:
    static std::unordered_map<std::string, SPTokenType> terminalTokenMap;
    static std::unordered_map<std::string, SPTokenType> nonTerminalTokenMap;

    static SPToken createTerminal(std::string s);
    static SPToken createNonTerminal(std::string s);
    static SPToken createConst(std::string s);
};
#endif
