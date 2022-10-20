#ifndef SPA_CFGEXTRACTOR_H
#define SPA_CFGEXTRACTOR_H

#include "util/cfg/CFGHead.h"
#include "pkb/PKBInterface.h"

class CFGExtractor {
public:
    virtual std::unordered_set<STMT_NUM> getStatementRelations(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt) = 0;
    virtual bool isTransitiveComputed(PKBInterface* pkb, STMT_NUM stmt) = 0;
};


#endif //SPA_CFGEXTRACTOR_H
