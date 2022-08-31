#include "TNode.h"
#include "util/Token.h"

class VariableNode : public TNode {
private:
    std::string variableName;
public:
    VariableNode(int sN, std::string t) : TNode(sN) {
        variableName = t;
    }

    std::string getName();
};
