#pragma once

#include <unordered_set>
#include "util/TokenStack.h"
#include "SyntaxErrorException.h"

class Parser {
private:
    TokenStack* tokenStack;
    int statementCount;

public:
    Parser(std::vector<Token> ts) {
        tokenStack = new TokenStack(ts);
        statementCount = 1;
    }

    ~Parser() {
        delete tokenStack;
    }

    std::unordered_set<std::string> variables;
    std::unordered_set<std::string> constants;
    std::vector<int> assigns;
    std::vector<int> whiles;
    std::vector<int> ifs;
    std::vector<int> reads;
    std::vector<int> prints;
    std::vector<int> calls;

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
    void parseAssignToken();
    void parseSemiColon();
    void parseThen();
    void parseElse();
    void parseCondToken();
    void parseRelFactor();
    void parseRelationToken();
    std::string parseConst();
    void parseTerm();
    void parseFactor();
    void parseOp();
    void parseFactorToken();
};