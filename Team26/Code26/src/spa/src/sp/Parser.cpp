#include "Parser.h"

#include <utility>
#include "pkb/PKB.h"

void Parser::parseSimple() {
    int numOfProcedures = 0;
    std::vector<std::shared_ptr<ProcedureNode>> procedures;
    while(tokenStack->hasNextToken()) {
        if (tokenStack->getNext().getTokenType() == SPTokenType::ProcedureToken) {
            std::shared_ptr<ProcedureNode> pn = parseProcedure();
            procedures.push_back(pn);
            numOfProcedures++;
        } else {
            throw SyntaxErrorException();
        }
    }

    if(!numOfProcedures){
        throw SyntaxErrorException();
    }
    de->extract(procedures);
}

std::shared_ptr<ProcedureNode> Parser::parseProcedure() {
    int currStatement = statementCount;
    std::string name = parseName();
    parseLCurly();
    de->addProcedure(name);
    std::vector<std::shared_ptr<StatementNode>> stmtList = parseStatementList();
    tokenStack->checkAndUseNextToken(SPTokenType::RCurlyToken);
    pkbInterface->addProcedure(name, currStatement, statementCount);
    return make_shared<ProcedureNode>(name, stmtList);
}

std::string Parser::parseName() {
    if(!tokenStack->peekNext().isNonTerminal()) {
        throw SyntaxErrorException();
    }

    std::string name = tokenStack->getNext().getTokenString();
    return name;
}

std::string Parser::parseConst() {
    if(tokenStack->peekNext().getTokenType() != SPTokenType::ConstToken) {
        throw SyntaxErrorException();
    }

    std::string cons = tokenStack->getNext().getTokenString();
    return cons;
}

void Parser::parseLCurly() {
    if(tokenStack->getNext().getTokenType() != SPTokenType::LCurlyToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseRCurly() {
    if(tokenStack->getNext().getTokenType() != SPTokenType::RCurlyToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseLParen() {
    if(tokenStack->getNext().getTokenType() != SPTokenType::LParenToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseRParen() {
    if(tokenStack->getNext().getTokenType() != SPTokenType::RParenToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseAssignToken() {
    if(tokenStack->getNext().getTokenType() != SPTokenType::AssignToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseSemiColon() {
    if(tokenStack->getNext().getTokenType() != SPTokenType::SemiColonToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseThen() {
    if(tokenStack->getNext().getTokenType() != SPTokenType::ThenToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseElse() {
    if(tokenStack->getNext().getTokenType() != SPTokenType::ElseToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseCondToken() {
    if(tokenStack->getNext().getTokenType() != SPTokenType::CondToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseRelationToken() {
    if(tokenStack->getNext().getTokenType() != SPTokenType::RelationToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseOp() {
    if(tokenStack->getNext().getTokenType() != SPTokenType::OpToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseFactorToken() {
    if(tokenStack->getNext().getTokenType() != SPTokenType::FactorToken) {
        throw SyntaxErrorException();
    }
}

std::vector<std::shared_ptr<StatementNode>> Parser::parseStatementList() {
    int oldStatementCount = statementCount;
    int currStatementListNumber = statementListNumber++;
    std::vector<std::shared_ptr<StatementNode>> stmtList;

    while(tokenStack->hasNextToken() && tokenStack->peekNext().getTokenType() != SPTokenType::RCurlyToken) {
        std::shared_ptr<StatementNode> stmt = parseStatement(currStatementListNumber);
        stmtList.push_back(stmt);
    }

    if(oldStatementCount == statementCount){
        throw SyntaxErrorException();
    }

    return stmtList;
}

std::shared_ptr<StatementNode> Parser::parseStatement(int stmtListNum) {
    if(!tokenStack->peekNext().isNonTerminal()) {
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
    string varAssigned = tokenStack->getNext().getTokenString();
    pkbInterface->addVariable(varAssigned);
    tokenStack->checkAndUseNextToken(SPTokenType::AssignToken);
    std::shared_ptr<TNode> expr = std::move(parseExpression());
    parseSemiColon();
    pkbInterface->addAssignStatement(currStatement, stmtListNum, expr);

    return AssignNode::createAssignNode(currStatement, varAssigned, expr);
}

std::shared_ptr<IfNode> Parser::parseIf(int stmtListNum) {
    tokenStack->getNext(); //consume If SPToken.
    int currStatement = statementCount++;

    parseLParen();
    std::shared_ptr<TNode> cond = std::move(parseCond());
    tokenStack->checkAndUseNextToken(SPTokenType::RParenToken);
    tokenStack->checkAndUseNextToken(SPTokenType::ThenToken);
    parseLCurly();
    std::vector<std::shared_ptr<StatementNode>> ifStatementList = parseStatementList();
    tokenStack->checkAndUseNextToken(SPTokenType::RCurlyToken);
    tokenStack->checkAndUseNextToken(SPTokenType::ElseToken);
    parseLCurly();
    std::vector<std::shared_ptr<StatementNode>> elseStatementList = parseStatementList();
    tokenStack->checkAndUseNextToken(SPTokenType::RCurlyToken);
    pkbInterface->addIfStatement(currStatement, stmtListNum);

    return IfNode::createIfNode(currStatement, cond, ifStatementList, elseStatementList);
}

std::shared_ptr<TNode> Parser::parseCond() {
    if(tokenStack->peekNext().getTokenType() == SPTokenType::CondToken
    && tokenStack->peekNext().getTokenString() == "!") {
        tokenStack->checkAndUseNextToken(SPTokenType::CondToken);
        parseLParen();
        std::shared_ptr<TNode> cond = std::move(parseCond());
        tokenStack->checkAndUseNextToken(SPTokenType::RParenToken);
        return TNode::createNOTConditionalExpression(statementCount, "!", cond);
    } else if (tokenStack->peekNext().getTokenType() == SPTokenType::LParenToken && tokenStack->isCondTokenAfterRparen()) {
        parseLParen();
        std::shared_ptr<TNode> cond = std::move(parseCond());
        tokenStack->checkAndUseNextToken(SPTokenType::RParenToken);
        string condToken = tokenStack->peekNext().getTokenString();
        tokenStack->checkAndUseNextToken(SPTokenType::CondToken);
        parseLParen();
        std::shared_ptr<TNode> cond2 = std::move(parseCond());
        tokenStack->checkAndUseNextToken(SPTokenType::RParenToken);
        return TNode::createConditionalExpression(statementCount, condToken, cond, cond2);
    } else {
        return parseRel();
    }
}

std::shared_ptr<TNode> Parser::parseRel() {
    std::shared_ptr<TNode> relFactor = std::move(parseExpression());
    string relToken = tokenStack->peekNext().getTokenString();
    tokenStack->checkAndUseNextToken(SPTokenType::RelationToken);
    std::shared_ptr<TNode> relFactor2 = std::move(parseExpression());

    return TNode::createRelationalExpression(statementCount, relToken, relFactor, relFactor2);
}

std::shared_ptr<TNode> Parser::parseRelFactor() {
    if(tokenStack->peekNext().isNonTerminal()) {
        std::string name = parseName();
        pkbInterface->addVariable(name);
        return TNode::createVariableName(statementCount, name);
    } else if (tokenStack->peekNext().getTokenType() == SPTokenType::ConstToken) {
        std::string constant = parseConst();
        pkbInterface->addConst(std::stoi(constant));
        return TNode::createConstantValue(statementCount, constant);
    } else {
        return parseExpression();
    }
}

std::shared_ptr<WhileNode> Parser::parseWhile(int stmtListNum) {
    tokenStack->getNext(); //consume While SPToken
    int currStatement = statementCount++;
    parseLParen();
    std::shared_ptr<TNode> cond = std::move(parseCond());
    tokenStack->checkAndUseNextToken(SPTokenType::RParenToken);
    parseLCurly();
    std::vector<std::shared_ptr<StatementNode>> statementList = parseStatementList();
    tokenStack->checkAndUseNextToken(SPTokenType::RCurlyToken);

    pkbInterface->addWhileStatement(currStatement, stmtListNum);

    return WhileNode::createWhileNode(currStatement, cond, statementList);
}

std::shared_ptr<ReadNode> Parser::parseRead(int stmtListNum) {
    tokenStack->getNext(); //consume Read SPToken
    int currStatement = statementCount++;
    string varName = parseName();
    pkbInterface->addVariable(varName);
    parseSemiColon();

    pkbInterface->addReadStatement(currStatement, stmtListNum);

    return ReadNode::createReadNode(currStatement, varName);
}

std::shared_ptr<PrintNode> Parser::parsePrint(int stmtListNum) {
    tokenStack->getNext(); //consume Print SPToken
    int currStatement = statementCount++;
    string varName = parseName();
    pkbInterface->addVariable(varName);
    parseSemiColon();

    pkbInterface->addPrintStatement(currStatement, stmtListNum);

    return PrintNode::createPrintNode(currStatement, varName);
}


std::shared_ptr<CallNode> Parser::parseCall(int stmtListNum) {
    tokenStack->getNext(); //consume Call SPToken
    int currStatement = statementCount++;
    string varName = parseName();
    parseSemiColon();

    CallStruct cs(currStatement, varName);
    de->addCallStatement(cs);

    //pkbInterface->addCallStatement(currStatement, stmtListNum);
    return CallNode::createCallNode(currStatement, varName);
}

std::shared_ptr<TNode> Parser::parseExpression() {
    std::shared_ptr<TNode> base = std::move(parseTerm());
    while(tokenStack->peekNext().getTokenType() == SPTokenType::OpToken) {
        std::string operand = tokenStack->peekNext().getTokenString();
        parseOp();
        std::shared_ptr<TNode> term2 = std::move(parseTerm());
        base = TNode::createTerm(statementCount, operand, base, term2);
    }
    return base;
}

std::shared_ptr<TNode> Parser::parseTerm() {
    std::shared_ptr<TNode> base = std::move(parseFactor());
    while(tokenStack->peekNext().getTokenType() == SPTokenType::FactorToken) {
        std::string operand = tokenStack->peekNext().getTokenString();
        parseFactorToken();
        std::shared_ptr<TNode> factor2 = std::move(parseFactor());

        base = TNode::createTerm(statementCount, operand, base, factor2);
    }
    return base;
}

std::shared_ptr<TNode> Parser::parseFactor() {
    if(tokenStack->peekNext().isNonTerminal()) {
        std::string name = parseName();
        if (pkbInterface) { // TODO: Write Integration tests for Parser and PKB, unsure if this works
            pkbInterface->addVariable(name);
        }
        return TNode::createVariableName(statementCount, name);
    } else if (tokenStack->peekNext().getTokenType() == SPTokenType::ConstToken) {
        std::string constant = parseConst();
        if (pkbInterface) {
            pkbInterface->addConst(std::stoi(constant));
        }
        return TNode::createConstantValue(statementCount, constant);
    } else {
        parseLParen();
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
