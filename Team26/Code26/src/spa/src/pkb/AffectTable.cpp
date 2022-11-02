#include "AffectTable.h"

void AffectTable::insertAffect(int stmt, int affectedStmt) {
    if (this->affectList.find(stmt) != this->affectList.end()) {
        this->affectList.find(stmt)->second.insert(affectedStmt);
    } else {
        std::pair<int, std::unordered_set<int>> affect (stmt, {affectedStmt});
        this->affectList.insert(affect);
    }
}

std::unordered_map<int, std::unordered_set<int>>& AffectTable::getAllAffect() {
    return this->affectList;
}

bool AffectTable::existAffect(int stmt) {
    return this->affectList.find(stmt) != this->affectList.end();
}

std::unordered_set<int> AffectTable::getAffectedSet(int stmt) {
    return this->affectList[stmt];
}

void AffectTable::clear() {
    this->affectList.clear();
}
