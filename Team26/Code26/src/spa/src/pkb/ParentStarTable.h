//
// Created by QMS on 13/9/2022.
//

#ifndef SPA_PARENTSTARTABLE_H
#define SPA_PARENTSTARTABLE_H

#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class ParentStarTable {
private:
    unordered_map<int, vector<int>> parentStarList;
public:
    void insertParentStar(int parentStmtLineNumber, int childStmtLineNumber);
    bool existParentStar(int parentStmtLineNumber, int childStmtLineNumber);
    vector<int> getAllParentStar(int stmtLineNumber);
};

#endif //SPA_PARENTSTARTABLE_H
