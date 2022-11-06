#include "StatementTable.h"

void StatementTable::insertStmt(Statement stmt) {
    this->statementList.insert(&stmt);
}

std::unordered_set<Statement*> StatementTable::getStatementList() {
    return this->statementList;
}

std::unordered_set<std::string> StatementTable::getAllStmts() {
    std::unordered_set<std::string> result;
    for (auto stmt: this->statementList) {
        result.insert(std::to_string(stmt->lineNumber));
    }
    return result;
}

std::unordered_set<std::string> StatementTable::getAllStmtsByType(StatementType::StmtType type) {
    std::unordered_set<std::string> result;
    for (auto stmt: this->statementList) {
        if (stmt->type == type) {
            result.insert(std::to_string(stmt->lineNumber));
        }
    }
    return result;
}

//std::unordered_set<std::string> StatementTable::getAllReads() {
//    return getAllStmtsByType(StatementType::READ);
//}
//
//std::unordered_set<std::string> StatementTable::getAllAssigns() {
//    return getAllStmtsByType(StatementType::ASSIGN);
//}
//
//std::unordered_set<std::string> StatementTable::getAllWhiles() {
//    return getAllStmtsByType(StatementType::WHILE);
//}
//
//std::unordered_set<std::string> StatementTable::getAllIfs() {
//    return getAllStmtsByType(StatementType::IF);
//}
//
//std::unordered_set<std::string> StatementTable::getAllPrints() {
//    return getAllStmtsByType(StatementType::PRINT);
//}
//
//std::unordered_set<std::string> StatementTable::getAllCalls() {
//    return getAllStmtsByType(StatementType::CALL);
//}

std::unordered_set<Statement*> StatementTable::getAllCallStatements() {
    std::unordered_set<Statement*> result;
    for (auto &stmt: this->statementList) {
        if (stmt->type == StatementType::CALL) {
            result.insert(stmt);
        }
    }
    return result;
}

Statement* StatementTable::getStmtByLineNumber(int stmtNo) {
    Statement* result;
    for (auto &stmt: this->statementList) {
        if (stmt->lineNumber == stmtNo) {
            result = stmt;
            break;
        }
    }
    return result;
}

std::unordered_set<int> StatementTable::getAllAssignFromProcedure(int startStmt, int endStmt) {
    std::unordered_set<int> result;
    for (auto &stmt: this->statementList) {
        int lineNumber = stmt->lineNumber;
        StatementType::StmtType type = stmt->type;
        if ((lineNumber >= startStmt) && (lineNumber <= endStmt) && (type == StatementType::ASSIGN)) {
            result.insert(lineNumber);
        }
    }
    return result;
}

void StatementTable::clear() {
    this->statementList.clear();
}
