
#ifndef SPA_RUNTIMEEXTRACTOR_H
#define SPA_RUNTIMEEXTRACTOR_H

#include "pkb/PKBInterface.h"
#include "util/cfg/CFGHead.h"
#include "NextExtractor.h"

class RuntimeExtractor {
private:
    PKBInterface* pkbInterface;
    NextExtractor nextExtractor;

public:
    explicit RuntimeExtractor(PKBInterface* pkb) {
        pkbInterface = pkb;
    }

    ~RuntimeExtractor() {
        pkbInterface = nullptr;
    }

    bool isNext(CFGHeadPtr cfg, STMT_NUM stmt1, STMT_NUM stmt2);
    void computeNextStar(CFGHeadPtr cfg, STMT_NUM stmt);
    std::unordered_set<STMT_NUM> getNextNodes(CFGHeadPtr cfg, STMT_NUM stmt1);
};


#endif //SPA_RUNTIMEEXTRACTOR_H
