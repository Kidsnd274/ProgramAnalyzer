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
    WhileToken,
    ProcedureToken,
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
};