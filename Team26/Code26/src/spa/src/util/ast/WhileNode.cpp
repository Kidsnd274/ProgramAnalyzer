#include "WhileNode.h"

std::shared_ptr<TNode> WhileNode::getConditionalExpression() {
    return conditionalExpression;
}

std::vector<std::shared_ptr<StatementNode>> WhileNode::getStatementList() {
    return statementList;
}

std::shared_ptr<WhileNode> WhileNode::createWhileNode(int statementNumber, std::shared_ptr<TNode> conditionalExpression,
                                                      std::vector<std::shared_ptr<StatementNode>> statementList) {
    return std::make_shared<WhileNode>(statementNumber, conditionalExpression, statementList);
}
