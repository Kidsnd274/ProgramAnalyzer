#pragma once

#include <vector>
#include "util/TokenStack.h"

class Parser {
private:
    TokenStack* tokenStack;

public:
    Parser(std::vector<Token> ts) {
        tokenStack = new TokenStack(ts);
    }
};