#include "AffectStarTable.h"

void AffectStarTable::insertAffectStar(int stmt, std::unordered_set<int> affectStarSet) {
    std::pair<int, std::unordered_set<int>> affectStar (stmt, affectStarSet);
    this->affectStarList.insert(affectStar);
}

std::unordered_map<int, std::unordered_set<int>>& AffectStarTable::getAllAffectStar() {
    return this->affectStarList;
}

bool AffectStarTable::existAffectStar(int stmt) {
    return this->affectStarList.find(stmt) != this->affectStarList.end();
}

void AffectStarTable::clear() {
    this->affectStarList.clear();
}
