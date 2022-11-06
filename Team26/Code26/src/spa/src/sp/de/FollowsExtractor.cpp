#include "FollowsExtractor.h"

void FollowsExtractor::addToPkb(std::vector<std::shared_ptr<StatementNode>> stmtList) {
    for (int i = stmtList.size()-1; i > 0; --i) {
        pkb->addRelation(RelationType::FOLLOWS, stmtList[i-1]->getStatementNumber(), stmtList[i]->getStatementNumber());
    }
}

void FollowsExtractor::extractFromProcedure(std::shared_ptr<ProcedureNode> ptr) {
    std::vector<std::shared_ptr<StatementNode>> stmtList = ptr->getStatementList();
    addToPkb(stmtList);
}


void FollowsExtractor::extractFromIf(std::shared_ptr<IfNode> ptr) {
    pushToStack(ptr->getStatementNumber());
    std::vector<std::shared_ptr<StatementNode>> stmtList = ptr->getIfStatementList();
    addToPkb(stmtList);
    stmtList = ptr->getElseStatementList();
    addToPkb(stmtList);
}


void FollowsExtractor::extractFromWhile(std::shared_ptr<WhileNode> ptr) {
    pushToStack(ptr->getStatementNumber());
    std::vector<std::shared_ptr<StatementNode>> stmtList = ptr->getStatementList();
    addToPkb(stmtList);
}
