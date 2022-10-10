#include "CFGHead.h"
#include "StatementNumberNotFoundException.h"
#include <utility>

void CFGHead::connectNode(CFGNode node1, CFGNode node2)  {
    STMT_NUM stmtNum = node1.getStmtNumber();
    if (node1.isDummyNode()) {
        dummyAdjList.insert({stmtNum, node2});
    } else {
        if (adjList.find(stmtNum) == adjList.end()) { // If key doesn't exist
            adjList[stmtNum] = EDGES(); // Initialize key with null vector
        }
        adjList[stmtNum].push_back(node2);
    }
}

EDGES CFGHead::getEdges(STMT_NUM stmtNumber) {
    if (adjList.find(stmtNumber) == adjList.end()) {
        throw StatementNumberNotFoundException();
    }
    return adjList.at(stmtNumber);
}

CFGNode CFGHead::getDummyNodeEdge(STMT_NUM stmtNumber) {
    if (dummyAdjList.find(stmtNumber) == dummyAdjList.end()) {
        throw StatementNumberNotFoundException();
    }
    return dummyAdjList.at(stmtNumber);
}

CFGHeadPtr CFGHead::createNewCFG() {
    return std::make_shared<CFGHead>();
}

CFGMap CFGHead::getNormalNodeMap() {
    return this->adjList;
}

CFGDummyMap CFGHead::getDummyNodeMap() {
    return this->dummyAdjList;
}

STMT_NUM CFGHead::findDummyNodeNext(CFGNode& dummy) {
    return dummyAdjList[dummy.getStmtNumber()].getStmtNumber();
}

bool CFGHead::isStatementInCFG(STMT_NUM stmt1) {
    return adjList.find(stmt1) != adjList.end();
}

bool CFGHead::isNext(STMT_NUM stmt1, STMT_NUM stmt2) {
    if(!isStatementInCFG(stmt1) || !isStatementInCFG(stmt2)) {
        return false;
    }

    bool ans = false;
    for(auto &node : adjList[stmt1]) {
        if(node.isDummyNode()) {
            ans = ans || (findDummyNodeNext(node) == stmt2);
        } else {
            ans = ans || (node.getStmtNumber() == stmt2);
        }
    }

    return ans;
}

bool CFGHead::compareEdgesEquality(EDGES v1, EDGES v2) {
    if (v1.size() != v2.size()) {
        return false;
    }
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    return v1 == v2;
}

bool operator== (CFGHead leftCFG, CFGHead rightCFG) {
    auto leftNodeMap = leftCFG.getNormalNodeMap();
    auto rightNodeMap = rightCFG.getNormalNodeMap();

    std::unordered_set<STMT_NUM> verifiedNodes;
    // Check that keys in the left CFG is equal to the right CFG
    for (auto iter = leftNodeMap.begin(); iter != leftNodeMap.end(); ++iter) {
        STMT_NUM key = iter->first;
        if (verifiedNodes.find(key) != verifiedNodes.end()) {
            continue;
        }
        if (rightNodeMap.find(key) == rightNodeMap.end()) { // If key not found in right map
            return false;
        }
        // Key found, comparing edges
        EDGES leftEdges = leftNodeMap.at(key);
        EDGES rightEdges = rightNodeMap.at(key);
        bool compareEdges = CFGHead::compareEdgesEquality(leftEdges, rightEdges);
        if (!compareEdges) {
            return false;
        }
        verifiedNodes.insert(key);
    }

    // Check that keys in the right CFG is equal to the left CFG (in case right CFG has keys that left doesn't)
    for (auto iter = rightNodeMap.begin(); iter != rightNodeMap.end(); ++iter) {
        STMT_NUM key = iter->first;
        if (verifiedNodes.find(key) != verifiedNodes.end()) {
            continue;
        }
        if (leftNodeMap.find(key) == leftNodeMap.end()) { // If key not found in left map
            return false;
        }
        // Key found comparing edges
        EDGES leftEdges = leftNodeMap.at(key);
        EDGES rightEdges = rightNodeMap.at(key);
        bool compareEdges = CFGHead::compareEdgesEquality(leftEdges, rightEdges);
        if (!compareEdges) {
            return false;
        }
        verifiedNodes.insert(key);
    }

    // Compare Dummy Nodes
    return leftCFG.getDummyNodeMap() == rightCFG.getDummyNodeMap();
}

bool operator!= (CFGHead leftCFG, CFGHead rightCFG) {
    return !(std::move(leftCFG) == std::move(rightCFG));
}