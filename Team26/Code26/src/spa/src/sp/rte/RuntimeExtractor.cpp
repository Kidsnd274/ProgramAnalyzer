#include "RuntimeExtractor.h"

void RuntimeExtractor::computeTransitive(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt, CFGExtractor& extractor) {
    if(extractor.isTransitiveComputed(pkb, stmt)) {
        return;
    }

    std::unordered_set<STMT_NUM> currSet = extractor.getStatementRelations(cfg, pkb, stmt);
    extractor.addToTransitive(pkb, stmt, currSet);

    for(auto related : currSet) {
        computeTransitive(cfg, pkb, related, extractor);
        extractor.addTransitiveFrom(pkb, stmt, related);
    }

    return;
}

void RuntimeExtractor::computeNextStar(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt) {
    computeTransitive(cfg, pkb, stmt, nextExtractor);
}