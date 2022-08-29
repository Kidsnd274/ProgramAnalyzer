#include "Token.h"

class RCurlyToken : public Token {
public:
    RCurlyToken(std::string token) : Token(token) {}
};