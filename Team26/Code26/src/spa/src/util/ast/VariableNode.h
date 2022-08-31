#include "ITermNode.h"
#include "util/Token.h"

class VariableNode : public ITermNode {
private:
    std::string variableName;
public:
    VariableNode(int sN, std::string t) : ITermNode(sN) {
        variableName = t;
    }

    std::string getName();
};
