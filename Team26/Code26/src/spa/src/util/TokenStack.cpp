#include "TokenStack.h"

Token TokenStack::getNext() {
    if(!hasNextToken()) {
        //throw EndOfFileException
    }

    return tokenStack[tokenPointer++];
}

bool TokenStack::hasNextToken() {
    return tokenPointer < tokenStack.size();
}
Token TokenStack::peekNext() {
    if(!hasNextToken()) {
        //throw EndOfFileException
    }

    return tokenStack[tokenPointer];
}