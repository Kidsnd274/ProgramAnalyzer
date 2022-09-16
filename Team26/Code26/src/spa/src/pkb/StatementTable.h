//
// Created by QMS on 30/8/2022.
//

#ifndef SPA_STATEMENTTABLE_H
#define SPA_STATEMENTTABLE_H

#include <stdio.h>
#include <string>
#include <vector>
#include "Statement.h"

using namespace std;

class StatementTable {
private:
    vector<Statement> statementList;
public:
    void insertStmt(Statement stmt);
    vector<Statement> getStatementList();
    vector<string> getAllStmts();
    vector<string> getAllReads();
    vector<string> getAllAssigns();
    vector<string> getAllWhiles();
    vector<string> getAllIfs();
    vector<string> getAllPrints();
    vector<string> getAllCalls();
    Statement getStmtByLineNumber(int stmtNo);
};

#endif //SPA_STATEMENTTABLE_H
