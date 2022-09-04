#include "Parser.h"
#include "../PKB.h"

void Parser::parseSimple() {
    int numOfProcedures = 0;

    while(tokenStack->hasNextToken()) {
        if (tokenStack->getNext().getTokenType() == TokenType::ProcedureToken) {
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
    std::string name = parseName();
    parseLCurly();
    std::vector<std::shared_ptr<StatementNode>> stmtList = parseStatementList();
    parseRCurly();

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
    if(tokenStack->peekNext().getTokenType() != TokenType::ConstToken) {
        throw SyntaxErrorException();
    }

    std::string cons = tokenStack->getNext().getTokenString();
    return cons;
}

void Parser::parseLCurly() {
    if(tokenStack->getNext().getTokenType() != TokenType::LCurlyToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseRCurly() {
    if(tokenStack->getNext().getTokenType() != TokenType::RCurlyToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseLParen() {
    if(tokenStack->getNext().getTokenType() != TokenType::LParenToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseRParen() {
    if(tokenStack->getNext().getTokenType() != TokenType::RParenToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseAssignToken() {
    if(tokenStack->getNext().getTokenType() != TokenType::AssignToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseSemiColon() {
    if(tokenStack->getNext().getTokenType() != TokenType::SemiColonToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseThen() {
    if(tokenStack->getNext().getTokenType() != TokenType::ThenToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseElse() {
    if(tokenStack->getNext().getTokenType() != TokenType::ElseToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseCondToken() {
    if(tokenStack->getNext().getTokenType() != TokenType::CondToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseRelationToken() {
    if(tokenStack->getNext().getTokenType() != TokenType::RelationToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseOp() {
    if(tokenStack->getNext().getTokenType() != TokenType::OpToken) {
        throw SyntaxErrorException();
    }
}

void Parser::parseFactorToken() {
    if(tokenStack->getNext().getTokenType() != TokenType::FactorToken) {
        throw SyntaxErrorException();
    }
}

std::vector<std::shared_ptr<StatementNode>> Parser::parseStatementList() {
    int oldStatementCount = statementCount;

    std::vector<std::shared_ptr<StatementNode>> stmtList;

    while(tokenStack->hasNextToken() && tokenStack->peekNext().getTokenType() != TokenType::RCurlyToken) {
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

    TokenType t = tokenStack->peekNext().getTokenType();
    //TODO check if the next variable is assign before parsing as the test cases might include variables that have keywords as the names
    std::shared_ptr<StatementNode> stmt(nullptr);

    switch(t) {
        case TokenType::NameToken:
            stmt = std::move(parseAssign());
            break;
        case TokenType::IfToken:
            stmt = std::move(parseIf());
            break;
        case TokenType::WhileToken:
            stmt = std::move(parseWhile());
            break;
        case TokenType::ReadToken:
            stmt = std::move(parseRead());
            break;
        case TokenType::PrintToken:
            stmt = std::move(parsePrint());
            break;
        case TokenType::CallToken:
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
    parseAssignToken();
    std::shared_ptr<TNode> expr = std::move(parseExpression());
    parseSemiColon();

    return AssignNode::createAssignNode(currStatement, varAssigned, expr);
}

std::shared_ptr<IfNode> Parser::parseIf() {
    tokenStack->getNext(); //consume If Token.
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

    return IfNode::createIfNode(currStatement, cond, ifStatementList, elseStatementList);
}

std::shared_ptr<TNode> Parser::parseCond() {
    if(tokenStack->peekNext().getTokenType() == TokenType::CondToken
    && tokenStack->peekNext().getTokenString() == "!") {
        parseCondToken();
        parseLParen();
        std::shared_ptr<TNode> cond = std::move(parseCond());
        parseRParen();
        return TNode::createNOTConditionalExpression(statementCount, "!", cond);
    } else if (tokenStack->peekNext().getTokenType() == TokenType::LParenToken) {
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
    if(tokenStack->peekNext().getTokenType() == TokenType::NameToken) {
        std::string name = parseName();
        return TNode::createVariableName(statementCount, name);
    } else if (tokenStack->peekNext().getTokenType() == TokenType::ConstToken) {
        std::string constant = parseConst();
        return TNode::createConstantValue(statementCount, constant);
    } else {
        return parseExpression();
    }
}

std::shared_ptr<WhileNode> Parser::parseWhile() {
    tokenStack->getNext(); //consume While Token
    int currStatement = statementCount++;
    parseLParen();
    std::shared_ptr<TNode> cond = std::move(parseCond());
    parseRParen();
    parseLCurly();
    std::vector<std::shared_ptr<StatementNode>> statementList = parseStatementList();
    parseRCurly();

    return WhileNode::createWhileNode(currStatement, cond, statementList);
}

std::shared_ptr<ReadNode> Parser::parseRead() {
    tokenStack->getNext(); //consume Read Token
    int currStatement = statementCount++;
    string varName = parseName();
    parseSemiColon();

    return ReadNode::createReadNode(currStatement, varName);
}

std::shared_ptr<PrintNode> Parser::parsePrint() {
    tokenStack->getNext(); //consume Print Token
    int currStatement = statementCount++;
    string varName = parseName();
    parseSemiColon();

    return PrintNode::createPrintNode(currStatement, varName);
}

std::shared_ptr<CallNode> Parser::parseCall() {
    tokenStack->getNext(); //consume Call Token
    int currStatement = statementCount++;
    string varName = parseName();
    parseSemiColon();

    return CallNode::createCallNode(currStatement, varName);
}

std::shared_ptr<TNode> Parser::parseExpression() {
    std::shared_ptr<TNode> base = std::move(parseTerm());
    while(tokenStack->peekNext().getTokenType() == TokenType::OpToken) {
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
    while(tokenStack->peekNext().getTokenType() == TokenType::FactorToken) {
        std::string operand = tokenStack->peekNext().getTokenString();
        parseFactorToken();
        std::shared_ptr<TNode> factor2 = std::move(parseFactor());

        base = TNode::createTerm(statementCount, operand, base, factor2);
    }
    return base;
}

std::shared_ptr<TNode> Parser::parseFactor() {
    //TODO check if the variable is a non-terminal as the test case may include keyword as variable names
    if(tokenStack->peekNext().getTokenType() == TokenType::NameToken) {
        std::string name = parseName();
        return TNode::createVariableName(statementCount, name);
    } else if (tokenStack->peekNext().getTokenType() == TokenType::ConstToken) {
        std::string constant = parseConst();
        return TNode::createConstantValue(statementCount, constant);
    } else {
        parseLParen();
        std::shared_ptr<TNode> expr = std::move(parseExpression());
        parseRParen();
        return expr;
    }
}