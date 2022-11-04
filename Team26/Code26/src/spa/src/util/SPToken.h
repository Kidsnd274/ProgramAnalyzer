#include <string>
#ifndef SPA_TOKEN_H
#define SPA_TOKEN_H

enum class SPTokenType {
    LParenToken,
    RParenToken,
    LCurlyToken,
    RCurlyToken,
    AssignToken,
    RelationToken,
    CondToken,
    OpToken,
    ErrorToken,
    ConstToken,
    NameToken,
    ReadToken,
    PrintToken,
    IfToken,
    ThenToken,
    ElseToken,
    WhileToken,
    ProcedureToken,
    CallToken,
    SemiColonToken,
    FactorToken,
};

class SPToken {
private:
    SPTokenType tokenType;
    std::string tokenString;

public:
    SPToken(std::string s, SPTokenType tt) {
        tokenString = s;
        tokenType = tt;
    }

    SPTokenType getTokenType() const;
    std::string getTokenString() const;
    bool isNonTerminal();
};

bool operator== (const SPToken &leftToken, const SPToken &rightToken);
bool operator!= (const SPToken &leftToken, const SPToken &rightToken);
#endif
