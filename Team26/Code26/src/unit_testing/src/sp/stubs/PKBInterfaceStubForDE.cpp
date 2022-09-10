#include "PKBInterfaceStubForDE.h"

template<> void PKBInterfaceStubForDE<int, int>::addFollows(int stmt1Number, int stmt2Number) {

}

template<> void PKBInterfaceStubForDE<int, std::string>::addModifies(int stmtNumber, std::string varModified) {

}

template<> void PKBInterfaceStubForDE<std::string, std::string>::addModifies(std::string procedureName,
                                                                             std::string varModified) {

}

template<> void PKBInterfaceStubForDE<int, int>::addParent(int parentStmtNumber, int stmtNumber) {

}

template<> void PKBInterfaceStubForDE<int, int>::addParentStar(int parentStmtNumber, int stmtNumber) {

}

template<> void PKBInterfaceStubForDE<int, std::string>::addUses(int stmtNumber, std::string variableUsed) {

}

template<> void PKBInterfaceStubForDE<std::string, std::string>::addUses(std::string procedureName,
                                                                         std::string variableUsed) {

}
