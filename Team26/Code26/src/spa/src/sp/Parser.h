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

    ~Parser() {
        delete tokenStack;
    }
    void parseSimple();
    void parseProcedure();
    void parseStatementList();
    void parseStatement();
    void parseIf();
    void parseAssign();
    void parseRead();
    void parsePrint();
    void parseCall();
    void parseCond();
    void parseRel();
    std::string parseName();
    void parseLCurly();
    void parseRCurly();
    void parseLParen();
    void parseRParen();
    void parseExpression();
    void parseWhile();
};