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
    std::pair<int,vector<int>> parentStar (frontStmtLineNumber, {backStmtLineNumber});
    if (this->parentStarList.find(frontStmtLineNumber) != parentStarList.end()) {
        this->parentStarList[frontStmtLineNumber].push_back(backStmtLineNumber);
    } else {
        this->parentStarList.insert(parentStar);
    }
}

bool ParentStarTable::existParentStar(int frontStmtLineNumber, int backStmtLineNumber) {        // S8 (Major): POLA Violation - I believe that PKB should not even do any forms of relation checking. I suggest shifting this entire operation to QPS component
    unordered_map<int,vector<int>> list = this->parentStarList;
    bool isParentWildcard = frontStmtLineNumber == 0;
    bool isChildWildcard = backStmtLineNumber == 0;
    if (isParentWildcard && isChildWildcard) {
        return list.size() != 0;
    }
    if (isParentWildcard) {
        for (auto &p: list) {
            if (std::find(p.second.begin(), p.second.end(), backStmtLineNumber) != p.second.end()) {
                return true;
            }
        }
        return false;
    }
    if (isChildWildcard) {
        if (list.find(frontStmtLineNumber) != list.end()) {
            return list[frontStmtLineNumber].size() != 0;
        }
    }
    //Both not wildcard
    if (list.find(frontStmtLineNumber) != list.end()) {
        vector<int> children = list[frontStmtLineNumber];
        if (std::find(children.begin(), children.end(), backStmtLineNumber) != children.end()) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}
