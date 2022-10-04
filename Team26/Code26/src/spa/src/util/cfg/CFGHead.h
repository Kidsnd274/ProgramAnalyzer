#ifndef SPA_CFGHEAD_H
#define SPA_CFGHEAD_H

#include "CFGNode.h"
#include <vector>

class CFGHead;

typedef std::shared_ptr<CFGHead> CFGHeadPtr;

class CFGHead {
private:
    CFGNodePtr headNode;
    std::vector<CFGNodePtr> nodeArray;
    int currentStatementNumber = 1;
public:
    CFGHead(CFGNodePtr headNode) {
        this->headNode = headNode;
        nodeArray[0] = headNode;
    }

    void addCFGNode(CFGNodePtr newNode);
    CFGNodePtr getCFGNode(int statementNumber);
    CFGNodePtr getHead();
};

#endif //SPA_CFGHEAD_H
