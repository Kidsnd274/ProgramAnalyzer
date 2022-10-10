#ifndef SPA_CFGMANAGER_H
#define SPA_CFGMANAGER_H

#include "CFGHead.h"

class CFGManager {
private:
    CFGHeadPtr currentCFG = CFGHead::createNewCFG();
    CFGNode parentNode = {-1, CFGNodeType::NullNode};
public:
    void createNewCFG(); // Also resets CFG
    CFGHeadPtr getCurrentCFG();
    void addStandardNode(STMT_NUM stmtNum);
    void addDummyNode(STMT_NUM stmtNum);
    void setParentNode(CFGNode parentNode);
    void finalizeIfPortionOfIfStatement(STMT_NUM ifNode);
    void finalizeElsePortionOfIfStatement(STMT_NUM ifNode);
    void finalizeWhileStatement(STMT_NUM whileNode);
};

#endif //SPA_CFGMANAGER_H
