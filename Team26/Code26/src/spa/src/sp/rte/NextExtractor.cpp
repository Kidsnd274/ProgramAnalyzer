#include "NextExtractor.h"

bool NextExtractor::isNext(CFGHeadPtr cfg, STMT_NUM stmt1, STMT_NUM stmt2) {
    return cfg->isNext(stmt1, stmt2);
}

std::unordered_set<STMT_NUM> NextExtractor::getNextNodes(CFGHeadPtr cfg, STMT_NUM stmt1) {
    return cfg->getNextNodes(stmt1);
}

void NextExtractor::computeNextStar(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt) {
    if (pkb->hasNextStar(stmt)) {
        return;
    }
    pkb->addNextStar(stmt, getReachableNodes(std::move(cfg), pkb, stmt, ""));
}
