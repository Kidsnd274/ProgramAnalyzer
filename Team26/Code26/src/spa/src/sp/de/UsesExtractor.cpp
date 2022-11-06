#include "UsesExtractor.h"

#include <utility>

void UsesExtractor::addToPkb(std::unordered_set<std::string> &varSet, bool isCond) {
    std::vector<int> v = getAllItemsInStack();
    for (auto &var : varSet) {
        if (isCond) {
            pkb->addCondVar(v[0], var);
        }

        pkb->addRelation(RelationType::USES_S, getProcedureName(), var);
        for (auto i : v) {
            pkb->addRelation(RelationType::USES_S, i, var);
        }
    }
}

void UsesExtractor::extractFromIf(std::shared_ptr<IfNode> ptr) {
    extractFromStatementsWithCond(ptr->getStatementNumber(), ptr->getConditionalExpression());
}

void UsesExtractor::extractFromWhile(std::shared_ptr<WhileNode> ptr) {
    extractFromStatementsWithCond(ptr->getStatementNumber(), ptr->getConditionalExpression());
}

void UsesExtractor::extractFromStatementsWithCond(int stmtNumber, const std::shared_ptr<TNode>& cond) {
    pushToStack(stmtNumber);
    extractFromExpressionTree(cond, true);
}

void UsesExtractor::extractFromExpressionTree(const std::shared_ptr<TNode>& ptr, bool isCond) {
    std::unordered_set<std::string> varSet;
    std::queue<std::shared_ptr<TNode>> q;
    q.push(ptr);

    while (!q.empty()) {
        if (q.front()->getNodeType() == NodeType::VariableName) {
            varSet.insert(q.front()->getValue());
        }

        if (q.front()->hasLeftNode()) {
            q.push(q.front()->getLeftNode());
        }

        if (q.front()->hasRightNode()) {
            q.push(q.front()->getRightNode());
        }

        q.pop();
    }

    if (varSet.empty()) return;

    addToPkb(varSet, isCond);
}

void UsesExtractor::extractFromPrint(std::shared_ptr<PrintNode> ptr) {
    std::string varUsed = ptr->getVariableName();
    pkb->addRelation(RelationType::USES_S,getProcedureName(), varUsed);
    pkb->addRelation(RelationType::USES_S,ptr->getStatementNumber(), varUsed);
    std::vector<int> v = getAllItemsInStack();
    for (auto i : v) {
        pkb->addRelation(RelationType::USES_S,i, varUsed);
    }
}

void UsesExtractor::extractFromAssign(std::shared_ptr<AssignNode> ptr) {
    pushToStack(ptr->getStatementNumber());
    extractFromExpressionTree(ptr->getExpression(), false);
    popFromStack();
}
