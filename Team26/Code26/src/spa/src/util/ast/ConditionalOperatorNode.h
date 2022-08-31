#include <memory>
#include <string>
#include "TNode.h"

class ConditionalOperatorNode : TNode {
private:
    std::string conditionalOperator;
    std::shared_ptr<TNode> leftNode;
    std::shared_ptr<TNode> rightNode;

public:
    ConditionalOperatorNode(int sN, std::string cO, std::shared_ptr<TNode> lN,
                            std::shared_ptr<TNode> rN) : TNode(sN) {
        leftNode = std::move(lN);
        rightNode = std::move(rN);
    }

    // For creating !
    ConditionalOperatorNode(int sN, std::string cO, std::shared_ptr<TNode> lN) : TNode(sN) {
        leftNode = std::move(lN);
        rightNode = nullptr;
    }

    // For creating rel_expr
    ConditionalOperatorNode(int sN, std::shared_ptr<TNode> lN) : TNode(sN) {
        leftNode = std::move(lN);
    }

    std::shared_ptr<TNode> getLeftNode();
    std::shared_ptr<TNode> getRightNode();
 };