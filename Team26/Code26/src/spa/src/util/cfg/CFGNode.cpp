#include "CFGNode.h"

int CFGNode::getStmtNumber() const {
    return statementNumber;
}

CFGNodeType CFGNode::getNodeType() const {
    return nodeType;
}

bool CFGNode::isDummyNode() {
    return nodeType == CFGNodeType::DummyNode;
}

CFGNode CFGNode::node(int statementNumber) {
    return {statementNumber, CFGNodeType::NormalNode};
}

CFGNode CFGNode::dummyNode(int statementNumber) {
    return {statementNumber, CFGNodeType::DummyNode};
}

bool CFGNode::isNullNode() {
    return nodeType == CFGNodeType::NullNode;
}

bool CFGNode::isNormalNode() {
    return nodeType == CFGNodeType::NormalNode;
}

bool operator== (CFGNode leftNode, CFGNode rightNode) {
    bool cond1 = leftNode.getStmtNumber() == rightNode.getStmtNumber();
    bool cond2 = leftNode.getNodeType() == rightNode.getNodeType();
    return (cond1 && cond2);
}

bool operator!= (CFGNode leftNode, CFGNode rightNode) {
    return !(leftNode == rightNode);
}

bool operator< (CFGNode leftNode, CFGNode rightNode) {
    if (leftNode.getStmtNumber() == rightNode.getStmtNumber()) {
        if (leftNode.getNodeType() == rightNode.getNodeType()) {
            return true;
        }
        return leftNode.getNodeType() < rightNode.getNodeType();
    }

    return leftNode.getStmtNumber() < rightNode.getStmtNumber();
}
