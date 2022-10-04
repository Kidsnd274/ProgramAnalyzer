#ifndef SPA_CFGNODE_H
#define SPA_CFGNODE_H

#include <memory>
#include <utility>

enum class CFGNodeType {
    NormalNode,
    DummyNode
};

class CFGNode; // Forward declaration

typedef std::shared_ptr<CFGNode> CFGNodePtr;

class CFGNode {
private:
    int statementNumber;
    CFGNodePtr leftNode;
    CFGNodePtr rightNode;

public:
    CFGNode(int statementNumber) {
        this->statementNumber = statementNumber;
        this->leftNode = nullptr;
        this->rightNode = nullptr;
    }

    CFGNode(int statementNumber, CFGNodePtr leftNode, CFGNodePtr rightNode) {
        this->statementNumber = statementNumber;
        this->leftNode = std::move(leftNode);
        this->rightNode = std::move(rightNode);
    }

    int getStatementNumber() const;
    bool isThereLeftNode();
    bool isThereRightNode();
    bool areThereEdges(); // If Node is not connected to any other edges
    CFGNodePtr getLeftNode();
    CFGNodePtr getRightNode();
    void setLeftNode(CFGNodePtr leftNode);
    void setRightNode(CFGNodePtr rightNode);
};

#endif //SPA_CFGNODE_H
