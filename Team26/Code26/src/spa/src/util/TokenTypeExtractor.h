#include <map>
#include "Token.h"

class TokenTypeExtractor {
public:
    static Token createTerminalToken(std::string s);
    static Token createNonTerminalToken(std::string s);
    static Token createConstToken(std::string s);

    static std::map<std::string, TokenType> terminalTokenMap;
    static std::map<std::string, TokenType> nonTerminalTokenMap;
};