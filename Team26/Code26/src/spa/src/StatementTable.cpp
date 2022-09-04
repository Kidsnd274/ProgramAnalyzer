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

vector<string> StatementTable::getAllStmts() {
    vector<string> result;
    for (Statement stmt: this->statementList) {
        result.push_back(std::to_string(stmt.lineNumber));
    }
    return result;
}

vector<string> StatementTable::getAllReads() {
    vector<string> result;
    for (Statement stmt: this->statementList) {
        if (stmt.type == READ) {
            result.push_back(std::to_string(stmt.lineNumber));
        }
    }
    return result;
}

vector<string> StatementTable::getAllAssigns() {
    vector<string> result;
    for (Statement stmt: this->statementList) {
        if (stmt.type == ASSIGN) {
            result.push_back(std::to_string(stmt.lineNumber));
        }
    }
    return result;
}

vector<string> StatementTable::getAllWhiles() {
    vector<string> result;
    for (Statement stmt: this->statementList) {
        if (stmt.type == WHILE) {
            result.push_back(std::to_string(stmt.lineNumber));
        }
    }
    return result;
}

vector<string> StatementTable::getAllIfs() {
    vector<string> result;
    for (Statement stmt: this->statementList) {
        if (stmt.type == IF) {
            result.push_back(std::to_string(stmt.lineNumber));
        }
    }
    return result;
}

vector<string> StatementTable::getAllPrints() {
    vector<string> result;
    for (Statement stmt: this->statementList) {
        if (stmt.type == PRINT) {
            result.push_back(std::to_string(stmt.lineNumber));
        }
    }
    return result;
}

vector<string> StatementTable::getAllCalls() {
    vector<string> result;
    for (Statement stmt: this->statementList) {
        if (stmt.type == CALL) {
            result.push_back(std::to_string(stmt.lineNumber));
        }
    }
    return result;
}
