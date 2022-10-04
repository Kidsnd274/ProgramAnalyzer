#include "CFGHead.h"

void CFGHead::addCFGNode(CFGNodePtr newNode) {
    nodeArray[currentStatementNumber - 1] = newNode;
}

CFGNodePtr CFGHead::getCFGNode(int statementNumber) {
    return nodeArray[statementNumber - 1];
}

CFGNodePtr CFGHead::getHead() {
    return headNode;
}
