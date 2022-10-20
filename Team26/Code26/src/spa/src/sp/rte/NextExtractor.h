
#ifndef SPA_NEXTEXTRACTOR_H
#define SPA_NEXTEXTRACTOR_H

#include "CFGExtractor.h"

class NextExtractor : public CFGExtractor {
    std::unordered_set<STMT_NUM> getStatementRelations(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt);
    bool isTransitiveComputed(PKBInterface* pkb, STMT_NUM stmt);
    void addTransitiveFrom(PKBInterface* pkb, STMT_NUM toAddTo, STMT_NUM toAddFrom);
    void addToTransitive(PKBInterface* pkb, STMT_NUM toAddTo, std::unordered_set<STMT_NUM>& toBeAdded);
    void markTransitiveComputed(PKBInterface* pkb, STMT_NUM toMark);
};


#endif //SPA_NEXTEXTRACTOR_H
