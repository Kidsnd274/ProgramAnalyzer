#include "ModifiesTable.h"

void ModifiesTable::insertModifies(int stmtLineNumber, std::string varName) {
    if (this->modifiesList.find(stmtLineNumber) != this->modifiesList.end()) {
        this->modifiesList.find(stmtLineNumber)->second.push_back(varName);
    } else {
        std::pair<int, std::vector<std::string>> modifies(stmtLineNumber, {varName});
        this->modifiesList.insert(modifies);
    }
}

void ModifiesTable::insertProcModifies(std::string procedureName, std::string varName) {
    if (this->modifiesProcList.find(procedureName) != this->modifiesProcList.end()) {
        this->modifiesProcList.find(procedureName)->second.push_back(varName);
    } else {
        std::pair<std::string, std::vector<std::string>> modifies(procedureName, {varName});
        this->modifiesProcList.insert(modifies);
    }
}

bool ModifiesTable::existModifies(int stmtLineNumber, std::string varName) {
    if (stmtLineNumber == 0) {
        for (auto & stmt : this->modifiesList) {
            if (varName == std::string() || (std::find(stmt.second.begin(), stmt.second.end(), varName) != stmt.second.end())) {
                return true;
            }
        }
    }
    std::unordered_map<int, std::vector<std::string>> list = this->modifiesList;
    if (list.find(stmtLineNumber) != list.end() &&
        (varName == std::string() ||
         std::find(list[stmtLineNumber].begin(), list[stmtLineNumber].end(), varName) != list[stmtLineNumber].end())) {
        return true;
    }
    return false;
}

bool ModifiesTable::existStatement(int stmtLineNumber) {
    std::unordered_map<int, std::vector<std::string>> list = this->modifiesList;
    if (list.find(stmtLineNumber) != list.end()) {
        return true;
    }
    return false;
}

std::vector<std::string> ModifiesTable::getModifiesVar(int stmtLineNumber) {
    return this->modifiesList[stmtLineNumber];
}

std::string ModifiesTable::getFirstModifiedVar(int stmtLineNumber) {
    return this->modifiesList[stmtLineNumber].front();
}

std::vector<std::string> ModifiesTable::getAllModifiedVarByProc(std::string procedureName) {
    return this->modifiesProcList[procedureName];
}

std::unordered_map<int, std::vector<std::string>> ModifiesTable::getAllModifiesByStmt() {
    return this->modifiesList;
}

std::unordered_map<std::string, std::vector<std::string>> ModifiesTable::getAllModifiesByProc() {
    return this->modifiesProcList;
}

bool ModifiesTable::doesStatementModify(int stmt, std::string varModified) {
    std::unordered_map<int, std::vector<std::string>> list = this->modifiesList;
    if (list.find(stmt) == list.end()) {
        return false;
    } else {
        std::vector<std::string> vars = list[stmt];
        return std::find(vars.begin(), vars.end(), varModified) != vars.end();
    }
}

void ModifiesTable::clear() {
    this->modifiesList.clear();
    this->modifiesProcList.clear();
}
