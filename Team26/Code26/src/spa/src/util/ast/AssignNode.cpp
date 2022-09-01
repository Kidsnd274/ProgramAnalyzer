#include "AssignNode.h"

std::string AssignNode::getVariableName() {
    return variableName;
}

std::shared_ptr<TNode> AssignNode::getExpression() {
    return expression;
}
