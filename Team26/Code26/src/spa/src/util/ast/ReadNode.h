#include <string>
#include "StatementNode.h"

class ReadNode : public StatementNode {
    std::string variableName;

    ReadNode(int statementNumber, std::string variableName) : StatementNode(statementNumber) {
        this->variableName = variableName;
    }

    std::string getVariableName();
};
