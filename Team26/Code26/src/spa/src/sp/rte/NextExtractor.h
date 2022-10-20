
#ifndef SPA_NEXTEXTRACTOR_H
#define SPA_NEXTEXTRACTOR_H

#include "RuntimeExtractor.h"

class NextExtractor : public RuntimeExtractor {
    std::unordered_set<STMT_NUM> getStatementRelations(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt);
};


#endif //SPA_NEXTEXTRACTOR_H
