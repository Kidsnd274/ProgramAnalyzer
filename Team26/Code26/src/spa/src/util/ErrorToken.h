#include "Token.h"

class ErrorToken : public Token {
public:
    ErrorToken(std::string token) : Token(token) {}
};