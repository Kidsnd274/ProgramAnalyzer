#include "FollowsExtractor.h"
void FollowsExtractor::extractFromIf(std::shared_ptr<IfNode> ptr) {
    pushToStack(ptr->getStatementNumber());
    std::vector<std::shared_ptr<StatementNode>> stmtList = ptr->getIfStatementList();
    int lastNum = 0;
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
    std::vector<std::shared_ptr<StatementNode>> stmtList = ptr->getIfStatementList();
    int lastNum = 0;
    for(int i = stmtList.size()-1; i > 0; --i) {
        //pkb->addFollows(stmtList[i-1]->getStatementNumber(), stmtList[i]->getStatementNumber());
    }
}