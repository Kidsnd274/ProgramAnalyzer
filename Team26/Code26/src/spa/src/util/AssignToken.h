#include "Token.h"

class AssignToken : public Token {
public:
    AssignToken(std::string token) : Token(token) {}
};