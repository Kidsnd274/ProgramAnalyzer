//
// Created by QMS on 13/9/2022.
//

#ifndef SPA_FOLLOWSTABLE_H
#define SPA_FOLLOWSTABLE_H

#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class FollowsTable {
private:
    unordered_map<int, int> followsList;
public:
    void insertFollows(int frontStmtLineNumber, int backStmtLineNumber);
    bool existFollows(int frontStmtLineNumber, int backStmtLineNumber);
    std::unordered_map<int, int> getAllFollows();
    void clear();
};

#endif //SPA_FOLLOWSTABLE_H
