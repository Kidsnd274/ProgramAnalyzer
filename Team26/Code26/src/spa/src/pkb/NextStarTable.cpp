#include "NextStarTable.h"

void NextStarTable::insertNextStar(int stmt, std::unordered_set<int> nextStarSet) {
    std::pair<int, std::unordered_set<int>> nextStar (stmt, nextStarSet);
    this->nextStarList.insert(nextStar);
}

std::unordered_map<int, std::unordered_set<int>>& NextStarTable::getAllNextStar() {
    return this->nextStarList;
}

bool NextStarTable::existNextStar(int stmt) {
    return this->nextStarList.find(stmt) != this->nextStarList.end();
}
