//
// Created by QMS on 13/9/2022.
//

#ifndef SPA_PARENTTABLE_H

#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class ParentTable {
private:
    unordered_map<int, vector<int>> parentList;
public:
    void insertParent(int parentStmtLineNumber, int childStmtListNumber);
    bool existParent(int parentStmtLineNumber, int childStmtListNumber);
};

#endif //SPA_PARENTTABLE_H
