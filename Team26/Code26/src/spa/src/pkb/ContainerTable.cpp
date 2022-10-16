#include "ContainerTable.h"

void ContainerTable::insertCondition(int stmtLineNumber, std::shared_ptr<TNode> conditionNode) {
    this->containerList.insert({stmtLineNumber, conditionNode});
}

std::shared_ptr<TNode> ContainerTable::getConditionByStmtNumber(int stmtNumber) {
    if (this->containerList.find(stmtNumber) != this->containerList.end()) {
        return this->containerList.find(stmtNumber)->second;
    }
    return nullptr;
}

std::string ContainerTable::getVarName(std::shared_ptr<TNode> conditionPointer) {
    return conditionPointer->getLeftNode()->getValue();
}