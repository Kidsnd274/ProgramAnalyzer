
#include "AffectsExtractor.h"

void AffectsExtractor::computeAffects(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt) {
    if(pkb->hasAffects(stmt)) {
        return;
    }

    string varModified = pkb->getModifiedVariable(stmt);
    std::unordered_set<STMT_NUM> affectedSet = getReachableNodes(std::move(cfg), pkb, stmt, varModified);
//    for(auto i : affectedSet) {
//        if(pkb->isStatementAssign(i) && pkb->doesStatementUse(i, varModified)) {
//            pkb->addAffects(stmt, i);
//        }
//    }
}