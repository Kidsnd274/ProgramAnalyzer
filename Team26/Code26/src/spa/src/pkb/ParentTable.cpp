#include <unordered_set>
#include <algorithm>
#include "ParentTable.h"

void ParentTable::insertParent(int parentStmtLineNumber, int childStmtLineNumber) {
    std::pair<int,std::unordered_set<int>> parent (parentStmtLineNumber, {childStmtLineNumber});
    if (this->parentList.find(parentStmtLineNumber) != parentList.end()) {
        this->parentList[parentStmtLineNumber].insert(childStmtLineNumber);
    } else {
        this->parentList.insert(parent);
    }
}

bool ParentTable::existParent(int parentStmtLineNumber, int childStmtLineNumber) {
    std::unordered_map<int,std::unordered_set<int>> list = this->parentList;
    bool isParentWildcard = parentStmtLineNumber == 0;
    bool isChildWildcard = childStmtLineNumber == 0;
    if (isParentWildcard && isChildWildcard) {
        return list.size() != 0;
    }
    if (isParentWildcard) {
        for (auto &p: list) {
            if (p.second.find(childStmtLineNumber) != p.second.end()) {
                return true;
            }
        }
        return false;
    }
    if (isChildWildcard) {
        if (list.find(parentStmtLineNumber) != list.end()) {
            return list[parentStmtLineNumber].size() != 0;
        }
    }
    //Both not wildcard
    if (list.find(parentStmtLineNumber) != list.end()) {
        std::unordered_set<int> children = list[parentStmtLineNumber];
        if (children.find(childStmtLineNumber) != children.end()) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

std::unordered_map<int, std::unordered_set<int>> ParentTable::getAllParents() {
    return this->parentList;
}

void ParentTable::clear() {
    this->parentList.clear();
}
