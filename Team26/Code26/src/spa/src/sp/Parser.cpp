#include "Parser.h"

#include <utility>
#include "pkb/PKB.h"

void Parser::parseSimple() {
    int numOfProcedures = 0;
    std::vector<std::shared_ptr<ProcedureNode>> procedures;
    while(tokenStack->hasNextToken()) {
        tokenStack->checkAndUseNextToken(SPTokenType::ProcedureToken);
        std::shared_ptr<ProcedureNode> pn = parseProcedure();
        procedures.push_back(pn);
        numOfProcedures++;
    }

    if(!numOfProcedures){
        throw SyntaxErrorException();
    }
    de->extract(procedures);
}

std::shared_ptr<ProcedureNode> Parser::parseProcedure() {
    int currStatement = statementCount;
    std::string name = tokenStack->checkAndReturnNextToken(SPTokenType::NameToken);
    tokenStack->checkAndUseNextToken(SPTokenType::LCurlyToken);
    de->addProcedure(name);
    cfgManager->createNewCFG();
    std::vector<std::shared_ptr<StatementNode>> stmtList = parseStatementList();
    tokenStack->checkAndUseNextToken(SPTokenType::RCurlyToken);
    cfgManager->finalizeFinalNode();
    pkbInterface->addProcedure(name, currStatement, statementCount-1, cfgManager->getCurrentCFG());
    return make_shared<ProcedureNode>(name, stmtList);
}


std::vector<std::shared_ptr<StatementNode>> Parser::parseStatementList() {
    int oldStatementCount = statementCount;
    int currStatementListNumber = statementListNumber++;
    std::vector<std::shared_ptr<StatementNode>> stmtList;

    while(tokenStack->hasNextToken() && tokenStack->isNextTokenNotOfType(SPTokenType::RCurlyToken)) {
        std::shared_ptr<StatementNode> stmt = parseStatement(currStatementListNumber);
        stmtList.push_back(stmt);
    }

    if(oldStatementCount == statementCount){
        throw SyntaxErrorException();
    }

    return stmtList;
}

std::shared_ptr<StatementNode> Parser::parseStatement(int stmtListNum) {
    if(!tokenStack->isNextTokenNonTerminal()) {
        throw SyntaxErrorException();
    }

    SPTokenType t = tokenStack->peekNextTokenType();
    std::shared_ptr<StatementNode> stmt(nullptr);

    if(tokenStack->isNextTokenAssign() && tokenStack->isNextTokenNonTerminal()) {
        stmt = std::move(parseAssign(stmtListNum));
        return stmt;
    }

    switch(t) {
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

std::shared_ptr<AssignNode> Parser::parseAssign(int stmtListNum) {
    int currStatement = statementCount++;

    // consume non-terminal token
    string varAssigned = tokenStack->checkAndReturnNextToken(SPTokenType::NameToken);
    pkbInterface->addVariable(varAssigned);
    tokenStack->checkAndUseNextToken(SPTokenType::AssignToken);
    std::shared_ptr<TNode> expr = std::move(parseExpression());
    tokenStack->checkAndUseNextToken(SPTokenType::SemiColonToken);
    pkbInterface->addAssignStatement(currStatement, stmtListNum, expr);
    cfgManager->addStandardNode(currStatement);

    return AssignNode::createAssignNode(currStatement, varAssigned, expr);
}

std::shared_ptr<IfNode> Parser::parseIf(int stmtListNum) {
    tokenStack->checkAndUseNextToken(SPTokenType::IfToken); //consume If SPToken.
    int currStatement = statementCount++;
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
    cfgManager->finalizeElsePortionOfIfStatement(currStatement); // Connects last else stmt to DummyNode

    pkbInterface->addIfStatement(currStatement, stmtListNum);
    return IfNode::createIfNode(currStatement, cond, ifStatementList, elseStatementList);
}

std::shared_ptr<TNode> Parser::parseCond() {
    if(tokenStack->isNextTokenOfType(SPTokenType::CondToken) && tokenStack->isNextTokenStringEquals("!")) {
        tokenStack->checkAndUseNextToken(SPTokenType::CondToken);
        tokenStack->checkAndUseNextToken(SPTokenType::LParenToken);
        std::shared_ptr<TNode> cond = std::move(parseCond());
        tokenStack->checkAndUseNextToken(SPTokenType::RParenToken);

        return TNode::createNOTConditionalExpression(statementCount, "!", cond);
    } else if (tokenStack->isNextTokenOfType(SPTokenType::LParenToken) && tokenStack->isCondTokenAfterRparen()) {
        tokenStack->checkAndUseNextToken(SPTokenType::LParenToken);
        std::shared_ptr<TNode> cond = std::move(parseCond());
        tokenStack->checkAndUseNextToken(SPTokenType::RParenToken);
        string condToken = tokenStack->peekNextTokenString();
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
    string relToken = tokenStack->peekNextTokenString();
    tokenStack->checkAndUseNextToken(SPTokenType::RelationToken);
    std::shared_ptr<TNode> relFactor2 = std::move(parseExpression());

    return TNode::createRelationalExpression(statementCount, relToken, relFactor, relFactor2);
}

std::shared_ptr<TNode> Parser::parseRelFactor() {
    if(tokenStack->isNextTokenNonTerminal()) {
        std::string name = tokenStack->checkAndReturnNextToken(SPTokenType::NameToken);
        pkbInterface->addVariable(name);

        return TNode::createVariableName(statementCount, name);
    } else if (tokenStack->isNextTokenOfType(SPTokenType::ConstToken)) {
        std::string constant = tokenStack->checkAndReturnNextToken(SPTokenType::ConstToken);
        pkbInterface->addConst(std::stoi(constant));

        return TNode::createConstantValue(statementCount, constant);
    } else {
        return parseExpression();
    }
}

std::shared_ptr<WhileNode> Parser::parseWhile(int stmtListNum) {
    tokenStack->checkAndUseNextToken(SPTokenType::WhileToken); //consume While SPToken.
    int currStatement = statementCount++;
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

// S1 (Major): DRY - code structure is similar to parsePrint method -> perhaps could combine into 1 method but unsure if it will mess up currStatement = statementCount++ part
std::shared_ptr<ReadNode> Parser::parseRead(int stmtListNum) {
    tokenStack->checkAndUseNextToken(SPTokenType::ReadToken); //consume Read SPToken.
    int currStatement = statementCount++;
    string varName = tokenStack->checkAndReturnNextToken(SPTokenType::NameToken);
    pkbInterface->addVariable(varName);
    tokenStack->checkAndUseNextToken(SPTokenType::SemiColonToken);

    cfgManager->addStandardNode(currStatement);
    pkbInterface->addReadStatement(currStatement, stmtListNum);

    return ReadNode::createReadNode(currStatement, varName);
}

// S1 (Major): DRY - code structure is similar to parseRead method -> perhaps could combine into 1 method but unsure if it will mess up currStatement = statementCount++ part
std::shared_ptr<PrintNode> Parser::parsePrint(int stmtListNum) {
    tokenStack->checkAndUseNextToken(SPTokenType::PrintToken); //consume Print SPToken.
    int currStatement = statementCount++;
    string varName = tokenStack->checkAndReturnNextToken(SPTokenType::NameToken);
    pkbInterface->addVariable(varName);
    tokenStack->checkAndUseNextToken(SPTokenType::SemiColonToken);

    cfgManager->addStandardNode(currStatement);
    pkbInterface->addPrintStatement(currStatement, stmtListNum);

    return PrintNode::createPrintNode(currStatement, varName);
}


std::shared_ptr<CallNode> Parser::parseCall(int stmtListNum) {
    tokenStack->checkAndUseNextToken(SPTokenType::CallToken); //consume Call SPToken.
    int currStatement = statementCount++;
    string varName = tokenStack->checkAndReturnNextToken(SPTokenType::NameToken);
    tokenStack->checkAndUseNextToken(SPTokenType::SemiColonToken);

    CallStruct cs(currStatement, varName);
    de->addCallStatement(cs);

    cfgManager->addStandardNode(currStatement);
    pkbInterface->addCallStatement(currStatement, stmtListNum, varName);
    return CallNode::createCallNode(currStatement, varName);
}

std::shared_ptr<TNode> Parser::parseExpression() {
    std::shared_ptr<TNode> base = std::move(parseTerm());

    while(tokenStack->isNextTokenOfType(SPTokenType::OpToken)) {
        std::string operand = tokenStack->peekNextTokenString();
        tokenStack->checkAndUseNextToken(SPTokenType::OpToken);
        std::shared_ptr<TNode> term2 = std::move(parseTerm());
        base = TNode::createTerm(statementCount, operand, base, term2);
    }

    return base;
}

std::shared_ptr<TNode> Parser::parseTerm() {
    std::shared_ptr<TNode> base = std::move(parseFactor());

    while(tokenStack->isNextTokenOfType(SPTokenType::FactorToken)) {
        std::string operand = tokenStack->peekNextTokenString();
        tokenStack->checkAndUseNextToken(SPTokenType::FactorToken);
        std::shared_ptr<TNode> factor2 = std::move(parseFactor());

        base = TNode::createTerm(statementCount, operand, base, factor2);
    }

    return base;
}

std::shared_ptr<TNode> Parser::parseFactor() {
    if(tokenStack->isNextTokenNonTerminal()) {
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
    if (pkbInterface) { // TODO: Write Integration tests for Parser and PKB, unsure if this works
        pkbInterface->addVariable(var);
    }
}

void Parser::addConstToPkbIfExist(std::string cons) {
    if (pkbInterface) { // TODO: Write Integration tests for Parser and PKB, unsure if this works
        pkbInterface->addConst(std::stoi(cons));
    }
}
