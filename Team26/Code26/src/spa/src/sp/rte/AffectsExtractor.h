
#ifndef SPA_AFFECTSEXTRACTOR_H
#define SPA_AFFECTSEXTRACTOR_H

#include "CFGExtractor.h"

typedef std::unordered_map<STMT_NUM, std::vector<STMT_NUM>> DDG;

class AffectsExtractor : public CFGExtractor {
private:
    std::unordered_map<std::string, DDG> procToDDG;
    void computeDDG(std::string procName, CFGHeadPtr cfg, PKBInterface* pkb);
    void addEdgesToDDG(std::string procName, STMT_NUM stmt, std::unordered_set<STMT_NUM>& affectedSet);
    void dfs(std::string procName, STMT_NUM stmt, std::unordered_set<STMT_NUM>& visited);
public:
    void computeAffects(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt);
    void computeAffectsStar(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt);
};


#endif //SPA_AFFECTSEXTRACTOR_H
