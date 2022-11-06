#include "CFGExtractor.h"

bool CFGExtractor::toExclude(PKBInterface* pkb, STMT_NUM stmt, std::string varModified) {
    if (varModified == "") {
        return false;
    }

    // if statement is if or while we do not want to exclude it
    if (pkb->isStatementContainer(stmt)) {
        return false;
    }

    return pkb->doesStatementModify(stmt, varModified);
}

std::unordered_set<STMT_NUM> CFGExtractor::getReachableNodes(CFGHeadPtr cfg, PKBInterface* pkb, STMT_NUM stmt, std::string varModified) {
    if (!cfg->isStatementInCFG(stmt)) {
        return {};
    }

    std::unordered_set<int> ans;
    std::queue<int> q;

    for (auto node : cfg->getNextNodes(stmt)) {
        if (ans.find(node) == ans.end()) {
            q.push(node);
            ans.insert(node);
        }
    }

    while (!q.empty()) {
        STMT_NUM sm = q.front();
        q.pop();

        if (toExclude(pkb, sm, varModified)) {
            continue;
        }

        for (auto node :  cfg->getNextNodes(sm)) {
            if (ans.find(node) == ans.end()) {
                q.push(node);
                ans.insert(node);
            }
        }
    }
    return ans;
}
