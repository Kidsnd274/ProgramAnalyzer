//
// Created by QMS on 13/9/2022.
//

#ifndef SPA_FOLLOWSSTARTABLE_H
#define SPA_FOLLOWSSTARTABLE_H

#include <stdio.h>
#include <string>
#include <unordered_map>

using namespace std;

class FollowsStarTable {
private:
    unordered_map<int, int> followsStarList;
public:
    void insertFollowsStar(int frontStmtLineNumber, int backStmtLineNumber);
    bool existFollowsStar(int frontStmtLineNumber, int backStmtLineNumber);
    unordered_map<int, int> getAllFollowStars();
    void clear();
};

#endif //SPA_FOLLOWSSTARTABLE_H
