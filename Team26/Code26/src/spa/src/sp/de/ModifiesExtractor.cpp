#include "ModifiesExtractor.h"

void ModifiesExtractor::extractFromRead(std::shared_ptr<ReadNode> ptr) {
    extractFromModifiesStatements(ptr->getVariableName(), ptr->getStatementNumber());
}

void ModifiesExtractor::extractFromAssign(std::shared_ptr<AssignNode> ptr) {
    extractFromModifiesStatements(ptr->getVariableName(), ptr->getStatementNumber());
}

void ModifiesExtractor::extractFromModifiesStatements(std::string varModified, int stmtNumber) {
    pkb->addRelation(RelationType::MODIFIES_S, stmtNumber, varModified);
    pkb->addRelation(RelationType::MODIFIES_S, getProcedureName(), varModified);
    std::vector<int> v = getAllItemsInStack();
    for (auto i : v) {
        pkb->addRelation(RelationType::MODIFIES_S, i, varModified);
    }
}

void ModifiesExtractor::extractFromIf(std::shared_ptr<IfNode> ptr) {
    pushToStack(ptr->getStatementNumber());
}

void ModifiesExtractor::extractFromWhile(std::shared_ptr<WhileNode> ptr) {
    pushToStack(ptr->getStatementNumber());
}
