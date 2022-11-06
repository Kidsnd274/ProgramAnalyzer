#ifndef SPA_STATEMENTTABLE_H
#define SPA_STATEMENTTABLE_H

#include <string>
#include <unordered_set>
#include <unordered_set>
#include "Statement.h"

class StatementTable {
private:
    std::unordered_set<Statement*> statementList;
public:
    void insertStmt(Statement stmt);
    std::unordered_set<Statement*> getStatementList();
    std::unordered_set<std::string> getAllStmts();
    std::unordered_set<std::string> getAllStmtsByType(StatementType::StmtType type);
    Statement* getStmtByLineNumber(int stmtNo);
    std::unordered_set<int> getAllAssignFromProcedure(int startStmt, int endStmt);
    void clear();
};

#endif  // SPA_STATEMENTTABLE_H
