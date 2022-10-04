#include "CFGStandardNodeGenerator.h"

void CFGStandardNodeGenerator::addNode() {
    int nextStatementNumber = cfg->getNextStatementNumber();
    CFGNodePtr newNode = CFGNode::createNode(nextStatementNumber);
    if (previousNode != nullptr) {
        previousNode->setLeftNode(newNode);
    }
    cfg->addCFGNode(newNode);
    previousNode = newNode;
}

CFGNodeGenerator CFGStandardNodeGenerator::finalize() {
//    return CFGNodeGenerator::finalize();
}

CFGStandardNodeGeneratorPtr CFGStandardNodeGenerator::createGenerator(CFGHeadPtr cfg) {
    return std::make_shared<CFGStandardNodeGenerator>(cfg);
}
