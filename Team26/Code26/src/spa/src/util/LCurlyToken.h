#include "Token.h"

class LCurlyToken : public Token {
public:
    LCurlyToken(std::string token) : Token(token) {}
};