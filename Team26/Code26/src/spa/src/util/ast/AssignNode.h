#include <memory>

#include "ITermNode.h"
#include "IStatementNode.h"
#include "VariableNode.h"

class AssignNode : public IStatementNode {
private:
    std::shared_ptr<VariableNode> leftNode;
    std::shared_ptr<ITermNode> rightNode;

public:
    AssignNode(int sN, std::shared_ptr<VariableNode> lN,
               std::shared_ptr<ITermNode> rN) : IStatementNode(sN) {
        leftNode = std::move(lN);
        rightNode = std::move(rN);
    }
};

