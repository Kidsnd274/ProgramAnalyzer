#include "PKBInterfaceStubForDE.h"

void PKBInterfaceStubForDE::addFollows(int stmt1Number, int stmt2Number) {
    this->followsMap[stmt1Number] = stmt2Number;
}

void PKBInterfaceStubForDE::addParent(int parentStmtNumber, int stmtNumber) {
    this->parentMapIntInt[stmtNumber] = parentStmtNumber;
}

void PKBInterfaceStubForDE::addParentStar(int parentStmtNumber, int stmtNumber) {
    this->parentStarMapIntInt[stmtNumber] = parentStmtNumber;
}

void PKBInterfaceStubForDE::addModifies(int stmtNumber, std::string varModified) {
    auto newPair = std::pair<int, std::string>(stmtNumber, varModified);
    this->modifiesMapIntString.insert(newPair);
}

void PKBInterfaceStubForDE::addModifies(std::string procedureName, std::string varModified) {
    auto newPair = std::pair<std::string, std::string>(procedureName, varModified);
    this->modifiesMapStringString.insert(newPair);
}

void PKBInterfaceStubForDE::addUses(int stmtNumber, std::string variableUsed) {
    auto newPair = std::pair<int, std::string>(stmtNumber, variableUsed);
    this->usesMapIntString.insert(newPair);
}

void PKBInterfaceStubForDE::addUses(std::string procedureName, std::string variableUsed) {
    auto newPair = std::pair<std::string, std::string>(procedureName, variableUsed);
    this->usesMapStringString.insert(newPair);
}
