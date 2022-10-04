#ifndef SPA_CFGHEAD_H
#define SPA_CFGHEAD_H

#include "CFGNode.h"
#include <vector>

class CFGHead; // Forward declaration

typedef std::shared_ptr<CFGHead> CFGHeadPtr;

class CFGHead {
private:
    CFGNodePtr headNode;
    std::vector<CFGNodePtr> nodeArray;
    int nextStatementNumber = 1;
    bool initialized = false;
public:
    void addCFGNode(CFGNodePtr newNode);
    CFGNodePtr getCFGNode(int statementNumber);
    CFGNodePtr getHead();
    int getNextStatementNumber();
    static CFGHeadPtr createNewNodeHead();
};



#endif //SPA_CFGHEAD_H
