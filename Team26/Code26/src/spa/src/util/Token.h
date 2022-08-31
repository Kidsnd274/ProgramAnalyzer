#include <string>

enum class TokenType {
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
    ExclaimationToken,
};

class Token {
private:
    TokenType tokenType;
    std::string tokenString;

public:
    Token(std::string s, TokenType tt) {
        tokenString = s;
        tokenType = tt;
    }

    TokenType getTokenType() const;
    std::string getTokenString() const;
    bool isNonTerminal();
};

bool operator== (const Token &leftToken, const Token &rightToken);