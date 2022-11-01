#include <memory>
#include <string>
#include "StatementNode.h"

class ReadNode : public StatementNode {
private:
    std::string variableName;

public:
    ReadNode(int statementNumber, std::string variableName) : StatementNode(statementNumber, statementType::READ) {
        this->variableName = variableName;
    }

    std::string getVariableName();
    static std::shared_ptr<ReadNode> createReadNode(int statementNumber, std::string variableName);
};
