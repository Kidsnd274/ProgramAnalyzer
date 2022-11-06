#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "SyntaxErrorException.h"
#include "util/Common.h"
#include "util/Lexer.h"
#include "util/TokenStack.h"
#include "util/ast/TNode.h"
#include "util/cfg/CFGManager.h"
#include "de/DesignExtractor.h"

class Parser {
private:
    TokenStack* tokenStack;
    int statementCount;
    STMT_LIST_NUM statementListNumber;
    PKBInterface* pkbInterface;
    DesignExtractorInterface* de;
    std::shared_ptr<CFGManager> cfgManager;

    explicit Parser(std::vector<SPToken> ts) {
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

    // Methods related to pkb
    void addVariableToPkbIfExist(std::string var);
    void addConstToPkbIfExist(std::string cons);

    // Methods that return shared_ptr to StatementNode
    std::vector<std::shared_ptr<StatementNode>> parseStatementList();
    std::shared_ptr<StatementNode> parseStatement(STMT_LIST_NUM stmtListNum);
    std::shared_ptr<IfNode> parseIf(STMT_LIST_NUM stmtListNum);
    std::shared_ptr<WhileNode> parseWhile(STMT_LIST_NUM stmtListNum);
    std::shared_ptr<AssignNode> parseAssign(STMT_LIST_NUM stmtListNum);
    std::shared_ptr<StatementNode> parseRead(STMT_LIST_NUM stmtListNum);
    std::shared_ptr<StatementNode> parsePrint(STMT_LIST_NUM stmtListNum);
    std::shared_ptr<CallNode> parseCall(STMT_LIST_NUM stmtListNum);

    // Methods that return shared_ptr to TNode
    std::shared_ptr<TNode> parseCond();
    std::shared_ptr<TNode> parseRel();
    std::shared_ptr<TNode> parseExpression();
    std::shared_ptr<TNode> parseTerm();
    std::shared_ptr<TNode> parseFactor();
    std::shared_ptr<StatementNode> parseReadAndPrint(SPTokenType type, STMT_LIST_NUM stmtListNum);

    // Methods for QPS
    static std::shared_ptr<TNode> parseExpressionFromString(std::string exprString);
};
