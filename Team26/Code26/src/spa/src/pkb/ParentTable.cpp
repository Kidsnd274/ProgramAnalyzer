//
// Created by QMS on 13/9/2022.
//
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include "ParentTable.h"

using namespace std;

void ParentTable::insertParent(int parentStmtLineNumber, int childStmtLineNumber) {
    std::pair<int,int> parent (parentStmtLineNumber, childStmtLineNumber);
    this->parentList.insert(parent);
}

bool ParentTable::existParent(int parentStmtLineNumber, int childStmtLineNumber) {
    unordered_map<int,int> list = this->parentList;
    if (list.find(parentStmtLineNumber) != list.end() && list[parentStmtLineNumber] == childStmtLineNumber) {
        return true;
    }
    return false;
}
