#include "NextExtractor.h"

std::unordered_set<STMT_NUM> NextExtractor::getStatementRelations(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt) {
    return cfg->getNextNodes(stmt);
}