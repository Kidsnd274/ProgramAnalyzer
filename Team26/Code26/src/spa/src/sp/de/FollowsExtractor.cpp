#include "FollowsExtractor.h"

void FollowsExtractor::extractFromProcedure(std::shared_ptr<ProcedureNode> ptr) {
    std::vector<std::shared_ptr<StatementNode>> stmtList = ptr->getStatementList();
    for(int i = stmtList.size()-1; i > 0; --i) {
        //pkb->addFollows(stmtList[i-1]->getStatementNumber(), stmtList[i]->getStatementNumber());
    }
}


void FollowsExtractor::extractFromIf(std::shared_ptr<IfNode> ptr) {
    pushToStack(ptr->getStatementNumber());
    std::vector<std::shared_ptr<StatementNode>> stmtList = ptr->getIfStatementList();
    for(int i = stmtList.size()-1; i > 0; --i) {
        //pkb->addFollows(stmtList[i-1]->getStatementNumber(), stmtList[i]->getStatementNumber());
    }
    stmtList = ptr->getElseStatementList();
    for(int i = stmtList.size()-1; i > 0; --i) {
        //pkb->addFollows(stmtList[i-1]->getStatementNumber(), stmtList[i]->getStatementNumber());
    }
}

void FollowsExtractor::extractFromWhile(std::shared_ptr<WhileNode> ptr) {
    pushToStack(ptr->getStatementNumber());
    std::vector<std::shared_ptr<StatementNode>> stmtList = ptr->getStatementList();
    for(int i = stmtList.size()-1; i > 0; --i) {
        //pkb->addFollows(stmtList[i-1]->getStatementNumber(), stmtList[i]->getStatementNumber());
    }
}