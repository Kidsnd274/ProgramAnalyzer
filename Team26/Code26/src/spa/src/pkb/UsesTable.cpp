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

bool UsesTable::existUses(int stmtLineNumber, string varName) {     // S8 (Major): POLA Violation - I believe that PKB should not even do any forms of relation checking. I suggest shifting this entire operation to QPS component
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
