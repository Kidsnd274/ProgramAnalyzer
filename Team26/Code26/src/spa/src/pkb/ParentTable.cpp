#include "ParentTable.h"

void ParentTable::insertParent(int parentStmtLineNumber, int childStmtLineNumber) {
    std::pair<int,std::unordered_set<int>> parent (parentStmtLineNumber, {childStmtLineNumber});
    if (this->parentList.find(parentStmtLineNumber) != parentList.end()) {
        this->parentList[parentStmtLineNumber].insert(childStmtLineNumber);
    } else {
        this->parentList.insert(parent);
    }
}

std::unordered_map<int, std::unordered_set<int>> ParentTable::getAllParents() {
    return this->parentList;
}

void ParentTable::clear() {
    this->parentList.clear();
}
