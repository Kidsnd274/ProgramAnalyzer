#include "PKBInterfaceStubForDE.h"

void PKBInterfaceStubForDE::addFollows(int stmt1Number, int stmt2Number) {
    this->followsMap[stmt1Number] = stmt2Number;
}

void PKBInterfaceStubForDE::addParent(int parentStmtNumber, int stmtNumber) {
    this->parentMapIntInt[stmtNumber] = parentStmtNumber;
}

void PKBInterfaceStubForDE::addParentStar(int parentStmtNumber, int stmtNumber) {
    this->parentStarMapIntInt.insert({parentStmtNumber, stmtNumber});
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

void PKBInterfaceStubForDE::addReadStatement(int statementNumber, int stmtListNum) {
    this->statements.insert({statementNumber, stmtListNum});
}

void PKBInterfaceStubForDE::addAssignStatement(int statementNumber, int stmtListNum, std::shared_ptr<TNode> ptr) {
    this->statements.insert({statementNumber, stmtListNum});
}

void PKBInterfaceStubForDE::addWhileStatement(int statementNumber, int stmtListNum) {
    this->statements.insert({statementNumber, stmtListNum});
}

void PKBInterfaceStubForDE::addIfStatement(int statementNumber, int stmtListNum) {
    this->statements.insert({statementNumber, stmtListNum});
}

void PKBInterfaceStubForDE::addPrintStatement(int statementNumber, int stmtListNum) {
    this->statements.insert({statementNumber, stmtListNum});
}