#include <vector>
#include "Token.h"

class TokenStack {
private:
    std::vector<Token> tokenStack;
    int tokenPointer;

public:
    Token getNext();
    bool hasNextToken();
    Token peekNext();
};