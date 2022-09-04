//
// Created by QMS on 4/9/2022.
//

#ifndef SPA_CONSTANTTABLE_H
#define SPA_CONSTANTTABLE_H

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class ConstantTable {
private:
    vector<int> constList;
public:
    void insertConst(int constant);
    vector<string> getAllConstants();
};

#endif //SPA_CONSTANTTABLE_H
