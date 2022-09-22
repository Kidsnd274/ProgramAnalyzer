//
// Created by QMS on 13/9/2022.
//
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include "FollowsTable.h"

using namespace std;

void FollowsTable::insertFollows(int frontStmtLineNumber, int backStmtLineNumber) {
    std::pair<int,int> follows (frontStmtLineNumber, backStmtLineNumber);
    this->followsList.insert(follows);
}

bool FollowsTable::existFollows(int frontStmtLineNumber, int backStmtLineNumber) {      // S8 (Major): POLA Violation - I believe that PKB should not even do any forms of relation checking. I suggest shifting this entire operation to QPS component
    unordered_map<int, int> list = this->followsList;
    if (list.find(frontStmtLineNumber) != list.end() && list[frontStmtLineNumber] == backStmtLineNumber) {
        return true;
    }
    return false;
}
