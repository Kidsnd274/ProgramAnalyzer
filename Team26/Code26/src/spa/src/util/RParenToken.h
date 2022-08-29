#include "Token.h"

class RParenToken : public Token {
public:
    RParenToken(std::string token) : Token(token) {}
};