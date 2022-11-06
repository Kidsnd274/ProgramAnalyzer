#include "ModifiesTable.h"

void ModifiesTable::insertModifies(int stmtLineNumber, std::string varName) {
    if (this->modifiesList.find(stmtLineNumber) != this->modifiesList.end()) {
        this->modifiesList.find(stmtLineNumber)->second.insert(varName);
    } else {
        std::pair<int,std::unordered_set<std::string>> modifies (stmtLineNumber, {varName});
        this->modifiesList.insert(modifies);
    }
}

void ModifiesTable::insertProcModifies(std::string procedureName, std::string varName) {
    if (this->modifiesProcList.find(procedureName) != this->modifiesProcList.end()) {
        this->modifiesProcList.find(procedureName)->second.insert(varName);
    } else {
        std::pair<std::string,std::unordered_set<std::string>> modifies (procedureName, {varName});
        this->modifiesProcList.insert(modifies);
    }
}

bool ModifiesTable::existModifies(int stmtLineNumber, std::string varName) {
    if (stmtLineNumber == 0) {
        for (auto & stmt: this->modifiesList) {
            if (varName == std::string() || stmt.second.find(varName) != stmt.second.end()) {
                return true;
            }
        }
    }
    std::unordered_map<int,std::unordered_set<std::string>> list = this->modifiesList;
    if (list.find(stmtLineNumber) != list.end() &&
        (varName == std::string() ||
        list[stmtLineNumber].find(varName) != list[stmtLineNumber].end())) {
        return true;
    }
    return false;
}

bool ModifiesTable::existStatement(int stmtLineNumber) {
    std::unordered_map<int,std::unordered_set<std::string>> list = this->modifiesList;
    if (list.find(stmtLineNumber) != list.end()) {
        return true;
    }
    return false;
}

std::unordered_set<std::string> ModifiesTable::getModifiesVar(int stmtLineNumber) {
    return this->modifiesList[stmtLineNumber];
}

std::string ModifiesTable::getFirstModifiedVar(int stmtLineNumber) {
    return *begin(this->modifiesList[stmtLineNumber]);
}

std::unordered_set<std::string> ModifiesTable::getAllModifiedVarByProc(std::string procedureName) {
    return this->modifiesProcList[procedureName];
}

std::unordered_map<int, std::unordered_set<std::string>> ModifiesTable::getAllModifiesByStmt() {
    return this->modifiesList;
}

std::unordered_map<std::string, std::unordered_set<std::string>> ModifiesTable::getAllModifiesByProc() {
    return this->modifiesProcList;
}

bool ModifiesTable::doesStatementModify(int stmt, std::string varModified) {
    std::unordered_map<int,std::unordered_set<std::string>> list = this->modifiesList;
    if (list.find(stmt) == list.end()) {
        return false;
    } else {
        std::unordered_set<std::string> vars = list[stmt];
        return vars.find(varModified) != vars.end();
    }
}

void ModifiesTable::clear() {
    this->modifiesList.clear();
    this->modifiesProcList.clear();
}
