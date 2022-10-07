#include "CFGManager.h"

void CFGManager::createNewCFG() {
    currentCFG = CFGHead::createNewCFG();
    parentNode = {-1, CFGNodeType::NullNode};
}

CFGHeadPtr CFGManager::getCurrentCFG() {
    return currentCFG;
}

void CFGManager::addStandardNode(STMT_NUM stmtNum) {
    CFGNode newNode = CFGNode::node(stmtNum);
    if (!parentNode.isNullNode()) {
        currentCFG->connectNode(parentNode, newNode);
    }
    parentNode = newNode;
}

void CFGManager::addDummyNode(STMT_NUM stmtNum) {
    CFGNode newNode = CFGNode::dummyNode(stmtNum);
    if (!parentNode.isNullNode()) { // DummyNode stmt number should refer to the if stmt number
        currentCFG->connectNode(parentNode, newNode);
    }
    parentNode = newNode;
}

void CFGManager::setParentNode(CFGNode newParentNode) {
    this->parentNode = newParentNode;
}

void CFGManager::finalizeIfPortionOfIfStatement(STMT_NUM ifNode) {
    addDummyNode(ifNode);
    setParentNode(CFGNode::node(ifNode));
}



void CFGManager::finalizeWhileStatement(STMT_NUM whileNode) {
    currentCFG->connectNode(parentNode, CFGNode::node(whileNode));
    setParentNode(CFGNode::node(whileNode));
    addDummyNode(whileNode);
}

void CFGManager::finalizeElsePortionOfIfStatement(STMT_NUM ifNode) {
    addDummyNode(ifNode);
}
