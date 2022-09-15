//
// Created by QMS on 13/9/2022.
//
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include "ParentStarTable.h"

using namespace std;

void ParentStarTable::insertParentStar(int frontStmtLineNumber, int backStmtLineNumber) {
    std::pair<int,int> parentStar (frontStmtLineNumber, backStmtLineNumber);
    this->parentStarList.insert(parentStar);
}

bool ParentStarTable::existParentStar(int frontStmtLineNumber, int backStmtLineNumber) {
    unordered_map<int,int> list = this->parentStarList;
    if (list.find(frontStmtLineNumber) != list.end() && list[frontStmtLineNumber] == backStmtLineNumber) {
        return true;
    }
    return false;
}
