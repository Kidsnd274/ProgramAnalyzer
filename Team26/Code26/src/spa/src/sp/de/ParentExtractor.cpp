#include "ParentExtractor.h"

void ParentExtractor::extractFromWhile(std::shared_ptr<WhileNode> ptr) {
    std::vector<std::shared_ptr<StatementNode>> stmtList = ptr->getStatementList();
    extractFromStatementsWithStatementList(ptr->getStatementNumber(), stmtList);
}

void ParentExtractor::extractFromIf(std::shared_ptr<IfNode> ptr) {
    std::vector<std::shared_ptr<StatementNode>> stmtList = ptr->getIfStatementList();
    std::vector<std::shared_ptr<StatementNode>> elseStmtList = ptr->getElseStatementList();
    stmtList.insert(stmtList.end(), elseStmtList.begin(), elseStmtList.end());
    extractFromStatementsWithStatementList(ptr->getStatementNumber(), stmtList);
}

void ParentExtractor::extractFromStatementsWithStatementList(int stmtNum, std::vector<std::shared_ptr<StatementNode>> &stmtList) {
    pushToStack(stmtNum);
    std::vector<int> v = getAllItemsInStack();
    for (auto &stmt : stmtList) {
        //pkb.addParent(v.top(), stmt->getStatementNumber());
        for (auto p : v) {
            //pkb.addParentStar(p, stmt->getStatementNumber()); <- let qps handle O(n^2)
        }
    }
}