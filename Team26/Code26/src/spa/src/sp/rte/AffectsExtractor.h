
#ifndef SPA_AFFECTSEXTRACTOR_H
#define SPA_AFFECTSEXTRACTOR_H

#include "util/cfg/CFGHead.h"
#include "pkb/PKBInterface.h"

class AffectsExtractor {
public:
    bool isAffects(CFGHeadPtr cfg, STMT_NUM stmt1, STMT_NUM stmt2);
    void computeAffects(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt);
    void computeAffectsStar(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt);
};


#endif //SPA_AFFECTSEXTRACTOR_H