#include "TokenStack.h"

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