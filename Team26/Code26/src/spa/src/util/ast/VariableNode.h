#include "IExpressionNode.h"
#include "util/Token.h"

class VariableNode : public IExpressionNode {
private:
    std::string variableName;
public:
    VariableNode(int sN, std::string t) : IExpressionNode(sN) {
        variableName = t;
    }

    std::string getName();
};
