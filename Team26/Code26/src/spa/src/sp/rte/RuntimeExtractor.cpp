#include "RuntimeExtractor.h"

void RuntimeExtractor::computeTransitive(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt, CFGExtractor& extractor) {
    if(extractor.isTransitiveComputed(pkb, stmt)) {
        return;
    }

    std::unordered_set<STMT_NUM> currSet = extractor.getStatementRelations(cfg, pkb, stmt);

    for(auto related : currSet) {
        computeTransitive(cfg, pkb, related, extractor);
        extractor.addTransitive(pkb, stmt, related);
    }

    return;
}

void RuntimeExtractor::computeNextStar(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt) {
    computeTransitive(cfg, pkb, stmt, nextExtractor);
}