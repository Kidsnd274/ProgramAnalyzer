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
    std::pair<int,string> uses (stmtLineNumber, varName);
    this->usesList.insert(uses);
}

bool UsesTable::existUses(int stmtLineNumber, string varName) {
    unordered_map<int,string> list = this->usesList;
    if (list.find(stmtLineNumber) != list.end() && list[stmtLineNumber] == varName) {
        return true;
    }
    return false;
}
