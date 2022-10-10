//
// Created by QMS on 13/9/2022.
//
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include "UsesTable.h"

using namespace std;

void UsesTable::insertUses(int stmtLineNumber, string varName) {
    std::pair<int,vector<string>> uses (stmtLineNumber, {varName});
    if (this->usesList.find(stmtLineNumber) != this->usesList.end()) {
        this->usesList.find(stmtLineNumber)->second.push_back(varName);
    } else {
        this->usesList.insert(uses);
    }
}

void UsesTable::insertProcUses(std::string procedureName, std::string varName) {
    std::pair<std::string,vector<string>> uses (procedureName, {varName});
    if (this->usesProcList.find(procedureName) != this->usesProcList.end()) {
        this->usesProcList.find(procedureName)->second.push_back(varName);
    } else {
        this->usesProcList.insert(uses);
    }
}

bool UsesTable::existUses(int stmtLineNumber, string varName) {
    if (stmtLineNumber == 0) {
        for (auto & stmt: this->usesList) {
            if (varName == std::string() || std::find(stmt.second.begin(), stmt.second.end(), varName) != stmt.second.end()) {
                return true;
            }
        }
    }
    unordered_map<int,vector<string>> list = this->usesList;
    if (list.find(stmtLineNumber) != list.end() &&
    (varName == std::string() ||
    std::find(list[stmtLineNumber].begin(), list[stmtLineNumber].end(), varName) != list[stmtLineNumber].end())) {
        return true;
    }
    return false;
}

vector<string> UsesTable::getAllVarUsedByProc(string procedureName) {
    return this->usesProcList[procedureName];
}
