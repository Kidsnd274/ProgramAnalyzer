
#ifndef SPA_RUNTIMEEXTRACTOR_H
#define SPA_RUNTIMEEXTRACTOR_H

#include "pkb/PKBInterface.h"
#include "util/cfg/CFGHead.h"

class RuntimeExtractor {
private:
    PKBInterface* pkbInterface;
    CFGHeadPtr cfg;

public:
    RuntimeExtractor(PKBInterface* pkb, CFGHeadPtr cfgPtr) {
        pkbInterface = pkb;
        cfg = cfgPtr;
    }

    ~RuntimeExtractor() {
        pkbInterface = nullptr;
    }
};


#endif //SPA_RUNTIMEEXTRACTOR_H
