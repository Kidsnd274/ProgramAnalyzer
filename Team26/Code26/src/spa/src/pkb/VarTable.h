//
// Created by QMS on 30/8/2022.
//

#ifndef SPA_VARTABLE_H
#define SPA_VARTABLE_H

//#pragma once
#include <string>
#include <unordered_set>

using namespace std;

class VarTable {
private:
    unordered_set<string> varList;

public:
    void insertVar(string var);
    unordered_set<string> getAllVariables();
    void clear();
};

#endif //SPA_VARTABLE_H
