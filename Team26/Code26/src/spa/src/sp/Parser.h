#pragma once

#include <memory>
#include <vector>
#include "util/TokenStack.h"
#include "SyntaxErrorException.h"
#include "util/ast/TNode.h"
#include "de/DesignExtractor.h"

class Parser {
private:
    TokenStack* tokenStack;
    int statementCount;
    int statementListNumber;
    PKBInterface* pkbInterface;
    //TODO sam help me check if there is a need to destroy this pointer
    DesignExtractorInterface* de;

public:
    Parser(std::vector<SPToken> ts, PKBInterface* pkbParserInterface) {
        tokenStack = new TokenStack(ts);
        statementCount = 1;
        statementListNumber = 1;
        pkbInterface = pkbParserInterface;
        de = new DesignExtractor(pkbInterface);
    }

    ~Parser() {
        delete tokenStack;
        delete de;
    }

    void parseSimple();
    std::shared_ptr<ProcedureNode> parseProcedure();

    //Methods that return shared_ptr to StatementNode
    std::vector<std::shared_ptr<StatementNode>> parseStatementList();

    std::shared_ptr<StatementNode> parseStatement(int stmtListNum);
    std::shared_ptr<IfNode> parseIf(int stmtListNum);
    std::shared_ptr<WhileNode> parseWhile(int stmtListNum);
    std::shared_ptr<AssignNode> parseAssign(int stmtListNum);
    std::shared_ptr<ReadNode> parseRead(int stmtListNum);
    std::shared_ptr<PrintNode> parsePrint(int stmtListNum);
    std::shared_ptr<CallNode> parseCall(int stmtListNum);

    //Methods that return shared_ptr to TNode
    std::shared_ptr<TNode> parseCond();
    std::shared_ptr<TNode> parseRelFactor();
    std::shared_ptr<TNode> parseRel();
    std::shared_ptr<TNode> parseExpression();
    std::shared_ptr<TNode> parseTerm();
    std::shared_ptr<TNode> parseFactor();

    //Methods that validates and returns the value of a token
    std::string parseName();
    std::string parseConst();

    //Methods that validates a token
    void parseLCurly();
    void parseRCurly();
    void parseLParen();
    void parseRParen();
    void parseAssignToken();
    void parseSemiColon();
    void parseThen();
    void parseElse();
    void parseCondToken();
    void parseRelationToken();
    void parseOp();
    void parseFactorToken();
};