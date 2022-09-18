#pragma  once
#include <vector>
#include <stack>
#include "SPToken.h"
#include "EndOfFileException.h"

class TokenStack {
private:
    std::vector<SPToken> tokenStack;
    int tokenPointer;

public:
    TokenStack(std::vector<SPToken> ts) {
        tokenPointer = 0;
        tokenStack = ts;
    }
    SPToken getNext();
    bool hasNextToken();
    SPToken peekNext();
    bool isNextTokenAssign();
    bool isCondTokenAfterRparen();
};