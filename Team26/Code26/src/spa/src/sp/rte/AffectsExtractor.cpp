
#include "AffectsExtractor.h"

void AffectsExtractor::computeAffects(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt) {
    if(pkb->hasAffects(stmt)) {
        return;
    }

    string varModified = pkb->getModifiedVariable(stmt);
    std::unordered_set<STMT_NUM> affectedSet = getReachableNodes(std::move(cfg), pkb, stmt, varModified);

    for(auto i : affectedSet) {
        if(pkb->isStatementAssign(i) && pkb->doesStatementUse(i, varModified)) {
            pkb->addAffects(stmt, i);
        }
    }
}

void AffectsExtractor::computeDDG(std::string& procName, CFGHeadPtr cfg, PKBInterface *pkb) {
    std::unordered_set<STMT_NUM> assignSet = pkb->getAllAssignFromProcedure(procName);
    for(auto stmt : assignSet) {
        if(!pkb->hasAffects(stmt)) {
            computeAffects(std::move(cfg), pkb, stmt);
        }

        std::unordered_set<STMT_NUM> affectedSet = pkb->getAffects(stmt);
        addEdgesToDDG(procName, stmt, affectedSet);
    }
}

void AffectsExtractor::addEdgesToDDG(std::string& procName, STMT_NUM stmt, std::unordered_set<STMT_NUM>& affectedSet) {
    for(auto affected : affectedSet) {
        procToDDG[procName][stmt].push_back(affected);
    }
}

void AffectsExtractor::computeAffectsStar(CFGHeadPtr cfg, PKBInterface *pkb, STMT_NUM stmt) {
    if(pkb->hasAffectsStar(stmt)) {
        return;
    }

    std::string procName = pkb->getProcedureNameOf(std::move(cfg));
    if(procToDDG.find(procName) != procToDDG.end()) {
        computeDDG(procName, std::move(cfg), pkb);
    }
    std::unordered_set<STMT_NUM> visited;
    dfsOnNeighbours(procName, stmt, visited);
    pkb->addAffectsStar(stmt, visited);
}

void AffectsExtractor::dfs(std::string& procName, STMT_NUM stmt, std::unordered_set<STMT_NUM>& visited) {
    if(visited.find(stmt) != visited.end()) {
        return;
    }

    visited.insert(stmt);

    dfsOnNeighbours(procName, stmt, visited);
}

void AffectsExtractor::dfsOnNeighbours(std::string& procName, STMT_NUM stmt, std::unordered_set<STMT_NUM>& visited) {
    for (auto i : procToDDG[procName][stmt]) {
        if(visited.find(i) == visited.end()) {
            dfs(procName, i, visited);
        }
    }
}