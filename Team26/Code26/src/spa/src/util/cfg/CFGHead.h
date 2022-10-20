#ifndef SPA_CFGHEAD_H
#define SPA_CFGHEAD_H

#include "CFGNode.h"
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <string>

class CFGHead;

typedef std::shared_ptr<CFGHead> CFGHeadPtr;
typedef int STMT_NUM;
typedef std::vector<CFGNode> EDGES;
typedef std::unordered_map<STMT_NUM, EDGES> CFGMap;
typedef std::unordered_map<STMT_NUM, CFGNode> CFGDummyMap;

class CFGHead {
private:
    CFGMap adjList;
    CFGDummyMap dummyAdjList;
public:
    void connectNode(CFGNode node1, CFGNode node2);
    EDGES getEdges(STMT_NUM stmtNumber);
    CFGNode getDummyNodeEdge(STMT_NUM stmtNumber);
    CFGMap* getAdjList();
    CFGDummyMap* getDummyAdjList();
    void initializeFinalNode(CFGNode finalNode);
    static CFGHeadPtr createNewCFG();
    static bool compareEdgesEquality(EDGES v1, EDGES v2);

    // relationships
    bool isNext(STMT_NUM stmt1, STMT_NUM stmt2);
    bool isStatementInCFG(STMT_NUM stmt1);
    STMT_NUM findDummyNodeNext(CFGNode& dummy);

    // graph traversal
    std::unordered_set<STMT_NUM> getReachableNodes(STMT_NUM stmt);
    void addToReachableQueue(CFGNode& node, std::queue<int>& q, std::unordered_set<int>& ans);
    bool hasNextStatement(STMT_NUM stmt);
    std::unordered_set<STMT_NUM> getNextNodes(STMT_NUM stmt);

    // debug methods
    std::string returnAllEdgesInString();
    CFGMap getNormalNodeMap();
    CFGDummyMap getDummyNodeMap();
};

bool operator== (CFGHead leftCFG, CFGHead rightCFG);
bool operator!= (CFGHead leftCFG, CFGHead rightCFG);

#endif //SPA_CFGHEAD_H
