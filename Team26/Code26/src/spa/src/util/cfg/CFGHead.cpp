#include "CFGHead.h"
#include "StatementNumberNotFoundException.h"
#include <cassert>
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

CFGMap *CFGHead::getAdjList() {
    return &this->adjList;
}

CFGDummyMap *CFGHead::getDummyAdjList() {
    return &this->dummyAdjList;
}

STMT_NUM CFGHead::findDummyNodeNext(CFGNode& dummy) {
    CFGNode dummyPointsTo = dummyAdjList.at(dummy.getStmtNumber());
    if(dummyPointsTo.isNullNode()) {
        return -1;
    } else if(dummyPointsTo.isDummyNode()) {
        return findDummyNodeNext(dummyPointsTo);
    } else {
        return dummyPointsTo.getStmtNumber();
    }
}

bool CFGHead::hasNextStatement(STMT_NUM stmt) {
    if (!isStatementInCFG(stmt)) {
        return false;
    }

    bool ans = false;

    for(auto &node : adjList[stmt]) {
        if(node.isDummyNode()) {
            ans = ans || findDummyNodeNext(node) != -1;
        } else {
            ans = true;
        }
    }

    return ans;
}

std::unordered_set<STMT_NUM> CFGHead::getNextNodes(STMT_NUM stmt) {
    if (!isStatementInCFG(stmt)) {
        return {};
    }

    std::unordered_set<STMT_NUM> ans;

    for(auto &node : adjList[stmt]) {
        if(node.isDummyNode()) {
            int nextNode = findDummyNodeNext(node);
            if(nextNode != -1) {
                ans.insert(nextNode);
            }
        } else {
            ans.insert(node.getStmtNumber());
        }
    }

    return ans;
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

void CFGHead::addToReachableQueue(CFGNode& node, std::queue<int>& q, std::unordered_set<int>& ans) {
    if (node.isDummyNode()) {
        int dn = findDummyNodeNext(node);
        if (dn != -1 && ans.find(dn) == ans.end()) {
            q.push(dn);
        }
    } else if (ans.find(node.getStmtNumber()) == ans.end()) {
        q.push(node.getStmtNumber());
    }
}

std::unordered_set<STMT_NUM> CFGHead::getReachableNodes(STMT_NUM stmt) {
    if(!isStatementInCFG(stmt)) {
        return {};
    }

    std::unordered_set<int> ans;
    std::queue<int> q;

    for(auto &node : adjList[stmt]) {
        addToReachableQueue(node, q, ans);
    }

    while(!q.empty()) {
        STMT_NUM sm = q.front();
        q.pop();

        if(ans.find(sm) != ans.end()) {
            continue;
        }

        ans.insert(sm);

        for(auto &node : adjList[sm]) {
            addToReachableQueue(node, q, ans);
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

void CFGHead::initializeFinalNode(CFGNode finalNode) {
    switch (finalNode.getNodeType()) {
        case CFGNodeType::DummyNode:
            dummyAdjList.insert({finalNode.getStmtNumber(), {-1, CFGNodeType::NullNode}});
            break;
        case CFGNodeType::NormalNode:
            adjList[finalNode.getStmtNumber()] = EDGES();
            break;
        case CFGNodeType::NullNode:
        default:
            assert(false);
    }
}

std::string CFGHead::returnAllEdgesInString() {
    std::string result = "Normal Node Adjacency List:\n";
    for (auto iter = adjList.begin(); iter != adjList.end(); ++iter) {
        STMT_NUM key = iter->first;
        result += std::to_string(key);
        result += ": ";
        for (CFGNode node:adjList.at(key)) {
            switch (node.getNodeType()) {
                case CFGNodeType::NormalNode:
                    result += std::to_string(node.getStmtNumber());
                    result += ", ";
                    break;
                case CFGNodeType::DummyNode:
                    result += "D";
                    result += std::to_string(node.getStmtNumber());
                    result += ", ";
                    break;
                case CFGNodeType::NullNode:
                    result += "Null";
                    result += ", ";
                    break;
            }
        }
        result += "\n";
    }
    result += "Dummy Node Adjacency List:\n";
    for (auto iter = dummyAdjList.begin(); iter != dummyAdjList.end(); ++iter) {
        STMT_NUM key = iter->first;
        result += std::to_string(key);
        result += ": ";
        CFGNode node = iter->second;
        switch (node.getNodeType()) {
            case CFGNodeType::NormalNode:
                result += std::to_string(node.getStmtNumber());
                result += ", ";
                break;
            case CFGNodeType::DummyNode:
                result += "D";
                result += std::to_string(node.getStmtNumber());
                result += ", ";
                break;
            case CFGNodeType::NullNode:
                result += "Null";
                result += ", ";
                break;
        }
        result += "\n";
    }
    return result;
}

CFGMap CFGHead::getNormalNodeMap() {
    return this->adjList;
}

CFGDummyMap CFGHead::getDummyNodeMap() {
    return this->dummyAdjList;
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