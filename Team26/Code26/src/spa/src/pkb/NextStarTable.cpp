#include "NextStarTable.h"

void NextStarTable::insertNextStar(STMT_NUM stmt, std::unordered_set<STMT_NUM> nextStarSet) {
    std::pair<STMT_NUM, std::unordered_set<STMT_NUM>> nextStar (stmt, nextStarSet);
    this->nextStarList.insert(nextStar);
}

std::unordered_map<STMT_NUM, std::unordered_set<STMT_NUM>>& NextStarTable::getAllNextStar() {
    return this->nextStarList;
}

bool NextStarTable::existNextStar(STMT_NUM stmt) {
    return this->nextStarList.find(stmt) != this->nextStarList.end();
}

std::unordered_set<STMT_NUM> NextStarTable::getNextStar(STMT_NUM stmt) {
    return this->nextStarList[stmt];
}
