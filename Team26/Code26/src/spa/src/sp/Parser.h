#pragma once

#include <memory>
#include <vector>
#include "util/TokenStack.h"
#include "SyntaxErrorException.h"
#include "util/ast/TNode.h"
#include "util/ast/ProcedureNode.h"
#include "util/ast/AssignNode.h"
#include "util/ast/IfNode.h"
#include "util/ast/WhileNode.h"
#include "util/ast/ReadNode.h"
#include "util/ast/PrintNode.h"
#include "util/ast/CallNode.h"

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
    std::shared_ptr<ProcedureNode> parseProcedure();
    std::vector<std::shared_ptr<StatementNode>> parseStatementList();
    std::shared_ptr<StatementNode> parseStatement();
    std::shared_ptr<IfNode> parseIf();
    std::shared_ptr<AssignNode> parseAssign();
    std::shared_ptr<ReadNode> parseRead();
    std::shared_ptr<PrintNode> parsePrint();
    std::shared_ptr<CallNode> parseCall();
    std::shared_ptr<TNode> parseCond();
    std::shared_ptr<TNode> parseRel();
    std::string parseName();
    void parseLCurly();
    void parseRCurly();
    void parseLParen();
    void parseRParen();
    std::shared_ptr<TNode> parseExpression();
    std::shared_ptr<WhileNode> parseWhile();
    void parseAssignToken();
    void parseSemiColon();
    void parseThen();
    void parseElse();
    void parseCondToken();
    std::shared_ptr<TNode> parseRelFactor();
    void parseRelationToken();
    std::string parseConst();
    std::shared_ptr<TNode> parseTerm();
    std::shared_ptr<TNode> parseFactor();
    void parseOp();
    void parseFactorToken();
};