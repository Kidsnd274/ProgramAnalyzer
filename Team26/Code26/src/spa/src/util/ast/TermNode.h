#include <memory>
#include <string>
#include "IExpressionNode.h"

class TermNode : public IExpressionNode {
private:
    std::string operand;
    std::shared_ptr<IExpressionNode> leftNode;
    std::shared_ptr<IExpressionNode> rightNode;

public:
    TermNode(int sN, std::string op, std::shared_ptr<IExpressionNode> lN,
             std::shared_ptr<IExpressionNode> rN) : IExpressionNode(sN) {
        operand = op;
        leftNode = std::move(lN);
        rightNode = std::move(rN);
    }
};