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

void Parser::parseProcedure() {
    std::string name = parseName();
    parseLCurly();
    parseStatementList();
    parseRCurly();
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

void Parser::parseStatementList() {
    int oldStatementCount = statementCount;

    while(tokenStack->hasNextToken() && tokenStack->peekNext().getTokenType() != TokenType::RCurlyToken) {
        parseStatement();
    }

    if(oldStatementCount == statementCount){
        throw SyntaxErrorException();
    }
}

void Parser::parseStatement() {
    if(!tokenStack->peekNext().isNonTerminal()) {
        throw SyntaxErrorException();
    }

    TokenType t = tokenStack->peekNext().getTokenType();
    //TODO check if the next variable is assign before parsing as the test cases might include variables that have keywords as the names
    switch(t) {
        case TokenType::NameToken:
            parseAssign();
            break;
        case TokenType::IfToken:
            parseIf();
            break;
        case TokenType::WhileToken:
            parseWhile();
            break;
        case TokenType::ReadToken:
            parseRead();
            break;
        case TokenType::PrintToken:
            parsePrint();
            break;
        case TokenType::CallToken:
            parseCall();
            break;
        default:
            throw SyntaxErrorException();
            break;
    }
    statementCount++;
}

void Parser::parseAssign() {
    string varAssigned = tokenStack->getNext().getTokenString();
    parseAssignToken();
    parseExpression();
    parseSemiColon();
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
    if(tokenStack->peekNext().getTokenType() == TokenType::CondToken
    && tokenStack->peekNext().getTokenString() == "!") {
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
    //TODO check if the variable is a non-terminal as the test case may include keyword as variable names
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
    parseSemiColon();
}

void Parser::parsePrint() {
    tokenStack->getNext(); //consume Print Token
    string varName = parseName();
    parseSemiColon();
}

void Parser::parseCall() {
    tokenStack->getNext(); //consume Call Token
    string varName = parseName();
    parseSemiColon();
}

void Parser::parseExpression() {
    parseTerm();
    while(tokenStack->peekNext().getTokenType() == TokenType::OpToken) {
        parseOp();
        parseTerm();
    }
    //TODO check for bad syntax
}

void Parser::parseTerm() {
    parseFactor();
    while(tokenStack->peekNext().getTokenType() == TokenType::FactorToken) {
        parseFactorToken();
        parseFactor();
    }
}

void Parser::parseFactor() {
    //TODO check if the variable is a non-terminal as the test case may include keyword as variable names
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