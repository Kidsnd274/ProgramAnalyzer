#ifndef SPA_CFGNODE_H
#define SPA_CFGNODE_H

#include <memory>
#include <utility>

enum class CFGNodeType {
    NormalNode,
    DummyNode
};

class CFGNode {
private:
    int statementNumber;
    CFGNodeType nodeType;

public:
    CFGNode(int statementNumber, CFGNodeType nodeType) {
        this->statementNumber = statementNumber;
        this->nodeType = nodeType;
    }

    int getStmtNumber() const;
    CFGNodeType getNodeType() const;
    bool isDummyNode();
    static CFGNode newNode(int statementNumber);
    static CFGNode newDummyNode(int statementNumber);
};

bool operator== (CFGNode leftNode, CFGNode rightNode);
bool operator!= (CFGNode leftNode, CFGNode rightNode);
#endif //SPA_CFGNODE_H
