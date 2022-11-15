#include "FollowsTable.h"

// S1 (Major): DRY - Class structure and methods are similar to FollowsStarTable
void FollowsTable::insertFollows(int frontStmtLineNumber, int backStmtLineNumber) {
    std::pair<int, int> follows(frontStmtLineNumber, backStmtLineNumber);
    this->followsList.insert(follows);
}

bool FollowsTable::existFollows(int frontStmtLineNumber, int backStmtLineNumber) {
    std::unordered_map<int, int> list = this->followsList;
    if (list.find(frontStmtLineNumber) != list.end() && list[frontStmtLineNumber] == backStmtLineNumber) {
        return true;
    }
    return false;
}

std::unordered_map<int, int> FollowsTable::getAllFollows() {
    return this->followsList;
}

void FollowsTable::clear() {
    this->followsList.clear();
}
