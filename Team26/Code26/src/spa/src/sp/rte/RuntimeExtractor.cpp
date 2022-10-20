#include "RuntimeExtractor.h"

void RuntimeExtractor::computeTransitive(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt, CFGExtractor& extractor, std::unordered_set<STMT_NUM>& visited) {
    if(extractor.isTransitiveComputed(pkb, stmt) || (visited.find(stmt) != visited.end())) {
        return;
    }

    visited.insert(stmt);

    std::unordered_set<STMT_NUM> currSet = extractor.getStatementRelations(cfg, pkb, stmt);
    extractor.addToTransitive(pkb, stmt, currSet);

    for(auto related : currSet) {
        computeTransitive(cfg, pkb, related, extractor, visited);
        extractor.addTransitiveFrom(pkb, stmt, related);
    }

    return;
}

void RuntimeExtractor::computeNextStar(CFGHeadPtr cfg, STMT_NUM stmt) {
    std::unordered_set<STMT_NUM> visited;
    computeTransitive(cfg, pkb, stmt, nextExtractor, visited);
}