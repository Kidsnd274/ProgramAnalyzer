#ifndef SPA_CFGNODEHEAD_H
#define SPA_CFGNODEHEAD_H

#include "CFGNode.h"
#include <vector>

class CFGNodeHead {
private:
    CFGNodePtr headNode;
    std::vector<CFGNodePtr> nodeArray;
    int currentStatementNumber = 1;
public:
    CFGNodeHead(CFGNodePtr headNode) {
        this->headNode = headNode;
        nodeArray[0] = headNode;
    }

    void addCFGNode(CFGNodePtr newNode);
    CFGNodePtr getCFGNode(int statementNumber);
    CFGNodePtr getHead();
};

#endif //SPA_CFGNODEHEAD_H
