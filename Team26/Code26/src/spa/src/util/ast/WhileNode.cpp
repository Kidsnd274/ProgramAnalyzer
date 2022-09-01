#include "WhileNode.h"

std::shared_ptr<TNode> WhileNode::getConditionalExpression() {
    return conditionalExpression;
}

std::vector<std::shared_ptr<StatementNode>> WhileNode::getStatementList() {
    return statementList;
}
