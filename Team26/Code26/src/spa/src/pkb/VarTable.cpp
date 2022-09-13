//
// Created by QMS on 30/8/2022.
//
#include <stdio.h>
#include <string>
#include <vector>
#include "VarTable.h"

using namespace std;

void VarTable::insertVar(string var) {
    this->varList.push_back(var);
}

vector<string> VarTable::getAllVariables() {
    return this->varList;
}