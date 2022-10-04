#include "TokenStack.h"

std::string TokenStack::checkAndReturnNextToken(SPTokenType tokenType) {
    if(tokenType == SPTokenType::NameToken) {
        if(!peekNext().isNonTerminal()) {
            throw SyntaxErrorException();
        }
    }
    std::string val = getNext().getTokenString();
    return val;
}

SPTokenType TokenStack::peekNextTokenType() {
    return peekNext().getTokenType();
}

bool TokenStack::isNextTokenNonTerminal() {
    return peekNext().isNonTerminal();
}

bool TokenStack::isNextTokenOfType(SPTokenType tokenType) {
    return peekNext().getTokenType() == tokenType;
}

void TokenStack::checkAndUseNextToken(SPTokenType tokenType) {
    if(getNext().getTokenType() != tokenType) {
        throw SyntaxErrorException();
    }
}

SPToken TokenStack::getNext() {
    if(!hasNextToken()) {
        throw EndOfFileException();
    }

    return tokenStack[tokenPointer++];
}

bool TokenStack::hasNextToken() {
    return tokenPointer < tokenStack.size();
}
SPToken TokenStack::peekNext() {
    if(!hasNextToken()) {
        throw EndOfFileException();
    }

    return tokenStack[tokenPointer];
}

bool TokenStack::isNextTokenAssign() {
    return (tokenPointer + 1) < tokenStack.size() && tokenStack[tokenPointer + 1].getTokenType() == SPTokenType::AssignToken;
}

bool TokenStack::isCondTokenAfterRparen() {
    int j = tokenPointer + 1;
    std::stack<char> parenStack;
    parenStack.push('l');
    while(j < tokenStack.size() && !parenStack.empty()) {
        if(tokenStack[j].getTokenType() == SPTokenType::RParenToken && parenStack.top() == 'l')
            parenStack.pop();
        else if(tokenStack[j].getTokenType() == SPTokenType::RParenToken)
            parenStack.push('r');
        else if( tokenStack[j].getTokenType() == SPTokenType::LParenToken)
            parenStack.push('l');
        j++;
    }

    return (tokenStack[j].getTokenType() == SPTokenType::CondToken) &&
    (tokenStack[j].getTokenString() == "&&" || tokenStack[j].getTokenString() == "||");
}