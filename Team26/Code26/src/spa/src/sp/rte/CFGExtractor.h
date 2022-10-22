
#ifndef SPA_CFGEXTRACTOR_H
#define SPA_CFGEXTRACTOR_H

#include "util/cfg/CFGHead.h"
#include "pkb/PKBInterface.h"

class CFGExtractor {
private:
    bool toExclude(PKBInterface* pkb, STMT_NUM stmt, std::string varModified);
public:
    std::unordered_set<STMT_NUM> getReachableNodes(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt, std::string varModified);
};


#endif //SPA_CFGEXTRACTOR_H
