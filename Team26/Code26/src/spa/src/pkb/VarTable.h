//
// Created by QMS on 30/8/2022.
//

#ifndef SPA_VARTABLE_H
#define SPA_VARTABLE_H

//#pragma once
#include <string>

using namespace std;

class VarTable {
private:
    vector<string> varList;

public:
    void insertVar(string var);
    vector<string> getAllVariables();
};

#endif //SPA_VARTABLE_H
