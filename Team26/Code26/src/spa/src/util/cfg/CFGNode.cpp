#include "CFGNode.h"

#include <utility>

int CFGNode::getStmtNumber() const {
    return statementNumber;
}

CFGNodeType CFGNode::getNodeType() {
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
