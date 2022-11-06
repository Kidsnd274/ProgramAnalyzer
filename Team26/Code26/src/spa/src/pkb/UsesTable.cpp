#include "UsesTable.h"

void UsesTable::insertUses(int stmtLineNumber, std::string varName) {
    std::pair<int, std::unordered_set<std::string>> uses(stmtLineNumber, {varName});
    if (this->usesList.find(stmtLineNumber) != this->usesList.end()) {
        this->usesList.find(stmtLineNumber)->second.insert(varName);
    } else {
        this->usesList.insert(uses);
    }
}

void UsesTable::insertProcUses(std::string procedureName, std::string varName) {
    std::pair<std::string, std::unordered_set<std::string>> uses(procedureName, {varName});
    if (this->usesProcList.find(procedureName) != this->usesProcList.end()) {
        this->usesProcList.find(procedureName)->second.insert(varName);
    } else {
        this->usesProcList.insert(uses);
    }
}

bool UsesTable::existUses(int stmtLineNumber, std::string varName) {
    if (stmtLineNumber == 0) {
        for (auto & stmt : this->usesList) {
            if (varName == std::string() || std::find(stmt.second.begin(), stmt.second.end(), varName) != stmt.second.end()) {
                return true;
            }
        }
    }
    std::unordered_map<int, std::unordered_set<std::string>> list = this->usesList;
    if (list.find(stmtLineNumber) != list.end() &&
        (varName == std::string() ||
         list[stmtLineNumber].find(varName) != list[stmtLineNumber].end())) {
        return true;
    }
    return false;
}

std::unordered_set<std::string> UsesTable::getAllVarUsedByProc(std::string procedureName) {
    return this->usesProcList[procedureName];
}

std::unordered_map<int, std::unordered_set<std::string>> UsesTable::getAllUsesByStmt() {
    return this->usesList;
}

std::unordered_map<std::string, std::unordered_set<std::string>> UsesTable::getAllUsesByProc() {
    return this->usesProcList;
}

bool UsesTable::doesStatementUse(int stmt, std::string varUsed) {
    std::unordered_map<int, std::unordered_set<std::string>> list = this->usesList;
    if (list.find(stmt) == list.end()) {
        return false;
    } else {
        std::unordered_set<std::string> vars = list[stmt];
        return std::find(vars.begin(), vars.end(), varUsed) != vars.end();
    }
}

void UsesTable::clear() {
    this->usesList.clear();
    this->usesProcList.clear();
}
