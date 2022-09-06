//
// Created by QMS on 30/8/2022.
//

#ifndef SPA_VARTABLE_H
#define SPA_VARTABLE_H

//#pragma once
#include <string>
#include "Variable.h"

using namespace std;

class VarTable {
private:
    vector<Variable> varList;

public:
    void insertVar(Variable var);
    vector<string> getAllVariables();
};

#endif //SPA_VARTABLE_H
