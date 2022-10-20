#ifndef SPA_CFGLOGIC_H
#define SPA_CFGLOGIC_H

#include "pkb/PKBInterface.h"

class CFGLogic {
private:
    CFGHeadPtr cfg;
    PKBInterface* pkbInterface;
    CFGMap* adjList;
    CFGDummyMap* dummyAdjList;
public:
    CFGLogic(CFGHeadPtr cfg, PKBInterface* pkbInterface) {
        this->cfg = cfg;
        this->pkbInterface = pkbInterface;
        this->adjList = cfg->getAdjList();
        this->dummyAdjList = cfg->getDummyAdjList();
    }

    ~CFGLogic() {
        adjList = nullptr;
        dummyAdjList = nullptr;
        pkbInterface = nullptr;
    }

    bool isStatementInCFG(STMT_NUM stmt1);
};

#endif //SPA_CFGLOGIC_H
