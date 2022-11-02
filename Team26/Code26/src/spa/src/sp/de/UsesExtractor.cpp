#include "UsesExtractor.h"

void UsesExtractor::extractFromIf(std::shared_ptr<IfNode> ptr) {
    extractFromStatementsWithCond(ptr->getStatementNumber(), ptr->getConditionalExpression());
}

void UsesExtractor::extractFromWhile(std::shared_ptr<WhileNode> ptr) {
    extractFromStatementsWithCond(ptr->getStatementNumber(), ptr->getConditionalExpression());
}

void UsesExtractor::extractFromStatementsWithCond(int stmtNumber, std::shared_ptr<TNode> cond) {
    pushToStack(stmtNumber);
    extractFromExpressionTree(cond, true);
}

void UsesExtractor::extractFromExpressionTree(std::shared_ptr<TNode> ptr, bool isCond) {
    std::unordered_set<std::string> varSet;
    std::queue<std::shared_ptr<TNode>> q;
    q.push(ptr);

    while (!q.empty()) {
        if (q.front()->getNodeType() == NodeType::VariableName) {
            varSet.insert(q.front()->getValue());
        }
        if (q.front()->hasLeftNode()) q.push(q.front()->getLeftNode());
        if (q.front()->hasRightNode()) q.push(q.front()->getRightNode());
        q.pop();
    }

    if (varSet.empty()) return;

    std::vector<int> v = getAllItemsInStack();
    for (auto &var : varSet) {
        if (isCond) {
            pkb->addCondVar(v[0], var);
        }

        pkb->addUses(getProcedureName(), var);
        for (auto i : v) {
            pkb->addUses(i, var);
        }
    }
}

void UsesExtractor::extractFromPrint(std::shared_ptr<PrintNode> ptr) {
    std::string varUsed = ptr->getVariableName();
    pkb->addUses(getProcedureName(), varUsed);
    pkb->addUses(ptr->getStatementNumber(), varUsed);
    std::vector<int> v = getAllItemsInStack();
    for (auto i : v) {
        pkb->addUses(i, varUsed);
    }
}

void UsesExtractor::extractFromAssign(std::shared_ptr<AssignNode> ptr) {
    pushToStack(ptr->getStatementNumber());
    extractFromExpressionTree(ptr->getExpression(), false);
    popFromStack();
}
