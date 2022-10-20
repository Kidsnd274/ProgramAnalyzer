#include "NextExtractor.h"

std::unordered_set<STMT_NUM> NextExtractor::getStatementRelations(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt) {
    return cfg->getNextNodes(stmt);
}

bool NextExtractor::isTransitiveComputed(PKBInterface* pkb, STMT_NUM stmt) {
    //return pkb->isNextStarComputed(stmt);
    return false; //placeholder until method has been implemented in pkb
}

void NextExtractor::addTransitive(PKBInterface* pkb, STMT_NUM toAddTo, STMT_NUM toAddFrom) {
    //pkb->addAllNextStar(toAddTo, toAddFrom);
}