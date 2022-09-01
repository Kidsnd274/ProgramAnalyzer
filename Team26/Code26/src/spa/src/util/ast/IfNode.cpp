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
