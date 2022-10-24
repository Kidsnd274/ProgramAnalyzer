//
// Created by QMS on 30/8/2022.
//

#ifndef SPA_STATEMENTTABLE_H
#define SPA_STATEMENTTABLE_H

#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_set>
#include "Statement.h"

using namespace std;

class StatementTable {
private:
    std::vector<Statement> statementList;
public:
    void insertStmt(Statement stmt);
    std::vector<Statement> getStatementList();
    std::vector<std::string> getAllStmts();
    std::vector<std::string> getAllStmtsByType(StatementType::StmtType type);
    std::vector<std::string> getAllReads();
    std::vector<std::string> getAllAssigns();
    std::vector<std::string> getAllWhiles();
    std::vector<std::string> getAllIfs();
    std::vector<std::string> getAllPrints();
    std::vector<std::string> getAllCalls();
    std::vector<Statement> getAllCallStatements();
    Statement getStmtByLineNumber(int stmtNo);
    std::unordered_set<int> getAllAssignFromProcedure(int startStmt, int endStmt);
};

#endif //SPA_STATEMENTTABLE_H
