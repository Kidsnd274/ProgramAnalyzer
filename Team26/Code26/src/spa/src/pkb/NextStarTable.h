#ifndef SPA_NEXTSTARTABLE_H
#define SPA_NEXTSTARTABLE_H

#include <unordered_map>
#include <unordered_set>
#include "util/cfg/CFGHead.h"

class NextStarTable {
private:
    std::unordered_map<STMT_NUM, std::unordered_set<STMT_NUM>> nextStarList;

public:
    void insertNextStar(STMT_NUM stmt, std::unordered_set<STMT_NUM> nextStarSet);
    std::unordered_map<STMT_NUM, std::unordered_set<STMT_NUM>>& getAllNextStar();
    bool existNextStar(STMT_NUM stmt);
};


#endif //SPA_NEXTSTARTABLE_H
