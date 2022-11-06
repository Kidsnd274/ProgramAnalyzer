#ifndef SPA_USESTABLE_H
#define SPA_USESTABLE_H

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

class UsesTable {
private:
    std::unordered_map<int, std::vector<std::string>> usesList;
    std::unordered_map<std::string, std::vector<std::string>> usesProcList;

public:
    void insertUses(int stmtLineNumber, std::string varName);
    void insertProcUses(std::string procedureName, std::string varName);
    bool existUses(int stmtLineNumber, std::string varName);
    std::vector<std::string> getAllVarUsedByProc(std::string procedureName);
    std::unordered_map<int, std::vector<std::string>> getAllUsesByStmt();
    std::unordered_map<std::string, std::vector<std::string>> getAllUsesByProc();
    bool doesStatementUse(int stmt, std::string varUsed);
    void clear();
};

#endif  // SPA_USESTABLE_H
