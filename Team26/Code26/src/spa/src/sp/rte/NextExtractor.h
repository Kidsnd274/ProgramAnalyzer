
#ifndef SPA_NEXTEXTRACTOR_H
#define SPA_NEXTEXTRACTOR_H

#include "CFGExtractor.h"

class NextExtractor : public CFGExtractor {
    std::unordered_set<STMT_NUM> getStatementRelations(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt);
    bool isTransitiveComputed(PKBInterface* pkb, STMT_NUM stmt);
    void addTransitive(PKBInterface* pkb, STMT_NUM toAddTo, STMT_NUM toAddFrom);
};


#endif //SPA_NEXTEXTRACTOR_H
