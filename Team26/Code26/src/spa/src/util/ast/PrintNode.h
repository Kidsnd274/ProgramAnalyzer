#include <memory>
#include <string>
#include "StatementNode.h"

class PrintNode : public StatementNode {
    std::string variableName;
    
public:
    PrintNode(int statementNumber, std::string variableName) : StatementNode(statementNumber) {
        this->variableName = variableName;
    }

    std::string getVariableName();

    static std::shared_ptr<PrintNode> createPrintNode(int statementNumber, std::string variableName);
};
