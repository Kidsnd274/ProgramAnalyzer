#ifndef SPA_CFGHEAD_H
#define SPA_CFGHEAD_H

#include "CFGNode.h"
#include <unordered_map>
#include <vector>

class CFGHead;

typedef std::shared_ptr<CFGHead> CFGHeadPtr;
typedef int STMT_NUM;
typedef std::vector<CFGNode> EDGES;
typedef std::vector<std::vector<EDGES>> CFGMap;
typedef std::unordered_map<STMT_NUM, CFGNode> CFGAdjMap;

class CFGHead {
private:
     CFGMap adjList;
     CFGAdjMap dummyAdjList;
public:
    void connectNode(CFGNode node1, CFGNode node2);
    EDGES getEdges(STMT_NUM stmtNumber);
    EDGES getDummyNodeEdges(STMT_NUM stmtNumber);
    CFGMap getNormalNodeMap();
    CFGMap getDummyNodeMap();
    static CFGHeadPtr createNewCFG();
};

bool operator== (CFGHead leftCFG, CFGHead rightCFG);
bool operator!= (CFGHead leftCFG, CFGHead rightCFG);

#endif //SPA_CFGHEAD_H
