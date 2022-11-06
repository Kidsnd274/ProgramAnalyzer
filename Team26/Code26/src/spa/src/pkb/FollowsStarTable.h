#ifndef SPA_FOLLOWSSTARTABLE_H
#define SPA_FOLLOWSSTARTABLE_H

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include "util/Common.h"

class FollowsStarTable {
private:
    std::unordered_map<STMT_NUM, STMT_NUM> followsStarList;

public:
    void insertFollowsStar(STMT_NUM frontStmtLineNumber, STMT_NUM backStmtLineNumber);
    bool existFollowsStar(STMT_NUM frontStmtLineNumber, STMT_NUM backStmtLineNumber);
    std::unordered_map<STMT_NUM, STMT_NUM> getAllFollowStars();
    void clear();
};

#endif  // SPA_FOLLOWSSTARTABLE_H
