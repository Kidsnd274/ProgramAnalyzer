//
// Created by QMS on 13/9/2022.
//
#include <stdio.h>
#include <string>
#include <utility>
#include <algorithm>
#include "FollowsTable.h"

using namespace std;

void FollowsTable::insertFollows(int frontStmtLineNumber, int backStmtLineNumber) {
    std::pair<int,int> follows (frontStmtLineNumber, backStmtLineNumber);
    this->followsList.insert(follows);
}

bool FollowsTable::existFollows(int frontStmtLineNumber, int backStmtLineNumber) {
    unordered_map<int, int> list = this->followsList;
    if (list.find(frontStmtLineNumber) != list.end() && list[frontStmtLineNumber] == backStmtLineNumber) {
        return true;
    }
    return false;
}

std::unordered_map<int, int> FollowsTable::getAllFollows() {
    return this->followsList;
}

void FollowsTable::clear() {
    this->followsList.clear();
}
