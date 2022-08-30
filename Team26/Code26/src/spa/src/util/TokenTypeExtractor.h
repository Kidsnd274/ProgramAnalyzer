#include <map>
#include "Token.h"

class TokenTypeExtractor {
public:
    static std::map<std::string, TokenType> terminalTokenMap;
    static std::map<std::string, TokenType> nonTerminalTokenMap;

    static Token createTerminal(std::string s);
    static Token createNonTerminal(std::string s);
    static Token createConst(std::string s);
};