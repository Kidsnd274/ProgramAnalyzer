#include "ContainerTable.h"

void ContainerTable::addCondVar(int stmtNumber, std::string varName) {
    if (this->condVars.find(stmtNumber) != this->condVars.end()) {
        this->condVars.find(stmtNumber)->second.insert(varName);
    } else {
        this->condVars[stmtNumber] = {varName};
    }
}

std::unordered_set<std::string> ContainerTable::getVarNames(int stmtNumber) {
    if (this->condVars.find(stmtNumber) != this->condVars.end()) {
        return this->condVars.find(stmtNumber)->second;
    } else {
        return {};
    }
}

void ContainerTable::clear() {
    this->condVars.clear();
}
