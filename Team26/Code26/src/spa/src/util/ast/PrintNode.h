#include <memory>
#include "VariableNode.h"

class PrintNode : public TNode {
    std::shared_ptr<VariableNode> variableNode;

    PrintNode(std::shared_ptr<VariableNode> vN) {
        variableNode = std::move(vN);
    }
};