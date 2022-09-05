#include "AssignNode.h"

std::string AssignNode::getVariableName() {
    return variableName;
}

std::shared_ptr<TNode> AssignNode::getExpression() {
    return expression;
}

std::shared_ptr<AssignNode> AssignNode::createAssignNode(int statementNumber, std::string variableName,
                                                         std::shared_ptr<TNode> expression) {
    return std::make_shared<AssignNode>(statementNumber, variableName, expression);
}
