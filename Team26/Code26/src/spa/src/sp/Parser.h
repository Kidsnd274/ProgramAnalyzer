#pragma once

#include <memory>
#include <utility>
#include <vector>
#include "SyntaxErrorException.h"
#include "util/Lexer.h"
#include "util/TokenStack.h"
#include "util/ast/TNode.h"
#include "util/cfg/CFGManager.h"
#include "de/DesignExtractor.h"

class Parser {
private:
    TokenStack* tokenStack;
    int statementCount;
    int statementListNumber;
    PKBInterface* pkbInterface;
    DesignExtractorInterface* de;
    std::shared_ptr<CFGManager> cfgManager;

    Parser(std::vector<SPToken> ts) {
        tokenStack = new TokenStack(std::move(ts));
        this->statementCount = 1;
        this->statementListNumber = 1;
        pkbInterface = nullptr;
        de = nullptr;
        cfgManager = std::make_shared<CFGManager>();
    }

public:
    Parser(std::vector<SPToken> ts, PKBInterface* pkbParserInterface) {
        tokenStack = new TokenStack(ts);
        statementCount = 1;
        statementListNumber = 1;
        pkbInterface = pkbParserInterface;
        de = new DesignExtractor(pkbInterface);
        cfgManager = std::make_shared<CFGManager>();
    }

    // For testing CFG Generation
    Parser(std::vector<SPToken> ts, PKBInterface* pkbParserInterface, std::shared_ptr<CFGManager> cfgManager) {
        tokenStack = new TokenStack(ts);
        statementCount = 1;
        statementListNumber = 1;
        pkbInterface = pkbParserInterface;
        de = new DesignExtractor(pkbInterface);
        this->cfgManager = std::move(cfgManager);

    }

    ~Parser() {
        delete tokenStack;
        tokenStack = nullptr;
        delete de;
        de = nullptr;
        cfgManager = nullptr;
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

    // Methods for QPS
    static std::shared_ptr<TNode> parseExpressionFromString(std::string exprString);
};