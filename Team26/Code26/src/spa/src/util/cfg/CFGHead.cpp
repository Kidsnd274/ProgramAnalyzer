#include "CFGHead.h"

void CFGHead::addCFGNode(CFGNodePtr newNode) {
    if (!initialized) {
        headNode = newNode;
        initialized = true;
    }
    nodeArray[nextStatementNumber++ - 1] = newNode;
}

CFGNodePtr CFGHead::getCFGNode(int statementNumber) {
    return nodeArray[statementNumber - 1];
}

CFGNodePtr CFGHead::getHead() {
    return headNode;
}

int CFGHead::getNextStatementNumber() {
    return nextStatementNumber;
}

CFGHeadPtr CFGHead::createNewNodeHead() {
    return std::make_shared<CFGHead>();
}


