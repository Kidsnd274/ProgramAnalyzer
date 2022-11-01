
#ifndef SPA_RUNTIMEEXTRACTOR_H
#define SPA_RUNTIMEEXTRACTOR_H

#include "pkb/PKBInterface.h"
#include "util/cfg/CFGHead.h"
#include "NextExtractor.h"
#include "AffectsExtractor.h"

class RuntimeExtractor {
private:
    PKBInterface* pkbInterface;
    NextExtractor nextExtractor;
    AffectsExtractor affectsExtractor;

public:
    explicit RuntimeExtractor(PKBInterface* pkb) {
        pkbInterface = pkb;
    }

    ~RuntimeExtractor() {
        pkbInterface = nullptr;
    }

    //Next relationships
    bool isNext(CFGHeadPtr cfg, STMT_NUM stmt1, STMT_NUM stmt2);
    void computeNextStar(CFGHeadPtr cfg, STMT_NUM stmt);
    std::unordered_set<STMT_NUM> getNextNodes(CFGHeadPtr cfg, STMT_NUM stmt1);

    //Affects relationships
    void computeAffects(CFGHeadPtr cfg, STMT_NUM stmt);
    void computeAffectsStar(const CFGHeadPtr& cfg, STMT_NUM stmt);

    void clearCache();
};


#endif //SPA_RUNTIMEEXTRACTOR_H
