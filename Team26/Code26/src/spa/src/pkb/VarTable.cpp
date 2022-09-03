//
// Created by QMS on 30/8/2022.
//
#include <stdio.h>
#include <string>
#include "VarTable.h"

using namespace std;

void VarTable::insertVar(Variable var) {
    this->varList.push_back(var);
}

vector<string> VarTable::getAllVariables() {
    vector<string> result;
    for (Variable var: this->varList) {
        result.push_back(var.name);
    }
    return result;
}