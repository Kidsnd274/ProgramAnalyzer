#include "VarTable.h"

using namespace std;

void VarTable::insertVar(std::string var) {
    this->varList.insert(var);
}

std::unordered_set<std::string> VarTable::getAllVariables() {
    return this->varList;
}

void VarTable::clear() {
    this->varList.clear();
}
