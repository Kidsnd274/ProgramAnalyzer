#ifndef SPA_NEXTSTARTABLE_H
#define SPA_NEXTSTARTABLE_H

#include <unordered_map>
#include <unordered_set>

class NextStarTable {
private:
    std::unordered_map<int, std::unordered_set<int>> nextStarList;

public:
    void insertNextStar(int stmt, std::unordered_set<int> nextStarSet);
    std::unordered_map<int, std::unordered_set<int>>& getAllNextStar();
    bool existNextStar(int stmt);
};


#endif //SPA_NEXTSTARTABLE_H
