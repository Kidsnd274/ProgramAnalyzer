//
// Created by QMS on 13/9/2022.
//
#include <stdio.h>
#include <string>
#include <utility>
#include <unordered_set>
#include <algorithm>
#include "ParentStarTable.h"

using namespace std;

void ParentStarTable::insertParentStar(int frontStmtLineNumber, int backStmtLineNumber) {
    std::pair<int,unordered_set<int>> parentStar (frontStmtLineNumber, {backStmtLineNumber});
    if (this->parentStarList.find(frontStmtLineNumber) != parentStarList.end()) {
        this->parentStarList[frontStmtLineNumber].insert(backStmtLineNumber);
    } else {
        this->parentStarList.insert(parentStar);
    }
}

bool ParentStarTable::existParentStar(int frontStmtLineNumber, int backStmtLineNumber) {
    unordered_map<int,unordered_set<int>> list = this->parentStarList;
    bool isParentWildcard = frontStmtLineNumber == 0;
    bool isChildWildcard = backStmtLineNumber == 0;
    if (isParentWildcard && isChildWildcard) {
        return list.size() != 0;
    }
    if (isParentWildcard) {
        for (auto &p: list) {
            if (p.second.find(backStmtLineNumber) != p.second.end()) {
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
        unordered_set<int> children = list[frontStmtLineNumber];
        if (children.find(backStmtLineNumber) != children.end()) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

unordered_set<int> ParentStarTable::getAllParentStar(int childStmtLineNumber) {
    unordered_set<int> result;
    for (std::pair<int, std::unordered_set<int>> pair: this->parentStarList) {
        if (pair.second.find(childStmtLineNumber) != pair.second.end()) {
            result.insert(pair.first);
        }
    }
    return result;
}

unordered_map<int, unordered_set<int>> ParentStarTable::getAllParentStars() {
    return this->parentStarList;
}

void ParentStarTable::clear() {
    this->parentStarList.clear();
}
