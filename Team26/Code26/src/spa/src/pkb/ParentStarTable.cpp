#include "ParentStarTable.h"

void ParentStarTable::insertParentStar(int frontStmtLineNumber, int backStmtLineNumber) {
    std::pair<int, std::unordered_set<int>> parentStar (frontStmtLineNumber, {backStmtLineNumber});
    if (this->parentStarList.find(frontStmtLineNumber) != parentStarList.end()) {
        this->parentStarList[frontStmtLineNumber].insert(backStmtLineNumber);
    } else {
        this->parentStarList.insert(parentStar);
    }
}

bool ParentStarTable::existParentStar(int frontStmtLineNumber, int backStmtLineNumber) {
    std::unordered_map<int, std::unordered_set<int>> list = this->parentStarList;
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
    // Both not wildcard
    if (list.find(frontStmtLineNumber) != list.end()) {
        std::unordered_set<int> children = list[frontStmtLineNumber];
        if (children.find(backStmtLineNumber) != children.end()) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

std::unordered_set<int> ParentStarTable::getAllParentStar(int childStmtLineNumber) {
    std::unordered_set<int> result;
    for (std::pair<int, std::unordered_set<int>> pair: this->parentStarList) {
        if (pair.second.find(childStmtLineNumber) != pair.second.end()) {
            result.insert(pair.first);
        }
    }
    return result;
}

std::unordered_map<int, std::unordered_set<int>> ParentStarTable::getAllParentStars() {
    return this->parentStarList;
}

void ParentStarTable::clear() {
    this->parentStarList.clear();
}
