#include "Parser.h"
#include "pkb/PKB.h"

void Parser::parseSimple() {
    int numOfProcedures = 0;
    while(tokenStack->hasNextToken()) {
        if (tokenStack->getNext().getTokenType() == SPTokenType::ProcedureToken) {
            parseProcedure();
            numOfProcedures++;
        } else {
            throw SyntaxErrorException();
        }
    }

    if(!numOfProcedures){
        throw SyntaxErrorException();
    }
}

std::shared_ptr<ProcedureNode> Parser::parseProcedure() {
    int currStatement = statementCount;
    std::string name = parseName();
    parseLCurly();
    std::vector<std::shared_ptr<StatementNode>> stmtList = parseStatementList();
    parseRCurly();
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

    std::vector<std::shared_ptr<StatementNode>> stmtList;

    while(tokenStack->hasNextToken() && tokenStack->peekNext().getTokenType() != SPTokenType::RCurlyToken) {
        std::shared_ptr<StatementNode> stmt = parseStatement();
        stmtList.push_back(stmt);
    }

    if(oldStatementCount == statementCount){
        throw SyntaxErrorException();
    }

    return stmtList;
}

std::shared_ptr<StatementNode> Parser::parseStatement() {
    if(!tokenStack->peekNext().isNonTerminal()) {
        throw SyntaxErrorException();
    }

    SPTokenType t = tokenStack->peekNext().getTokenType();
    //TODO check if the next variable is assign before parsing as the test cases might include variables that have keywords as the names
    std::shared_ptr<StatementNode> stmt(nullptr);

    switch(t) {
        case SPTokenType::NameToken:
            stmt = std::move(parseAssign());
            break;
        case SPTokenType::IfToken:
            stmt = std::move(parseIf());
            break;
        case SPTokenType::WhileToken:
            stmt = std::move(parseWhile());
            break;
        case SPTokenType::ReadToken:
            stmt = std::move(parseRead());
            break;
        case SPTokenType::PrintToken:
            stmt = std::move(parsePrint());
            break;
        case SPTokenType::CallToken:
            stmt = std::move(parseCall());
            break;
        default:
            throw SyntaxErrorException();
            break;
    }

    return stmt;
}

std::shared_ptr<AssignNode> Parser::parseAssign() {
    int currStatement = statementCount++;
    string varAssigned = tokenStack->getNext().getTokenString();
    pkbInterface->addVariable(varAssigned);
    parseAssignToken();
    std::shared_ptr<TNode> expr = std::move(parseExpression());
    parseSemiColon();
    pkbInterface->addAssignStatement(currStatement);
    std::shared_ptr<AssignNode> n = AssignNode::createAssignNode(currStatement, varAssigned, expr);
    pkbInterface->addNode(n);

    return n;
}

std::shared_ptr<IfNode> Parser::parseIf() {
    tokenStack->getNext(); //consume If SPToken.
    int currStatement = statementCount++;

    parseLParen();
    std::shared_ptr<TNode> cond = std::move(parseCond());
    parseRParen();
    parseThen();
    parseLCurly();
    std::vector<std::shared_ptr<StatementNode>> ifStatementList = parseStatementList();
    parseRCurly();
    parseElse();
    parseLCurly();
    std::vector<std::shared_ptr<StatementNode>> elseStatementList = parseStatementList();
    parseRCurly();

    pkbInterface->addIfStatement(currStatement);

    return IfNode::createIfNode(currStatement, cond, ifStatementList, elseStatementList);
}

std::shared_ptr<TNode> Parser::parseCond() {
    if(tokenStack->peekNext().getTokenType() == SPTokenType::CondToken
    && tokenStack->peekNext().getTokenString() == "!") {
        parseCondToken();
        parseLParen();
        std::shared_ptr<TNode> cond = std::move(parseCond());
        parseRParen();
        return TNode::createNOTConditionalExpression(statementCount, "!", cond);
    } else if (tokenStack->peekNext().getTokenType() == SPTokenType::LParenToken) {
        parseLParen();
        std::shared_ptr<TNode> cond = std::move(parseCond());
        parseRParen();
        string condToken = tokenStack->peekNext().getTokenString();
        parseCondToken();
        parseLParen();
        std::shared_ptr<TNode> cond2 = std::move(parseCond());
        parseRParen();
        return TNode::createConditionalExpression(statementCount, condToken, cond, cond2);
    } else {
        return parseRel();
    }
}

std::shared_ptr<TNode> Parser::parseRel() {
    std::shared_ptr<TNode> relFactor = std::move(parseRelFactor());
    string relToken = tokenStack->peekNext().getTokenString();
    parseRelationToken();
    std::shared_ptr<TNode> relFactor2 = std::move(parseRelFactor());

    return TNode::createRelationalExpression(statementCount, relToken, relFactor, relFactor2);
}

std::shared_ptr<TNode> Parser::parseRelFactor() {
    //TODO check if the variable is a non-terminal as the test case may include keyword as variable names
    if(tokenStack->peekNext().getTokenType() == SPTokenType::NameToken) {
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

std::shared_ptr<WhileNode> Parser::parseWhile() {
    tokenStack->getNext(); //consume While SPToken
    int currStatement = statementCount++;
    parseLParen();
    std::shared_ptr<TNode> cond = std::move(parseCond());
    parseRParen();
    parseLCurly();
    std::vector<std::shared_ptr<StatementNode>> statementList = parseStatementList();
    parseRCurly();

    pkbInterface->addWhileStatement(currStatement);

    return WhileNode::createWhileNode(currStatement, cond, statementList);
}

std::shared_ptr<ReadNode> Parser::parseRead() {
    tokenStack->getNext(); //consume Read SPToken
    int currStatement = statementCount++;
    string varName = parseName();
    pkbInterface->addVariable(varName);
    parseSemiColon();

    pkbInterface->addReadStatement(currStatement);

    return ReadNode::createReadNode(currStatement, varName);
}

std::shared_ptr<PrintNode> Parser::parsePrint() {
    tokenStack->getNext(); //consume Print SPToken
    int currStatement = statementCount++;
    string varName = parseName();
    pkbInterface->addVariable(varName);
    parseSemiColon();

    pkbInterface->addPrintStatement(currStatement);

    return PrintNode::createPrintNode(currStatement, varName);
}

//TODO not for milestone 1
std::shared_ptr<CallNode> Parser::parseCall() {
    tokenStack->getNext(); //consume Call SPToken
    int currStatement = statementCount++;
    string varName = parseName();
    parseSemiColon();

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
    //TODO check for bad syntax: name, name
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
    //TODO check if the variable is a non-terminal as the test case may include keyword as variable names
    if(tokenStack->peekNext().getTokenType() == SPTokenType::NameToken) {
        std::string name = parseName();
        pkbInterface->addVariable(name);
        return TNode::createVariableName(statementCount, name);
    } else if (tokenStack->peekNext().getTokenType() == SPTokenType::ConstToken) {
        std::string constant = parseConst();
        pkbInterface->addConst(std::stoi(constant));
        return TNode::createConstantValue(statementCount, constant);
    } else {
        parseLParen();
        std::shared_ptr<TNode> expr = std::move(parseExpression());
        parseRParen();
        return expr;
    }
}