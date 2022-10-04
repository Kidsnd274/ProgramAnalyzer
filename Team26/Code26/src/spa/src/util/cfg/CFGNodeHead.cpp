#include "CFGNodeHead.h"

void CFGNodeHead::addCFGNode(CFGNodePtr newNode) {
    nodeArray[currentStatementNumber - 1] = newNode;
}

CFGNodePtr CFGNodeHead::getCFGNode(int statementNumber) {
    return nodeArray[statementNumber - 1];
}

CFGNodePtr CFGNodeHead::getHead() {
    return headNode;
}
