#ifndef SPA_FOLLOWSTABLE_H
#define SPA_FOLLOWSTABLE_H

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

class FollowsTable {
private:
    std::unordered_map<int, int> followsList;
public:
    void insertFollows(int frontStmtLineNumber, int backStmtLineNumber);
    bool existFollows(int frontStmtLineNumber, int backStmtLineNumber);
    std::unordered_map<int, int> getAllFollows();
    void clear();
};

#endif  // SPA_FOLLOWSTABLE_H
