#ifndef SPA_RUNTIMEEXTRACTOR_H
#define SPA_RUNTIMEEXTRACTOR_H

#include "NextExtractor.h"
#include <stack>

class RuntimeExtractor {
private:
    NextExtractor nextExtractor;
    PKBInterface* pkb;
    std::unordered_map<STMT_NUM, std::vector<STMT_NUM>> addAfterMap;
public:
    RuntimeExtractor(PKBInterface* pkbInterface) {
        pkb = pkbInterface;
    }
    void computeNextStar(CFGHeadPtr cfg, STMT_NUM stmt);
    void computeTransitive(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt, CFGExtractor& extractor,
                           std::unordered_set<STMT_NUM>& visited, std::vector<STMT_NUM>& stmtStack);
    void addAfterTransitiveComputation(CFGExtractor& extractor);
};


#endif //SPA_RUNTIMEEXTRACTOR_H
