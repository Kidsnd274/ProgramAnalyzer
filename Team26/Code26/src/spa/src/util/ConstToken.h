#include "Token.h"

class ConstToken : public Token {
public:
    ConstToken(std::string token) : Token(token) {}
};