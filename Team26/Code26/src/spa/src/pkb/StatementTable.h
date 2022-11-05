//
// Created by QMS on 30/8/2022.
//

#ifndef SPA_STATEMENTTABLE_H
#define SPA_STATEMENTTABLE_H

#include <stdio.h>
#include <string>
#include <unordered_set>
#include <unordered_set>
#include "Statement.h"

using namespace std;

class StatementTable {
private:
    std::unordered_set<Statement> statementList;
public:
    void insertStmt(Statement stmt);
    std::unordered_set<Statement> getStatementList();
    std::unordered_set<std::string> getAllStmts();
    std::unordered_set<std::string> getAllStmtsByType(StatementType::StmtType type);
    std::unordered_set<std::string> getAllReads();
    std::unordered_set<std::string> getAllAssigns();
    std::unordered_set<std::string> getAllWhiles();
    std::unordered_set<std::string> getAllIfs();
    std::unordered_set<std::string> getAllPrints();
    std::unordered_set<std::string> getAllCalls();
    std::unordered_set<Statement> getAllCallStatements();
    Statement getStmtByLineNumber(int stmtNo);
    std::unordered_set<int> getAllAssignFromProcedure(int startStmt, int endStmt);
    void clear();
};

#endif //SPA_STATEMENTTABLE_H
