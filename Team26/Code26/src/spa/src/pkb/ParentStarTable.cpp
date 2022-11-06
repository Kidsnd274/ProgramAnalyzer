#include "ParentStarTable.h"

void ParentStarTable::insertParentStar(int frontStmtLineNumber, int backStmtLineNumber) {
    std::pair<int, std::vector<int>> parentStar(frontStmtLineNumber, {backStmtLineNumber});
    if (this->parentStarList.find(frontStmtLineNumber) != parentStarList.end()) {
        this->parentStarList[frontStmtLineNumber].push_back(backStmtLineNumber);
    } else {
        this->parentStarList.insert(parentStar);
    }
}

bool ParentStarTable::existParentStar(int frontStmtLineNumber, int backStmtLineNumber) {
    std::unordered_map<int, std::vector<int>> list = this->parentStarList;
    bool isParentWildcard = frontStmtLineNumber == 0;
    bool isChildWildcard = backStmtLineNumber == 0;
    if (isParentWildcard && isChildWildcard) {
        return list.size() != 0;
    }
    if (isParentWildcard) {
        for (auto &p : list) {
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
    // Both not wildcard
    if (list.find(frontStmtLineNumber) != list.end()) {
        std::vector<int> children = list[frontStmtLineNumber];
        if (std::find(children.begin(), children.end(), backStmtLineNumber) != children.end()) {
            return true;
        } else {
            return false;
        }
    }
    return false;
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
