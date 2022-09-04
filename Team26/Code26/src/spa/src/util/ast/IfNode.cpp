#include "IfNode.h"

std::shared_ptr<TNode> IfNode::getConditionalExpression() {
    return conditionalExpression;
}

std::vector<std::shared_ptr<StatementNode>> IfNode::getIfStatementList() {
    return ifStatementList;
}

std::vector<std::shared_ptr<StatementNode>> IfNode::getElseStatementList() {
    return elseStatementList;
}

std::shared_ptr<IfNode> IfNode::createIfNode(int statementNumber, std::shared_ptr<TNode> conditionalExpression,
                                             std::vector<std::shared_ptr<StatementNode>> ifStatementList,
                                             std::vector<std::shared_ptr<StatementNode>> elseStatementList) {
    return std::make_shared<IfNode>(statementNumber, conditionalExpression, ifStatementList, elseStatementList);
}
