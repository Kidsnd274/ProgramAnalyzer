//
// Created by QMS on 30/8/2022.
//
#include <stdio.h>
#include <string>
#include <unordered_set>
#include "VarTable.h"

using namespace std;

void VarTable::insertVar(string var) {
    this->varList.insert(var);
}

unordered_set<string> VarTable::getAllVariables() {
    return this->varList;
}

void VarTable::clear() {
    this->varList.clear();
}
