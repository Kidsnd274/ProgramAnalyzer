#include "Parser.h"

#include "../PKB.h"
#include "util/ast/TNode.h"

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

shared_ptr<ProcedureNode> Parser::parseProcedure() {
    string name = parseName();
    parseLCurly();
    vector<shared_ptr<IStatementNode>> stmtList = parseStatementList();
    parseRCurly();
    return make_shared<ProcedureNode>(-1, name, stmtList);
}

string Parser::parseName() {
    if(!tokenStack->peekNext().isNonTerminal()) {
        throw SyntaxErrorException();
    }

    string name = tokenStack->getNext().getTokenString();
    return name;
}

void Parser::parseConst() {
    if(tokenStack->getNext().getTokenType() != TokenType::ConstToken) {
        throw SyntaxErrorException();
    }
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

std::vector<shared_ptr<IStatementNode>> Parser::parseStatementList() {
    int oldStatementCount = statementCount;
    std::vector<shared_ptr<IStatementNode>> stmtList;

    while(tokenStack->hasNextToken() && tokenStack->peekNext().getTokenType() != TokenType::RCurlyToken) {
        shared_ptr<IStatementNode> stmt = parseStatement();
        stmtList.push_back(stmt);
    }

    if(oldStatementCount == statementCount){
        throw SyntaxErrorException();
    }
    return stmtList;
}

shared_ptr<IStatementNode> Parser::parseStatement() {
    if(!tokenStack->peekNext().isNonTerminal()) {
        throw SyntaxErrorException();
    }

    TokenType t = tokenStack->peekNext().getTokenType();
    shared_ptr<IStatementNode> res(nullptr);
    switch(t) {
        case TokenType::NameToken:
            res = std::move(parseAssign());
            break;
        case TokenType::IfToken:
            res = std::move(parseIf());
            break;
        case TokenType::WhileToken:
            res = std::move(parseWhile());
            break;
        case TokenType::ReadToken:
            res = std::move(parseRead());
            break;
        case TokenType::PrintToken:
            res = std::move(parsePrint());
            break;
        case TokenType::CallToken:
            res = std::move(parseCall());
            break;
        default:
            //throw SyntaxErrorException
            break;
    }
    statementCount++;
}

shared_ptr<AssignNode> Parser::parseAssign() {
    string varAssigned = tokenStack->getNext().getTokenString();
    parseAssignToken();
    shared_ptr<ITermNode> exp = parseExpression();
    parseSemiColon();
    shared_ptr<VariableNode> var = make_shared<VariableNode>(statementCount, varAssigned);
    return make_shared<AssignNode>(statementCount, var, exp);
}

void Parser::parseIf() {
    tokenStack->getNext(); //consume If Token.
    parseLParen();
    parseCond();
    parseRParen();
    parseThen();
    parseLCurly();
    parseStatementList();
    parseRCurly();
    parseElse();
    parseLCurly();
    parseStatementList();
    parseRCurly();
}

void Parser::parseCond() {
    if(tokenStack->peekNext().getTokenType() == TokenType::CondToken) {
        parseCondToken();
        parseLParen();
        parseCond();
        parseRParen();
    } else if (tokenStack->peekNext().getTokenType() == TokenType::LParenToken) {
        parseLParen();
        parseCond();
        parseRParen();
        parseCondToken();
        parseLParen();
        parseCond();
        parseRParen();
    } else {
        parseRel();
    }
}

void Parser::parseRel() {
    parseRelFactor();
    parseRelationToken();
    parseRelFactor();
}

void Parser::parseRelFactor() {
    if(tokenStack->peekNext().getTokenType() == TokenType::NameToken) {
        parseName();
    } else if (tokenStack->peekNext().getTokenType() == TokenType::ConstToken) {
        parseConst();
    } else {
        parseExpression();
    }
}

void Parser::parseWhile() {
    tokenStack->getNext(); //consume While Token
    parseLParen();
    parseCond();
    parseRParen();
    parseLCurly();
    parseStatementList();
    parseRCurly();
}

void Parser::parseRead() {
    tokenStack->getNext(); //consume Read Token
    string varName = parseName();
}

void Parser::parsePrint() {
    tokenStack->getNext(); //consume Print Token
    string varName = parseName();
}

void Parser::parseCall() {
    tokenStack->getNext(); //consume Call Token
    string varName = parseName();
}

void Parser::parseExpression() {
    parseTerm();
    while(tokenStack->peekNext().getTokenType() == TokenType::OpToken) {
        parseOp();
        parseFactor();
    }
}

void Parser::parseTerm() {
    parseFactor();
    while(tokenStack->peekNext().getTokenType() == TokenType::FactorToken) {
        parseFactorToken();
        parseFactor();
    }
}

void Parser::parseFactor() {
    if(tokenStack->peekNext().getTokenType() == TokenType::NameToken) {
        parseName();
    } else if (tokenStack->peekNext().getTokenType() == TokenType::ConstToken) {
        parseConst();
    } else {
        parseLParen();
        parseExpression();
        parseRParen();
    }
}