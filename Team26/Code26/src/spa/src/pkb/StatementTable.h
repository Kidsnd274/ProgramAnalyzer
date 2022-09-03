//
// Created by QMS on 30/8/2022.
//

#ifndef SPA_STATEMENTTABLE_H
#define SPA_STATEMENTTABLE_H

#include <stdio.h>
#include <string>
#include "Statement.h"

using namespace std;

class StatementTable {
private:
    vector<Statement> statementList;
public:
    void insertStmt(Statement stmt);
};

#endif //SPA_STATEMENTTABLE_H
