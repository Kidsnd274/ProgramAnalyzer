#include "CFGNode.h"

#include <utility>

int CFGNode::getStmtNumber() const {
    return statementNumber;
}

CFGNodeType CFGNode::getNodeType() const {
    return nodeType;
}

bool CFGNode::isDummyNode() {
    return nodeType == CFGNodeType::DummyNode;
}

CFGNode CFGNode::newNode(int statementNumber) {
    return {statementNumber, CFGNodeType::NormalNode};
}

CFGNode CFGNode::newDummyNode(int statementNumber) {
    return {statementNumber, CFGNodeType::DummyNode};
}

bool operator== (CFGNode leftNode, CFGNode rightNode) {
    bool cond1 = leftNode.getStmtNumber() == rightNode.getStmtNumber();
    bool cond2 = leftNode.getNodeType() == rightNode.getNodeType();
    return (cond1 && cond2);
}

bool operator!= (CFGNode leftNode, CFGNode rightNode) {
    return !(leftNode == rightNode);
}
