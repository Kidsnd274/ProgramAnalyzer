#ifndef SPA_AFFECTTABLE_H
#define SPA_AFFECTTABLE_H

#include <unordered_map>
#include <unordered_set>
#include "util/cfg/CFGHead.h"

class AffectTable {
private:
    std::unordered_map<int, std::unordered_set<int>> affectList;

public:
    void insertAffect(int stmt, int affectedStmt);
    std::unordered_map<int, std::unordered_set<int>>& getAllAffect();
    bool existAffect(int stmt);
    std::unordered_set<int> getAffectedSet(int stmt);
};


#endif //SPA_AFFECTTABLE_H
