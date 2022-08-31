#include "ConditionalOperatorNode.h"

std::shared_ptr<TNode> ConditionalOperatorNode::getLeftNode() {
    return leftNode;
}

std::shared_ptr<TNode> ConditionalOperatorNode::getRightNode() {
    return rightNode;
}