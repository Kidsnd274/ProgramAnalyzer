#pragma once

#include "Token.h"

TokenType Token::getTokenType() const {
    return tokenType;
}

std::string Token::getTokenString() const {
    return tokenString;
}

bool operator== (const Token &leftToken, const Token &rightToken) {
    bool cond1 = leftToken.getTokenType() == rightToken.getTokenType();
    bool cond2 = leftToken.getTokenString() == rightToken.getTokenString();
    if (cond1 && cond2) {
        return true;
    }
    return false;
}