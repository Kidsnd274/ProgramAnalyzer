#include "ITermNode.h"

class ConstantNode : ITermNode {
private:
    int constant;

public:
    ConstantNode(int sN, int cstant) : ITermNode(sN) {
        constant = cstant;
    }
};