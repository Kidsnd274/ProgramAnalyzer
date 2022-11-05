//
// Created by QMS on 4/9/2022.
//

#ifndef SPA_CONSTANTTABLE_H
#define SPA_CONSTANTTABLE_H

#include <stdio.h>
#include <string>
#include <unordered_set>

using namespace std;

class ConstantTable {
private:
    unordered_set<int> constList;
public:
    void insertConst(int constant);
    unordered_set<string> getAllConstants();
    void clear();
};

#endif //SPA_CONSTANTTABLE_H
