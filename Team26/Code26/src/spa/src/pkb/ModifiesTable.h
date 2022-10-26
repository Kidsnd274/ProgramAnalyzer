//
// Created by QMS on 13/9/2022.
//

#ifndef SPA_MODIFIESTABLE_H
#define SPA_MODIFIESTABLE_H

#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>

class ModifiesTable {
private:
    std::unordered_map<int, std::vector<std::string>> modifiesList;
    std::unordered_map<std::string, std::vector<std::string>> modifiesProcList;
public:
    void insertModifies(int stmtLineNumber, std::string varName);
    void insertProcModifies(std::string procedureName, std::string varName);
    bool existModifies(int stmtLineNumber, std::string varName);
    bool existStatement(int stmtLineNumber);
    std::vector<std::string> getModifiesVar(int stmtLineNumber);
    std::string getFirstModifiedVar(int stmtLineNumber);
    std::vector<std::string> getAllModifiedVarByProc(std::string procedureName);
    std::unordered_map<int, std::vector<std::string>> getAllModifiesByStmt();
    std::unordered_map<std::string, std::vector<std::string>> getAllModifiesByProc();
    bool doesStatementModify(int stmt, std::string varModified);
    void clear();
};

#endif //SPA_MODIFIESTABLE_H
