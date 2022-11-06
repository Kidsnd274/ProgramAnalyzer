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

Statement* StatementTable::getStmtByLineNumber(int stmtNo) {
    Statement* result;
    for (auto stmt: this->statementList) {
        if (stmt->lineNumber == stmtNo) {
            result = stmt;
            break;
        }
    }
    return result;
}

std::unordered_set<int> StatementTable::getAllAssignFromProcedure(int startStmt, int endStmt) {
    std::unordered_set<int> result;
    for (auto stmt: this->statementList) {
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
