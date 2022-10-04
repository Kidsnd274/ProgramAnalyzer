#include "CFGNode.h"

#include <utility>

int CFGNode::getStatementNumber() const {
    return statementNumber;
}

bool CFGNode::isThereLeftNode() {
    return (leftNode != nullptr);
}

bool CFGNode::isThereRightNode() {
    return (rightNode != nullptr);
}

bool CFGNode::areThereEdges() {
    return !(leftNode == nullptr && rightNode == nullptr);
}

CFGNodePtr CFGNode::getLeftNode() {
    return leftNode;
}

CFGNodePtr CFGNode::getRightNode() {
    return rightNode;
}

void CFGNode::setLeftNode(CFGNodePtr newLeftNode) {
    this->leftNode = std::move(newLeftNode);
}

void CFGNode::setRightNode(CFGNodePtr newRightNode) {
    this->rightNode = std::move(newRightNode);
}
