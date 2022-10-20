#include "NextExtractor.h"

std::unordered_set<STMT_NUM> NextExtractor::getStatementRelations(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt) {
    return cfg->getNextNodes(stmt);
}

bool NextExtractor::isTransitiveComputed(PKBInterface* pkb, STMT_NUM stmt) {
    return pkb->isNextStarComputed(stmt);
}

void NextExtractor::addTransitiveFrom(PKBInterface* pkb, STMT_NUM toAddTo, STMT_NUM toAddFrom) {
    pkb->addAllNextStarFrom(toAddTo, toAddFrom);
}

void NextExtractor::addToTransitive(PKBInterface* pkb, STMT_NUM toAddTo, std::unordered_set<STMT_NUM>& toBeAdded) {
    pkb->addNextStar(toAddTo, toBeAdded);
}

void NextExtractor::markTransitiveComputed(PKBInterface* pkb, STMT_NUM toMark) {
    pkb->markNextStarDone(toMark);
}