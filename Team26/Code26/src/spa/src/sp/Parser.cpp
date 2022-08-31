#include "Parser.h"

#include "../PKB.h"
#include "../TNode.h"

void Parser::parseSimple() {
    int numOfProcedures = 0;

    while(tokenStack->hasNextToken()) {
        if (tokenStack->getNext().getTokenType() == TokenType::ProcedureToken) {
            parseProcedure();
            numOfProcedures++;
        } else {
            //throw SyntaxErrorException
        }
    }

    if(!numOfProcedures){
        //throw SyntaxErrorException
    }
}

void Parser::parseProcedure() {
    parseName();
    parseLCurly();
    parseStatementList();
    parseRCurly();
}

string Parser::parseName() {
    if(!tokenStack->peekNext().isNonTerminal()) {
        //throw SyntaxErrorException
    }

    string name = tokenStack->getNext().getTokenString();
    return name;
}

void Parser::parseLCurly() {
    if(tokenStack->getNext().getTokenType() != TokenType::LCurlyToken) {
        //throw SyntaxErrorException
    }
}

void Parser::parseRCurly() {
    if(tokenStack->getNext().getTokenType() != TokenType::RCurlyToken) {
        //throw SyntaxErrorException
    }
}

void Parser::parseStatementList() {
    int numOfStatements = 0;

    while(tokenStack->hasNextToken() && tokenStack->peekNext().getTokenType() != TokenType::RCurlyToken) {
        parseStatement();
        numOfStatements++;
    }

    if(!numOfStatements){
        //throw SyntaxErrorException
    }
}

void Parser::parseStatement() {
    if(!tokenStack->peekNext().isNonTerminal()) {
        //throw SyntaxErrorException
    }
    TokenType t = tokenStack->getNext().getTokenType();
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
            //throw SyntaxErrorException
            break;
    }
}