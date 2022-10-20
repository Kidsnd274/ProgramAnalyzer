#include "NextExtractor.h"

std::unordered_set<STMT_NUM> NextExtractor::getStatementRelations(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt) {
    return cfg->getNextNodes(stmt);
}

bool isTransitiveComputed(PKBInterface* pkb, STMT_NUM stmt) {
    //return pkb->isNextStarComputed(stmt);
    return false; //placeholder until method has been implemented in pkb
}