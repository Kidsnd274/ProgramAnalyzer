#include "VarTable.h"

// S1 (Major): DRY - Class structure and methods are similar to ConstantTable

void VarTable::insertVar(std::string var) {
    this->varList.push_back(var);
}

std::vector<std::string> VarTable::getAllVariables() {
    return this->varList;
}

void VarTable::clear() {
    this->varList.clear();
}
