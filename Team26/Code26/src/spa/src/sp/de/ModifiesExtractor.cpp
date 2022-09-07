#include "ModifiesExtractor.h"

void ModifiesExtractor::extractFromRead(std::shared_ptr<ReadNode> ptr) {
    extractFromModifiesStatements(ptr->getVariableName(), ptr->getStatementNumber());
}

void ModifiesExtractor::extractFromAssign(std::shared_ptr<AssignNode> ptr) {
    extractFromModifiesStatements(ptr->getVariableName(), ptr->getStatementNumber());
}

void ModifiesExtractor::extractFromModifiesStatements(std::string varModified, int stmtNumber) {
    //pkb.addModifies(stmtNumber, varModified);
    //pkb.addModifies(getProcedureName(), varModified);
    std::vector<int> v = getAllItemsInStack();
    for(auto i : v) {
        //pkb.addModifies(i, varModified);
    }
}