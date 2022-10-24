#ifndef SPA_AFFECTSTARTABLE_H
#define SPA_AFFECTSTARTABLE_H

#include <unordered_map>
#include <unordered_set>

class AffectStarTable {
private:
    std::unordered_map<int, std::unordered_set<int>> affectStarList;

public:
    void insertAffectStar(int stmt, std::unordered_set<int> affectStarSet);
    std::unordered_map<int, std::unordered_set<int>>& getAllAffectStar();
    bool existAffectStar(int stmt);
};


#endif //SPA_AFFECTSTARTABLE_H
