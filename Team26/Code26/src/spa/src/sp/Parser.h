#pragma once

#include <memory>
#include <vector>
#include "util/TokenStack.h"
#include "SyntaxErrorException.h"
#include "util/ast/ProcedureNode.h"
#include "util/ast/AssignNode.h"
#include "util/ast/WhileNode.h"
#include "util/ast/IfNode.h"
#include "util/ast/PrintNode.h"
#include "util/ast/ReadNode.h"
#include "util/ast/ITermNode.h"

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
    void parseConst();
    void parseTerm();
    void parseFactor();
    void parseOp();
    void parseFactorToken();
};