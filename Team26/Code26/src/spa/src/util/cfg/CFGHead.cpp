#include "CFGHead.h"

void CFGHead::connectNode(CFGNode node1, CFGNode node2)  {
    if (node1.isDummyNode()) {
        dummyAdjList[node1.getStmtNumber()].push_back(node2);
    } else {
        adjList[node1.getStmtNumber()].push_back(node2);
    }
}

EDGES CFGHead::getEdges(STMT_NUM stmtNumber) {
    if (adjList.find(stmtNumber) == adjList.end()) {
        return {};
    }
    return adjList[stmtNumber];
}

EDGES CFGHead::getDummyNodeEdges(STMT_NUM stmtNumber) {
    if (dummyAdjList.find(stmtNumber) == dummyAdjList.end()) {
        return {};
    }
    return dummyAdjList[stmtNumber];
}

CFGHeadPtr CFGHead::createNewCFG() {
    return std::make_shared<CFGHead>();
}
