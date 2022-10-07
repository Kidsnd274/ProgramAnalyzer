#include "CFGHead.h"

#include <utility>

void CFGHead::connectNode(CFGNode node1, CFGNode node2)  {
    if (node1.isDummyNode()) {
        dummyAdjList.insert({node1.getStmtNumber(), node2});
    } else {
        adjList.insert({node1.getStmtNumber(), node2});
    }
}

EDGES CFGHead::getEdges(STMT_NUM stmtNumber) {
    if (adjList.find(stmtNumber) == adjList.end()) {
        return {};
    }
    EDGES result;
    auto variables = this->adjList.equal_range(stmtNumber);

    for (auto it = variables.first; it != variables.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

EDGES CFGHead::getDummyNodeEdges(STMT_NUM stmtNumber) {
    if (dummyAdjList.find(stmtNumber) == dummyAdjList.end()) {
        return {};
    }
    EDGES result;
    auto variables = this->dummyAdjList.equal_range(stmtNumber);

    for (auto it = variables.first; it != variables.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

CFGHeadPtr CFGHead::createNewCFG() {
    return std::make_shared<CFGHead>();
}

CFGMap CFGHead::getNormalNodeMap() {
    return this->adjList;
}

CFGMap CFGHead::getDummyNodeMap() {
    return this->dummyAdjList;
}

bool operator== (CFGHead leftCFG, CFGHead rightCFG) {
    bool cond1 = leftCFG.getNormalNodeMap() == rightCFG.getNormalNodeMap();
    bool cond2 = leftCFG.getDummyNodeMap() == rightCFG.getDummyNodeMap();
    return cond1 && cond2;
}

bool operator!= (CFGHead leftCFG, CFGHead rightCFG) {
    return !(std::move(leftCFG) == std::move(rightCFG));
}