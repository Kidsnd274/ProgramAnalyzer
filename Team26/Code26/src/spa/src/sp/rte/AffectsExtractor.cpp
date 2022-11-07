#include "AffectsExtractor.h"

void AffectsExtractor::computeAffects(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt) {
    if (pkb->hasRelation(RelationType::AFFECTS, stmt)) {
        return;
    }

    std::string varModified = pkb->getModifiedVariable(stmt);
    std::unordered_set<STMT_NUM> affectedSet = getReachableNodes(std::move(cfg), pkb, stmt, varModified);

    for (auto i : affectedSet) {
        if (pkb->isStatementType(StatementType::ASSIGN, i)
            && pkb->doesStatementUseOrModify(RelationType::USES_S, i, varModified)) {
            pkb->addRelation(RelationType::AFFECTS, stmt, i);
        }
    }
}

void AffectsExtractor::computeDDG(std::string& procName, const CFGHeadPtr& cfg, PKBInterface *pkb) {
    std::unordered_set<STMT_NUM> assignSet = pkb->getAllAssignFromProcedure(procName);
    for (auto stmt : assignSet) {
        if (!pkb->hasRelation(RelationType::AFFECTS, stmt)) {
            computeAffects(cfg, pkb, stmt);
        }

        std::unordered_set<STMT_NUM> affectedSet = pkb->getAffects(stmt);
        addEdgesToDDG(procName, stmt, affectedSet);
    }
}

void AffectsExtractor::addEdgesToDDG(std::string& procName, STMT_NUM stmt, std::unordered_set<STMT_NUM>& affectedSet) {
    for (auto affected : affectedSet) {
        procToDDG[procName][stmt].push_back(affected);
    }
}

void AffectsExtractor::computeAffectsStar(const CFGHeadPtr& cfg, PKBInterface *pkb, STMT_NUM stmt) {
    if (pkb->hasRelation(RelationType::AFFECTS_T, stmt)) {
        return;
    }

    std::string procName = pkb->getProcedureNameOf(cfg);

    if (procToDDG.find(procName) == procToDDG.end()) {
        computeDDG(procName, cfg, pkb);
    }
    std::unordered_set<STMT_NUM> visited;
    dfsOnNeighbours(procName, stmt, visited);
    pkb->addRelation(RelationType::AFFECTS_T, stmt, visited);
}

void AffectsExtractor::dfs(std::string& procName, STMT_NUM stmt, std::unordered_set<STMT_NUM>& visited) {
    if (visited.find(stmt) != visited.end()) {
        return;
    }

    visited.insert(stmt);

    dfsOnNeighbours(procName, stmt, visited);
}

void AffectsExtractor::dfsOnNeighbours(std::string& procName, STMT_NUM stmt, std::unordered_set<STMT_NUM>& visited) {
    for (auto i : procToDDG[procName][stmt]) {
        if (visited.find(i) == visited.end()) {
            dfs(procName, i, visited);
        }
    }
}

void AffectsExtractor::clearCache() {
    procToDDG.clear();
}
