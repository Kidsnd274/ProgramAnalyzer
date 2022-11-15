#include "StatementTable.h"

void StatementTable::insertStmt(Statement stmt) {
    this->statementList.push_back(stmt);
}

std::vector<Statement> StatementTable::getStatementList() {
    return this->statementList;
}


// S1 (Major): DRY - Code structure of methods are similar to other getAll methods
std::vector<std::string> StatementTable::getAllStmts() {
    std::vector<std::string> result;
    for (Statement stmt : this->statementList) {
        result.push_back(std::to_string(stmt.lineNumber));
    }
    return result;
}

std::vector<std::string> StatementTable::getAllStmtsByType(StatementType::StmtType type) {
    std::vector<std::string> result;
    for (Statement stmt : this->statementList) {
        if (stmt.type == type) {
            result.push_back(std::to_string(stmt.lineNumber));
        }
    }
    return result;
}

// S1 (Major): DRY - Code structure of methods are similar to other getAll methods
std::vector<std::string> StatementTable::getAllReads() {
    return getAllStmtsByType(StatementType::READ);
}

// S1 (Major): DRY - Code structure of methods are similar to other getAll methods
std::vector<std::string> StatementTable::getAllAssigns() {
    return getAllStmtsByType(StatementType::ASSIGN);
}

// S1 (Major): DRY - Code structure of methods are similar to other getAll methods
std::vector<std::string> StatementTable::getAllWhiles() {
    return getAllStmtsByType(StatementType::WHILE);
}

// S1 (Major): DRY - Code structure of methods are similar to other getAll methods
std::vector<std::string> StatementTable::getAllIfs() {
    return getAllStmtsByType(StatementType::IF);
}

// S1 (Major): DRY - Code structure of methods are similar to other getAll methods
std::vector<std::string> StatementTable::getAllPrints() {
    return getAllStmtsByType(StatementType::PRINT);
}

// S1 (Major): DRY - Code structure of methods are similar to other getAll methods
std::vector<std::string> StatementTable::getAllCalls() {
    return getAllStmtsByType(StatementType::CALL);
}

// S1 (Major): DRY - Code structure of methods are similar to other getAll methods
std::vector<Statement> StatementTable::getAllCallStatements() {
    std::vector<Statement> result;
    for (Statement stmt : this->statementList) {
        if (stmt.type == StatementType::CALL) {
            result.push_back(stmt);
        }
    }
    return result;
}

Statement StatementTable::getStmtByLineNumber(int stmtNo) {
    Statement result;
    for (Statement stmt : this->statementList) {
        if (stmt.lineNumber == stmtNo) {
            result = stmt;
            break;
        }
    }
    return result;
}

std::unordered_set<int> StatementTable::getAllAssignFromProcedure(int startStmt, int endStmt) {
    std::unordered_set<int> result;
    for (Statement stmt : this->statementList) {
        int lineNumber = stmt.lineNumber;
        StatementType::StmtType type = stmt.type;
        if ((lineNumber >= startStmt) && (lineNumber <= endStmt) && (type == StatementType::ASSIGN)) {
            result.insert(lineNumber);
        }
    }
    return result;
}

void StatementTable::clear() {
    this->statementList.clear();
}
