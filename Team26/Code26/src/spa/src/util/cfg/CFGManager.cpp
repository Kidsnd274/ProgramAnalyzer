#include "CFGManager.h"

void CFGManager::createNewCFG() {
    currentCFG = CFGHead::createNewCFG();
}

CFGHeadPtr CFGManager::getCurrentCFG() {
    return currentCFG;
}

void CFGManager::addStandardNode(STMT_NUM stmtNum) {
    CFGNode newNode = CFGNode::newNode(stmtNum);
    if (!parentNode.isNullNode()) {
        currentCFG->connectNode(parentNode, newNode);
    }
    parentNode = newNode;
}

void CFGManager::addDummyNode(STMT_NUM stmtNum) {
    CFGNode newNode = CFGNode::newDummyNode(stmtNum);
    if (!parentNode.isNullNode()) { // DummyNode stmt number should refer to the if stmt number
        currentCFG->connectNode(parentNode, newNode);
    }
    parentNode = newNode;
}

void CFGManager::setParentNode(CFGNode newParentNode) {
    this->parentNode = newParentNode;
}

void CFGManager::finalizeIfPortionOfStatement(STMT_NUM ifNode) {
    addDummyNode(ifNode);
    setParentNode(CFGNode::newNode(ifNode));
}



void CFGManager::finalizeWhileStatement(STMT_NUM whileNode) {
    currentCFG->connectNode(parentNode, CFGNode::newNode(whileNode));
    setParentNode(parentNode);
    addDummyNode(whileNode);
}
