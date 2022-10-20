#ifndef SPA_RUNTIMEEXTRACTOR_H
#define SPA_RUNTIMEEXTRACTOR_H

#include "NextExtractor.h"

class RuntimeExtractor {
private:
    NextExtractor nextExtractor;
    PKBInterface* pkb;
public:
    RuntimeExtractor(PKBInterface* pkbInterface) {
        pkb = pkbInterface;
    }
    void computeNextStar(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt);
    void computeTransitive(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt, CFGExtractor& extractor);
};


#endif //SPA_RUNTIMEEXTRACTOR_H
