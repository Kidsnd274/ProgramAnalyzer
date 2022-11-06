#include "FollowsStarTable.h"

void FollowsStarTable::insertFollowsStar(int frontStmtLineNumber, int backStmtLineNumber) {
    std::pair<int, int> followsStar(frontStmtLineNumber, backStmtLineNumber);
    this->followsStarList.insert(followsStar);
}

std::unordered_map<int, int> FollowsStarTable::getAllFollowStars() {
    return this->followsStarList;
}

void FollowsStarTable::clear() {
    this->followsStarList.clear();
}
