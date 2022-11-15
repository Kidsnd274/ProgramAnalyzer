#include "ParentTable.h"

// S1 (Major): DRY - Class structure and methods are similar to ParentStarTable
void ParentTable::insertParent(int parentStmtLineNumber, int childStmtLineNumber) {
    std::pair<int, std::vector<int>> parent(parentStmtLineNumber, {childStmtLineNumber});
    if (this->parentList.find(parentStmtLineNumber) != parentList.end()) {
        this->parentList[parentStmtLineNumber].push_back(childStmtLineNumber);
    } else {
        this->parentList.insert(parent);
    }
}

std::unordered_map<int, std::vector<int>> ParentTable::getAllParents() {
    return this->parentList;
}

void ParentTable::clear() {
    this->parentList.clear();
}
