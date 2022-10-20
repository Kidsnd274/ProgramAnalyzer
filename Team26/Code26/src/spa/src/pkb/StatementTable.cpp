//
// Created by QMS on 30/8/2022.
//
#include <stdio.h>
#include <string>
#include <vector>
#include "StatementTable.h"

using namespace std;

void StatementTable::insertStmt(Statement stmt) {
    this->statementList.push_back(stmt);
}

std::vector<Statement> StatementTable::getStatementList() {
    return this->statementList;
}

std::vector<std::string> StatementTable::getAllStmts() {
    std::vector<std::string> result;
    for (Statement stmt: this->statementList) {
        result.push_back(std::to_string(stmt.lineNumber));
    }
    return result;
}

std::vector<std::string> StatementTable::getAllStmtsByType(StatementType::StmtType type) {
    std::vector<std::string> result;
    for (Statement stmt: this->statementList) {
        if (stmt.type == type) {
            result.push_back(std::to_string(stmt.lineNumber));
        }
    }
    return result;
}

std::vector<std::string> StatementTable::getAllReads() {
    return getAllStmtsByType(StatementType::READ);
}

std::vector<std::string> StatementTable::getAllAssigns() {
    return getAllStmtsByType(StatementType::ASSIGN);
}

std::vector<std::string> StatementTable::getAllWhiles() {
    return getAllStmtsByType(StatementType::WHILE);
}

std::vector<std::string> StatementTable::getAllIfs() {
    return getAllStmtsByType(StatementType::IF);
}

std::vector<std::string> StatementTable::getAllPrints() {
    return getAllStmtsByType(StatementType::PRINT);
}

std::vector<std::string> StatementTable::getAllCalls() {
    return getAllStmtsByType(StatementType::CALL);
}

std::vector<Statement> StatementTable::getAllCallStatements() {
    vector<Statement> result;
    for (Statement stmt: this->statementList) {
        if (stmt.type == StatementType::CALL) {
            result.push_back(stmt);
        }
    }
    return result;
}

Statement StatementTable::getStmtByLineNumber(int stmtNo) {
    Statement result;
    for (Statement stmt: this->statementList) {
        if (stmt.lineNumber == stmtNo) {
            result = stmt;
            break;
        }
    }
    return result;
}
