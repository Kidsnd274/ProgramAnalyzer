
#include "RuntimeExtractor.h"

bool RuntimeExtractor::isNext(CFGHeadPtr cfg, STMT_NUM stmt1, STMT_NUM stmt2) {
    return nextExtractor.isNext(std::move(cfg), stmt1, stmt2);
}

void RuntimeExtractor::computeNextStar(CFGHeadPtr cfg, STMT_NUM stmt) {
    nextExtractor.computeNextStar(std::move(cfg), pkbInterface, stmt);
}

std::unordered_set<STMT_NUM> RuntimeExtractor::getNextNodes(CFGHeadPtr cfg, STMT_NUM stmt1) {
    return nextExtractor.getNextNodes(std::move(cfg), stmt1);
}

void RuntimeExtractor::computeAffects(CFGHeadPtr cfg, STMT_NUM stmt) {
    affectsExtractor.computeAffects(std::move(cfg), pkbInterface, stmt);
}

void RuntimeExtractor::computeAffectsStar(const CFGHeadPtr& cfg, STMT_NUM stmt) {
    affectsExtractor.computeAffectsStar(cfg, pkbInterface, stmt);
}

void RuntimeExtractor::clearCache() {
    pkbInterface->clear();
    affectsExtractor.clearCache();
}