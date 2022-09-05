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