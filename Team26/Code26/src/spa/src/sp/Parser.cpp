#include "Parser.h"

void Parser::parseSimple() {
    int numOfProcedures = 0;
    std::vector<std::shared_ptr<ProcedureNode>> procedures;
    while (tokenStack->hasNextToken()) {
        tokenStack->checkAndUseNextToken(SPTokenType::ProcedureToken);
        std::shared_ptr<ProcedureNode> pn = parseProcedure();
        procedures.push_back(pn);
        numOfProcedures++;
    }

    if (!numOfProcedures) {
        throw SyntaxErrorException();
    }
    de->extract(procedures);
}

std::shared_ptr<ProcedureNode> Parser::parseProcedure() {
    STMT_NUM currStatement = statementCount;
    std::string name = tokenStack->checkAndReturnNextToken(SPTokenType::NameToken);
    tokenStack->checkAndUseNextToken(SPTokenType::LCurlyToken);
    de->addProcedure(name);
    cfgManager->createNewCFG();
    std::vector<std::shared_ptr<StatementNode>> stmtList = parseStatementList();
    tokenStack->checkAndUseNextToken(SPTokenType::RCurlyToken);
    cfgManager->finalizeFinalNode();
    pkbInterface->addProcedure(name, currStatement, statementCount-1, cfgManager->getCurrentCFG());
    return std::make_shared<ProcedureNode>(name, stmtList);
}


std::vector<std::shared_ptr<StatementNode>> Parser::parseStatementList() {
    STMT_LIST_NUM oldStatementCount = statementCount;
    STMT_LIST_NUM currStatementListNumber = statementListNumber++;
    std::vector<std::shared_ptr<StatementNode>> stmtList;

    while (tokenStack->hasNextToken() && tokenStack->isNextTokenNotOfType(SPTokenType::RCurlyToken)) {
        std::shared_ptr<StatementNode> stmt = parseStatement(currStatementListNumber);
        stmtList.push_back(stmt);
    }

    if (oldStatementCount == statementCount) {
        throw SyntaxErrorException();
    }

    return stmtList;
}

std::shared_ptr<StatementNode> Parser::parseStatement(STMT_LIST_NUM stmtListNum) {
    if (!tokenStack->isNextTokenNonTerminal()) {
        throw SyntaxErrorException();
    }

    SPTokenType t = tokenStack->peekNextTokenType();
    std::shared_ptr<StatementNode> stmt(nullptr);

    if (tokenStack->isNextTokenAssign() && tokenStack->isNextTokenNonTerminal()) {
        stmt = std::move(parseAssign(stmtListNum));
        return stmt;
    }

    switch (t) {
        case SPTokenType::NameToken:
            stmt = std::move(parseAssign(stmtListNum));
            break;
        case SPTokenType::IfToken:
            stmt = std::move(parseIf(stmtListNum));
            break;
        case SPTokenType::WhileToken:
            stmt = std::move(parseWhile(stmtListNum));
            break;
        case SPTokenType::ReadToken:
            stmt = std::move(parseRead(stmtListNum));
            break;
        case SPTokenType::PrintToken:
            stmt = std::move(parsePrint(stmtListNum));
            break;
        case SPTokenType::CallToken:
            stmt = std::move(parseCall(stmtListNum));
            break;
        default:
            throw SyntaxErrorException();
            break;
    }

    return stmt;
}

std::shared_ptr<AssignNode> Parser::parseAssign(STMT_LIST_NUM stmtListNum) {
    STMT_NUM currStatement = statementCount++;

    // consume non-terminal token
    std::string varAssigned = tokenStack->checkAndReturnNextToken(SPTokenType::NameToken);
    pkbInterface->addItem(Entity::VARIABLE, varAssigned, 0);
    tokenStack->checkAndUseNextToken(SPTokenType::AssignToken);
    std::shared_ptr<TNode> expr = std::move(parseExpression());
    tokenStack->checkAndUseNextToken(SPTokenType::SemiColonToken);
    pkbInterface->addAssignStatement(currStatement, stmtListNum, expr);
    cfgManager->addStandardNode(currStatement);

    return AssignNode::createAssignNode(currStatement, varAssigned, expr);
}

std::shared_ptr<IfNode> Parser::parseIf(STMT_LIST_NUM stmtListNum) {
    tokenStack->checkAndUseNextToken(SPTokenType::IfToken);  // consume If SPToken.
    STMT_NUM currStatement = statementCount++;
    cfgManager->addStandardNode(currStatement);

    tokenStack->checkAndUseNextToken(SPTokenType::LParenToken);
    std::shared_ptr<TNode> cond = std::move(parseCond());
    tokenStack->checkAndUseNextToken(SPTokenType::RParenToken);

    tokenStack->checkAndUseNextToken(SPTokenType::ThenToken);
    tokenStack->checkAndUseNextToken(SPTokenType::LCurlyToken);
    std::vector<std::shared_ptr<StatementNode>> ifStatementList = parseStatementList();
    tokenStack->checkAndUseNextToken(SPTokenType::RCurlyToken);
    cfgManager->finalizeIfPortionOfIfStatement(currStatement);

    tokenStack->checkAndUseNextToken(SPTokenType::ElseToken);
    tokenStack->checkAndUseNextToken(SPTokenType::LCurlyToken);
    std::vector<std::shared_ptr<StatementNode>> elseStatementList = parseStatementList();
    tokenStack->checkAndUseNextToken(SPTokenType::RCurlyToken);
    cfgManager->finalizeElsePortionOfIfStatement(currStatement);  // Connects last else stmt to DummyNode

    pkbInterface->addIfStatement(currStatement, stmtListNum);
    return IfNode::createIfNode(currStatement, cond, ifStatementList, elseStatementList);
}

std::shared_ptr<TNode> Parser::parseCond() {
    if (tokenStack->isNextTokenOfType(SPTokenType::CondToken) && tokenStack->isNextTokenStringEquals("!")) {
        tokenStack->checkAndUseNextToken(SPTokenType::CondToken);
        tokenStack->checkAndUseNextToken(SPTokenType::LParenToken);
        std::shared_ptr<TNode> cond = std::move(parseCond());
        tokenStack->checkAndUseNextToken(SPTokenType::RParenToken);

        return TNode::createNOTConditionalExpression(statementCount, "!", cond);
    } else if (tokenStack->isNextTokenOfType(SPTokenType::LParenToken) && tokenStack->isCondTokenAfterRparen()) {
        tokenStack->checkAndUseNextToken(SPTokenType::LParenToken);
        std::shared_ptr<TNode> cond = std::move(parseCond());
        tokenStack->checkAndUseNextToken(SPTokenType::RParenToken);
        std::string condToken = tokenStack->peekNextTokenString();
        tokenStack->checkAndUseNextToken(SPTokenType::CondToken);
        tokenStack->checkAndUseNextToken(SPTokenType::LParenToken);
        std::shared_ptr<TNode> cond2 = std::move(parseCond());
        tokenStack->checkAndUseNextToken(SPTokenType::RParenToken);

        return TNode::createConditionalExpression(statementCount, condToken, cond, cond2);
    } else {
        return parseRel();
    }
}

std::shared_ptr<TNode> Parser::parseRel() {
    std::shared_ptr<TNode> relFactor = std::move(parseExpression());
    std::string relToken = tokenStack->peekNextTokenString();
    tokenStack->checkAndUseNextToken(SPTokenType::RelationToken);
    std::shared_ptr<TNode> relFactor2 = std::move(parseExpression());

    return TNode::createRelationalExpression(statementCount, relToken, relFactor, relFactor2);
}

std::shared_ptr<WhileNode> Parser::parseWhile(STMT_LIST_NUM stmtListNum) {
    tokenStack->checkAndUseNextToken(SPTokenType::WhileToken);  // consume While SPToken.
    STMT_NUM currStatement = statementCount++;
    cfgManager->addStandardNode(currStatement);

    tokenStack->checkAndUseNextToken(SPTokenType::LParenToken);
    std::shared_ptr<TNode> cond = std::move(parseCond());
    tokenStack->checkAndUseNextToken(SPTokenType::RParenToken);
    tokenStack->checkAndUseNextToken(SPTokenType::LCurlyToken);
    std::vector<std::shared_ptr<StatementNode>> statementList = parseStatementList();
    tokenStack->checkAndUseNextToken(SPTokenType::RCurlyToken);

    cfgManager->finalizeWhileStatement(currStatement);
    pkbInterface->addWhileStatement(currStatement, stmtListNum);

    return WhileNode::createWhileNode(currStatement, cond, statementList);
}

std::shared_ptr<StatementNode> Parser::parseReadAndPrint(SPTokenType type, STMT_LIST_NUM stmtListNum) {
    tokenStack->checkAndUseNextToken(type);  // consume token
    STMT_NUM currStatement = statementCount++;
    std::string varName = tokenStack->checkAndReturnNextToken(SPTokenType::NameToken);
    pkbInterface->addItem(Entity::VARIABLE, varName, 0);
    tokenStack->checkAndUseNextToken(SPTokenType::SemiColonToken);

    cfgManager->addStandardNode(currStatement);

    if (type == SPTokenType::ReadToken) {
        pkbInterface->addReadStatement(currStatement, stmtListNum);
        return ReadNode::createReadNode(currStatement, varName);
    } else {
        pkbInterface->addPrintStatement(currStatement, stmtListNum);
        return PrintNode::createPrintNode(currStatement, varName);
    }
}

std::shared_ptr<StatementNode> Parser::parseRead(STMT_LIST_NUM stmtListNum) {
    return parseReadAndPrint(SPTokenType::ReadToken, stmtListNum);
}

std::shared_ptr<StatementNode> Parser::parsePrint(STMT_LIST_NUM stmtListNum) {
    return parseReadAndPrint(SPTokenType::PrintToken, stmtListNum);
}


std::shared_ptr<CallNode> Parser::parseCall(STMT_LIST_NUM stmtListNum) {
    tokenStack->checkAndUseNextToken(SPTokenType::CallToken);  // consume Call SPToken.
    STMT_NUM currStatement = statementCount++;
    std::string varName = tokenStack->checkAndReturnNextToken(SPTokenType::NameToken);
    tokenStack->checkAndUseNextToken(SPTokenType::SemiColonToken);

    CallStruct cs(currStatement, varName);
    de->addCallStatement(cs);

    cfgManager->addStandardNode(currStatement);
    pkbInterface->addCallStatement(currStatement, stmtListNum, varName);
    return CallNode::createCallNode(currStatement, varName);
}

std::shared_ptr<TNode> Parser::parseExpression() {
    std::shared_ptr<TNode> base = std::move(parseTerm());

    while (tokenStack->isNextTokenOfType(SPTokenType::OpToken)) {
        std::string operand = tokenStack->peekNextTokenString();
        tokenStack->checkAndUseNextToken(SPTokenType::OpToken);
        std::shared_ptr<TNode> term2 = std::move(parseTerm());
        base = TNode::createTerm(statementCount, operand, base, term2);
    }

    return base;
}

std::shared_ptr<TNode> Parser::parseTerm() {
    std::shared_ptr<TNode> base = std::move(parseFactor());

    while (tokenStack->isNextTokenOfType(SPTokenType::FactorToken)) {
        std::string operand = tokenStack->peekNextTokenString();
        tokenStack->checkAndUseNextToken(SPTokenType::FactorToken);
        std::shared_ptr<TNode> factor2 = std::move(parseFactor());

        base = TNode::createTerm(statementCount, operand, base, factor2);
    }

    return base;
}

std::shared_ptr<TNode> Parser::parseFactor() {
    if (tokenStack->isNextTokenNonTerminal()) {
        std::string name = tokenStack->checkAndReturnNextToken(SPTokenType::NameToken);
        addVariableToPkbIfExist(name);

        return TNode::createVariableName(statementCount, name);
    } else if (tokenStack->isNextTokenOfType(SPTokenType::ConstToken)) {
        std::string constant = tokenStack->checkAndReturnNextToken(SPTokenType::ConstToken);
        addConstToPkbIfExist(constant);

        return TNode::createConstantValue(statementCount, constant);
    } else {
        tokenStack->checkAndUseNextToken(SPTokenType::LParenToken);
        std::shared_ptr<TNode> expr = std::move(parseExpression());
        tokenStack->checkAndUseNextToken(SPTokenType::RParenToken);

        return expr;
    }
}

std::shared_ptr<TNode> Parser::parseExpressionFromString(std::string exprString) {
    Lexer lexer(std::move(exprString));
    std::vector<SPToken> tokenStack = lexer.tokenize();
    Parser customParser = Parser(std::move(tokenStack));

    return customParser.parseExpression();
}

void Parser::addVariableToPkbIfExist(std::string var) {
    if (pkbInterface) {
        pkbInterface->addItem(Entity::VARIABLE, var, 0);
    }
}

void Parser::addConstToPkbIfExist(std::string cons) {
    if (pkbInterface) {
        pkbInterface->addItem(Entity::CONSTANT, "", std::stoi(cons));
    }
}
