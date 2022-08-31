#include "TokenStack.h"

Token TokenStack::getNext() {
    return tokenStack[tokenPointer++];
}

bool TokenStack::hasNextToken() {
    return tokenPointer < tokenStack.size();
}
Token TokenStack::peekNext() {
    return tokenStack[tokenPointer];
}