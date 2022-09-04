#pragma  once
#include <vector>
#include "Token.h"
#include "EndOfFileException.h"

class TokenStack {
private:
    std::vector<Token> tokenStack;
    int tokenPointer;

public:
    TokenStack(std::vector<Token> ts) {
        tokenPointer = 0;
        tokenStack = ts;
    }
    Token getNext();
    bool hasNextToken();
    Token peekNext();
};