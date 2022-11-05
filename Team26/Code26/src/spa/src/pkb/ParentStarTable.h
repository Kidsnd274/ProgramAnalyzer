//
// Created by QMS on 13/9/2022.
//

#ifndef SPA_PARENTSTARTABLE_H
#define SPA_PARENTSTARTABLE_H

#include <stdio.h>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class ParentStarTable {
private:
    unordered_map<int, unordered_set<int>> parentStarList;
public:
    void insertParentStar(int parentStmtLineNumber, int childStmtLineNumber);
    bool existParentStar(int parentStmtLineNumber, int childStmtLineNumber);
    unordered_set<int> getAllParentStar(int childStmtLineNumber);
    unordered_map<int, unordered_set<int>> getAllParentStars();
    void clear();
};

#endif //SPA_PARENTSTARTABLE_H
