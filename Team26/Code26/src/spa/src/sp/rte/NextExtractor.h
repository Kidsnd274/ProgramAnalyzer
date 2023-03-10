#ifndef SPA_NEXTEXTRACTOR_H
#define SPA_NEXTEXTRACTOR_H

#include <unordered_set>
#include <utility>
#include <string>
#include "CFGExtractor.h"

class NextExtractor : public CFGExtractor{
public:
    bool isNext(CFGHeadPtr cfg, STMT_NUM stmt1, STMT_NUM stmt2);
    std::unordered_set<STMT_NUM> getNextNodes(CFGHeadPtr cfg, STMT_NUM stmt1);
    void computeNextStar(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt);
};

#endif  // SPA_NEXTEXTRACTOR_H
