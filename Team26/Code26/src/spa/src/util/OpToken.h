#include "Token.h"

class OpToken : public Token {
public:
    OpToken(std::string token) : Token(token) {}
};