//
// Created by QMS on 13/9/2022.
//

#ifndef SPA_USESTABLE_H
#define SPA_USESTABLE_H

#include <stdio.h>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class UsesTable {
private:
    unordered_map<int, std::unordered_set<std::string>> usesList;
    unordered_map<std::string, std::unordered_set<std::string>> usesProcList;
public:
    void insertUses(int stmtLineNumber, string varName);
    void insertProcUses(string procedureName, string varName);
    bool existUses(int stmtLineNumber, string varName);
    unordered_set<string> getAllVarUsedByProc(string procedureName);
    std::unordered_map<int, std::unordered_set<std::string>> getAllUsesByStmt();
    std::unordered_map<std::string, std::unordered_set<std::string>> getAllUsesByProc();
    bool doesStatementUse(int stmt, std::string varUsed);
    void clear();
};

#endif //SPA_USESTABLE_H
