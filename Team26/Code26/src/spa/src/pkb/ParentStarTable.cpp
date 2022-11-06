#include "ParentStarTable.h"

void ParentStarTable::insertParentStar(int frontStmtLineNumber, int backStmtLineNumber) {
    std::pair<int, std::vector<int>> parentStar(frontStmtLineNumber, {backStmtLineNumber});
    if (this->parentStarList.find(frontStmtLineNumber) != parentStarList.end()) {
        this->parentStarList[frontStmtLineNumber].push_back(backStmtLineNumber);
    } else {
        this->parentStarList.insert(parentStar);
    }
}

std::unordered_set<int> ParentStarTable::getAllParentStar(int childStmtLineNumber) {
    std::unordered_set<int> result;
    for (std::pair<int, std::vector<int>> pair : this->parentStarList) {
        if (std::find(pair.second.begin(), pair.second.end(), childStmtLineNumber) != pair.second.end()) {
            result.insert(pair.first);
        }
    }
    return result;
}

std::unordered_map<int, std::vector<int>> ParentStarTable::getAllParentStars() {
    return this->parentStarList;
}

void ParentStarTable::clear() {
    this->parentStarList.clear();
}
