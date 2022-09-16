//
// Created by QMS on 13/9/2022.
//
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include "FollowsStarTable.h"

using namespace std;

void FollowsStarTable::insertFollowsStar(int frontStmtLineNumber, int backStmtLineNumber) {
    std::pair<int,int> followsStar (frontStmtLineNumber, backStmtLineNumber);
    this->followsStarList.insert(followsStar);
}

bool FollowsStarTable::existFollowsStar(int frontStmtLineNumber, int backStmtLineNumber) {
    unordered_map<int,int> list = this->followsStarList;
    if (list.find(frontStmtLineNumber) != list.end() && list[frontStmtLineNumber] == backStmtLineNumber) {
        return true;
    }
    return false;
}
