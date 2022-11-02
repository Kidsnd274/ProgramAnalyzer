#pragma  once
#include <utility>
#include <vector>
#include <stack>
#include <string>
#include "SPToken.h"
#include "EndOfFileException.h"
#include "sp/SyntaxErrorException.h"

class TokenStack {
private:
    std::vector<SPToken> tokenStack;
    int tokenPointer;

public:
    explicit TokenStack(std::vector<SPToken> ts) {
        tokenPointer = 0;
        tokenStack = std::move(ts);
    }
    SPToken getNext();
    bool hasNextToken();
    SPToken peekNext();
    bool isNextTokenAssign();
    bool isCondTokenAfterRparen();
    bool checkAndUseNextToken(SPTokenType tokenType);
    bool isNextTokenOfType(SPTokenType tokenType);
    bool isNextTokenNonTerminal();
    bool isNextTokenNotOfType(SPTokenType tokenType);
    bool isNextTokenStringEquals(std::string s);
    SPTokenType peekNextTokenType();
    std::string peekNextTokenString();
    std::string checkAndReturnNextToken(SPTokenType tokenType);
};
