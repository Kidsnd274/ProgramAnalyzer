#ifndef SPA_PARENTSTARTABLE_H
#define SPA_PARENTSTARTABLE_H

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "util/Common.h"

class ParentStarTable {
private:
    std::unordered_map<STMT_NUM, std::vector<STMT_NUM>> parentStarList;

public:
    void insertParentStar(STMT_NUM parentStmtLineNumber, STMT_NUM childStmtLineNumber);
    bool existParentStar(STMT_NUM parentStmtLineNumber, STMT_NUM childStmtLineNumber);
    std::unordered_set<STMT_NUM> getAllParentStar(STMT_NUM childStmtLineNumber);
    std::unordered_map<STMT_NUM, std::vector<STMT_NUM>> getAllParentStars();
    void clear();
};

#endif  // SPA_PARENTSTARTABLE_H
