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

vector<Statement> StatementTable::getStatementList() {
    return this->statementList;
}

vector<string> StatementTable::getAllStmts() {      // S1 (Major): DRY - Code structure is similar to other getAll methodse e.g. getAllReads
    vector<string> result;
    for (Statement stmt: this->statementList) {
        result.push_back(std::to_string(stmt.lineNumber));
    }
    return result;
}

vector<string> StatementTable::getAllReads() {      // S1 (Major): DRY - Code structure is similar to other getAll methodse e.g. getAllAssigns
    vector<string> result;
    for (Statement stmt: this->statementList) {
        if (stmt.type == StatementType::READ) {
            result.push_back(std::to_string(stmt.lineNumber));
        }
    }
    return result;
}

vector<string> StatementTable::getAllAssigns() {    // S1 (Major): DRY - Code structure is similar to other getAll methodse e.g. getAllReads
    vector<string> result;
    for (Statement stmt: this->statementList) {
        if (stmt.type == StatementType::ASSIGN) {
            result.push_back(std::to_string(stmt.lineNumber));
        }
    }
    return result;
}

vector<string> StatementTable::getAllWhiles() {     // S1 (Major): DRY - Code structure is similar to other getAll methodse e.g. getAllReads
    vector<string> result;
    for (Statement stmt: this->statementList) {
        if (stmt.type == StatementType::WHILE) {
            result.push_back(std::to_string(stmt.lineNumber));
        }
    }
    return result;
}

vector<string> StatementTable::getAllIfs() {        // S1 (Major): DRY - Code structure is similar to other getAll methodse e.g. getAllReads
    vector<string> result;
    for (Statement stmt: this->statementList) {
        if (stmt.type == StatementType::IF) {
            result.push_back(std::to_string(stmt.lineNumber));
        }
    }
    return result;
}

vector<string> StatementTable::getAllPrints() {     // S1 (Major): DRY - Code structure is similar to other getAll methodse e.g. getAllReads
    vector<string> result;
    for (Statement stmt: this->statementList) {
        if (stmt.type == StatementType::PRINT) {
            result.push_back(std::to_string(stmt.lineNumber));
        }
    }
    return result;
}

vector<string> StatementTable::getAllCalls() {      // S1 (Major): DRY - Code structure is similar to other getAll methodse e.g. getAllReads
    vector<string> result;
    for (Statement stmt: this->statementList) {
        if (stmt.type == StatementType::CALL) {
            result.push_back(std::to_string(stmt.lineNumber));
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
