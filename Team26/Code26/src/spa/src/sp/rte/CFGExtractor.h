#ifndef SPA_CFGEXTRACTOR_H
#define SPA_CFGEXTRACTOR_H

#include "util/cfg/CFGHead.h"
#include "pkb/PKBInterface.h"

class CFGExtractor {
public:
    virtual std::unordered_set<STMT_NUM> getStatementRelations(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt) = 0;
    virtual bool isTransitiveComputed(PKBInterface* pkb, STMT_NUM stmt) = 0;
    virtual void addTransitiveFrom(PKBInterface* pkb, STMT_NUM toAddTo, STMT_NUM toAddFrom) = 0;
    virtual void addToTransitive(PKBInterface* pkb, STMT_NUM toAddTo, std::unordered_set<STMT_NUM>& toBeAdded) = 0;
};


#endif //SPA_CFGEXTRACTOR_H
