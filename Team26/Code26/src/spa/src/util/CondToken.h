#include "Token.h"

class CondToken : public Token {
public:
    CondToken(std::string token) : Token(token) {}
};