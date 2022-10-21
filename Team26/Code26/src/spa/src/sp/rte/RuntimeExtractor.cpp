
#include "RuntimeExtractor.h"

bool RuntimeExtractor::isNext(CFGHeadPtr cfg, STMT_NUM stmt1, STMT_NUM stmt2) {
    return nextExtractor.isNext(cfg, stmt1, stmt2);
}

void RuntimeExtractor::computeNextStar(CFGHeadPtr cfg, STMT_NUM stmt) {
    nextExtractor.computeNextStar(cfg, pkbInterface, stmt);
}

std::unordered_set<STMT_NUM> RuntimeExtractor::getNextNodes(CFGHeadPtr cfg, STMT_NUM stmt1) {
    return nextExtractor.getNextNodes(cfg, stmt1);
}