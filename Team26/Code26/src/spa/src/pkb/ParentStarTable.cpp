#include "ParentStarTable.h"

void ParentStarTable::insertParentStar(int frontStmtLineNumber, int backStmtLineNumber) {
    std::pair<int, std::unordered_set<int>> parentStar (frontStmtLineNumber, {backStmtLineNumber});
    if (this->parentStarList.find(frontStmtLineNumber) != parentStarList.end()) {
        this->parentStarList[frontStmtLineNumber].insert(backStmtLineNumber);
    } else {
        this->parentStarList.insert(parentStar);
    }
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
