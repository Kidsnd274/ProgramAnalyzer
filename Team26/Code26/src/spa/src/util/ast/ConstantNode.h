#include "IExpressionNode.h"

class ConstantNode : IExpressionNode {
private:
    int constant;

public:
    ConstantNode(int sN, int cstant) : IExpressionNode(sN) {
        constant = cstant;
    }
};