#include <memory>
#include <string>
#include "ITermNode.h"

class ExpressionNode : public ITermNode {
private:
    std::string operand;
    std::shared_ptr<ITermNode> leftNode;
    std::shared_ptr<ITermNode> rightNode;

public:
    ExpressionNode(int sN, std::string op, std::shared_ptr<ITermNode> lN,
                   std::shared_ptr<ITermNode> rN) : ITermNode(sN) {
        operand = op;
        leftNode = std::move(lN);
        rightNode = std::move(rN);
    }
};