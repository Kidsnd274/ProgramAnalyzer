#include "UsesExtractor.h"

void UsesExtractor::extractFromIf(std::shared_ptr<IfNode> ptr) {
    extractFromStatementsWithCond(ptr->getStatementNumber(), ptr->getConditionalExpression());
}

void UsesExtractor::extractFromWhile(std::shared_ptr<WhileNode> ptr) {
    extractFromStatementsWithCond(ptr->getStatementNumber(), ptr->getConditionalExpression());
}

void UsesExtractor::extractFromStatementsWithCond(int stmtNumber, std::shared_ptr<TNode> cond) {
    pushToStack(stmtNumber);
    extractFromCond(cond);
}

void UsesExtractor::extractFromCond(std::shared_ptr<TNode> ptr) {
    std::unordered_set<std::string> varSet;
    std::queue<std::shared_ptr<TNode>> q;
    q.push(ptr);

    while(!q.empty()) {
        if(q.front()->getNodeType() == NodeType::VariableName) {
            varSet.insert(q.front()->getValue());
        }
        if(q.front()->hasLeftNode()) q.push(q.front()->getLeftNode());
        if(q.front()->hasRightNode()) q.push(q.front()->getRightNode());
        q.pop();
    }

    if(varSet.empty()) return;

    std::vector<int> v = getAllItemsInStack();
    for(auto i : v) {
        for(auto &var : varSet) {
            //pkb.addUses(i, var);
        }
    }
}