#ifndef SPA_CFGMANAGER_H
#define SPA_CFGMANAGER_H

#include "CFGHead.h"
#include "CFGStandardNodeGenerator.h"
#include "CFGIfNodeGenerator.h"
#include "CFGWhileNodeGenerator.h"

class CFGManager {
private:
    CFGHeadPtr currentCFG;
    CFGNodeGeneratorPtr currentGenerator;
public:
    void createNewCFG();
    CFGHeadPtr getCFG();
    void addNode(int statementNumber);
    // If generator functions
    void addIfNode();
    void finalizeIfPortion();

};

#endif //SPA_CFGMANAGER_H
