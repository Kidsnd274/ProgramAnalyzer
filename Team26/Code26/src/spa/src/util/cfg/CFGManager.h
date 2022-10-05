#ifndef SPA_CFGMANAGER_H
#define SPA_CFGMANAGER_H

#include "CFGHead.h"

class CFGManager {
private:
    CFGHeadPtr currentCFG = nullptr;
    CFGNode parentNode;
    CFGNode previousNode;
public:
    void createNewCFG(); // Also resets CFG
    CFGHeadPtr getCurrentCFG();
    void addStandardNode(STMT_NUM stmtNum);
    void addDummyNode(STMT_NUM stmtNum);
    void setParentNode(CFGNode parentNode);
    void setPreviousNode(CFGNode PreviousNode);
    void finalizeIfStatement(CFGNode lastIfNode, CFGNode lastElseNode, CFGNode ifNode);
    void finalizeWhileStatement(CFGNode lastNode, CFGNode whileNode);
};

#endif //SPA_CFGMANAGER_H
