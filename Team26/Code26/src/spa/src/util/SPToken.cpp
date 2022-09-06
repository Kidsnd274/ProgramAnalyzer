#include "SPToken.h"

SPTokenType SPToken::getTokenType() const {
    return tokenType;
}

std::string SPToken::getTokenString() const {
    return tokenString;
}

bool SPToken::isNonTerminal() {
    return
            tokenType == SPTokenType::NameToken || tokenType == SPTokenType::ProcedureToken ||
            tokenType == SPTokenType::CallToken || tokenType == SPTokenType::IfToken ||
            tokenType == SPTokenType::ElseToken || tokenType == SPTokenType::WhileToken ||
            tokenType == SPTokenType::ThenToken || tokenType == SPTokenType::ReadToken ||
            tokenType == SPTokenType::PrintToken;
}

bool operator== (const SPToken &leftToken, const SPToken &rightToken) {
    bool cond1 = leftToken.getTokenType() == rightToken.getTokenType();
    bool cond2 = leftToken.getTokenString() == rightToken.getTokenString();
    if (cond1 && cond2) {
        return true;
    }
    return false;
}