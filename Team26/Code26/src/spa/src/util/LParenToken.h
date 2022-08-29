#include "Token.h"

class LParenToken : public Token {
public:
    LParenToken(std::string token) : Token(token) {}
};