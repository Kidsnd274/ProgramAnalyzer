#include "AffectStarTable.h"

// S1 (Major): DRY - Code structure of class and methods are similar to other relationship classes e.g. AffectsTable, NextTable, FollowsTable, FollowStarTable

void AffectStarTable::insertAffectStar(int stmt, std::unordered_set<int> affectStarSet) {
    std::pair<int, std::unordered_set<int>> affectStar(stmt, affectStarSet);
    this->affectStarList.insert(affectStar);
}

std::unordered_map<int, std::unordered_set<int>>& AffectStarTable::getAllAffectStar() {
    return this->affectStarList;
}

bool AffectStarTable::existAffectStar(int stmt) {
    return this->affectStarList.find(stmt) != this->affectStarList.end();
}

std::unordered_set<int> AffectStarTable::getAffectedStarSet(int stmt) {
    return this->affectStarList[stmt];
}

void AffectStarTable::clear() {
    this->affectStarList.clear();
}
