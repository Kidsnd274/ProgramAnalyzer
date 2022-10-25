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

// S8 (Major): POLA Violation - PKB should not know what wildcard is
bool ParentStarTable::existParentStar(int frontStmtLineNumber, int backStmtLineNumber) {
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

unordered_set<int> ParentStarTable::getAllParentStar(int childStmtLineNumber) {
    unordered_set<int> result;
    for (std::pair<int, std::vector<int>> pair: this->parentStarList) {
        if (std::find(pair.second.begin(), pair.second.end(), childStmtLineNumber) != pair.second.end()) {
            result.insert(pair.first);
        }
    }
    return result;
}

unordered_map<int, vector<int>> ParentStarTable::getAllParentStars() {
    return this->parentStarList;
}