#include "CFGHead.h"

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
        return {};
    }
    return adjList.at(stmtNumber);
}

CFGNode CFGHead::getDummyNodeEdge(STMT_NUM stmtNumber) {
    if (dummyAdjList.find(stmtNumber) == dummyAdjList.end()) {
        return {-1, CFGNodeType::NullNode};
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

bool CFGHead::compareEdgesEquality(EDGES &v1, EDGES &v2) {
    if (v1.size() != v2.size()) {
        return false;
    }
//    std::sort(v1.begin(), v1.end());
//    std::sort(v2.begin(), v2.end());
    return v1 == v2;
}

bool operator== (CFGHead leftCFG, CFGHead rightCFG) {
    std::unordered_set<STMT_NUM> verifiedNodes;

    auto leftNodeMap = leftCFG.getNormalNodeMap();
    auto rightNodeMap = rightCFG.getNormalNodeMap();

    // Check that items in left CFG is equal right CFG
    for (auto it = leftNodeMap.begin(); it != leftNodeMap.end();) {
        auto const& key = it->first;
        if (rightNodeMap.find(key) == rightNodeMap.end()) { // Key not found in right node
            return false;
        }
        EDGES leftEdges = leftNodeMap.at(key);
        EDGES rightEdges = rightNodeMap.at(key);
//        bool compareEdges = CFGHead::compareEdgesEquality(leftEdges, rightEdges);
//        if (!compareEdges) {
//            return false;
//        }
        verifiedNodes.insert(key);
        while (++it != leftNodeMap.end() && it->first == key);
    }

    // Check that items in the right CFG is equal left CFG (in case right has more)
    for (auto it = rightNodeMap.begin(); it != rightNodeMap.end();) {
        auto const& key = it->first;
        if (verifiedNodes.find(key) != verifiedNodes.end()) { // Verified stmt number already
            while (++it != leftNodeMap.end() && it->first == key);
            continue;
        }
        if (leftNodeMap.find(key) == leftNodeMap.end()) { // Key not found in right node
            return false;
        }
        EDGES leftEdges = leftNodeMap.at(key);
        EDGES rightEdges = rightNodeMap.at(key);
//        bool compareEdges = CFGHead::compareEdgesEquality(leftEdges, rightEdges);
//        if (!compareEdges) {
//            return false;
//        }
        while (++it != leftNodeMap.end() && it->first == key);
    }

    // Compare DummyNodes
//    bool cond2 = leftCFG.getDummyNodeMap() == rightCFG.getDummyNodeMap();
    return true;
}

bool operator!= (CFGHead leftCFG, CFGHead rightCFG) {
    return !(std::move(leftCFG) == std::move(rightCFG));
}