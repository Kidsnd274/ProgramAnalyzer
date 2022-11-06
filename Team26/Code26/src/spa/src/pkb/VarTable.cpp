#include "VarTable.h"

void VarTable::insertVar(std::string var) {
    this->varList.push_back(var);
}

std::vector<std::string> VarTable::getAllVariables() {
    return this->varList;
}

void VarTable::clear() {
    this->varList.clear();
}
