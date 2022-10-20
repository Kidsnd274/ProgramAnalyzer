#include "RuntimeExtractor.h"

void RuntimeExtractor::computeTransitive(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt, CFGExtractor& extractor,
                                         std::unordered_set<STMT_NUM>& visited, std::vector<STMT_NUM>& stmtStack) {
    if(extractor.isTransitiveComputed(pkb, stmt)) {
        return;
    }

    if(visited.find(stmt) != visited.end()) {
        addAfterMap[stmt] = stmtStack;
        return;
    }

    visited.insert(stmt);
    stmtStack.push_back(stmt);

    std::unordered_set<STMT_NUM> currSet = extractor.getStatementRelations(cfg, pkb, stmt);

    for(auto related : currSet) {
        computeTransitive(cfg, pkb, related, extractor, visited, stmtStack);
        extractor.addTransitiveFrom(pkb, stmt, related);
    }
    extractor.addToTransitive(pkb, stmt, currSet);
    extractor.markTransitiveComputed(pkb, stmt);
    stmtStack.pop_back();

    return;
}

void RuntimeExtractor::addAfterTransitiveComputation(CFGExtractor& extractor) {
    //std::cout << "in Add after" << to_string(addAfterMap.size()) <<std::endl;
    for(auto &[f,s] : addAfterMap) {
        //std::cout << "in Add after" <<std::endl;
        for(auto i : s){
            extractor.addTransitiveFrom(pkb, i, f);
        }
    }
}

void RuntimeExtractor::computeNextStar(CFGHeadPtr cfg, STMT_NUM stmt) {
    std::unordered_set<STMT_NUM> visited;
    std::vector<STMT_NUM> stmtStack;
    computeTransitive(cfg, pkb, stmt, nextExtractor, visited, stmtStack);
    addAfterTransitiveComputation(nextExtractor);
}