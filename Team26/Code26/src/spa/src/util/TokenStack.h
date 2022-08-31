#pragma  once
#include <vector>
#include "Token.h"

class TokenStack {
private:
    std::vector<Token> tokenStack;
    int tokenPointer;

public:
    TokenStack(std::vector<Token> ts) {
        tokenStack = ts;
    }
    Token getNext();
    bool hasNextToken();
    Token peekNext();
};