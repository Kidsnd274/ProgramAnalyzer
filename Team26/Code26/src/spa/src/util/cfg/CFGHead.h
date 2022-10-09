#ifndef SPA_CFGHEAD_H
#define SPA_CFGHEAD_H

#include "CFGNode.h"
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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
    CFGMap getNormalNodeMap();
    CFGDummyMap getDummyNodeMap();
    static CFGHeadPtr createNewCFG();
    static bool compareEdgesEquality(EDGES& v1, EDGES& v2);
};

bool operator== (CFGHead leftCFG, CFGHead rightCFG);
bool operator!= (CFGHead leftCFG, CFGHead rightCFG);

#endif //SPA_CFGHEAD_H
