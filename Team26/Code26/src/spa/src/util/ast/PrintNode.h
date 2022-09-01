#include <string>
#include "StatementNode.h"

class PrintNode : public StatementNode {
    std::string variableName;

    PrintNode(int statementNumber, std::string variableName) : StatementNode(statementNumber) {
        this->variableName = variableName;
    }

    std::string getVariableName();
};
