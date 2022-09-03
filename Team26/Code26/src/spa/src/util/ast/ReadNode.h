#include <string>
#include "StatementNode.h"

class ReadNode : public StatementNode {
    std::string variableName;

public:
    ReadNode(int statementNumber, std::string variableName) : StatementNode(statementNumber) {
        this->variableName = variableName;
    }

    std::string getVariableName();
};
