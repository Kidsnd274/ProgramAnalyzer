#include <memory>
#include "VariableNode.h"

class ReadNode : public TNode {
    std::shared_ptr<VariableNode> variableNode;

    ReadNode(int sN, std::shared_ptr<VariableNode> vN) : TNode(sN) {
        variableNode = std::move(vN);
    }
};