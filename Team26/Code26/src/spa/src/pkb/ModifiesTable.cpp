//
// Created by QMS on 13/9/2022.
//
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include "ModifiesTable.h"

using namespace std;

void ModifiesTable::insertModifies(int stmtLineNumber, string varName) {
    std::pair<int,string> modifies (stmtLineNumber, varName);
    this->modifiesList.insert(modifies);
}

bool ModifiesTable::existModifies(int stmtLineNumber, string varName) {
    unordered_map<int,string> list = this->modifiesList;
    if (list.find(stmtLineNumber) != list.end() && list[stmtLineNumber] == varName) {
        return true;
    }
    return false;
}
