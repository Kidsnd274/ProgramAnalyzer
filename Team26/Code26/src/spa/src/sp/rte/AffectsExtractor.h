
#ifndef SPA_AFFECTSEXTRACTOR_H
#define SPA_AFFECTSEXTRACTOR_H

#include "CFGExtractor.h"

class AffectsExtractor : public CFGExtractor {
public:
    void computeAffects(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt);
    void computeAffectsStar(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt);
};


#endif //SPA_AFFECTSEXTRACTOR_H
