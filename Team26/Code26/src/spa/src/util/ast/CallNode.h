#include <memory>
#include <string>
#include "StatementNode.h"

class CallNode : public StatementNode {
    std::string procedureName;

public:
    CallNode(int statementNumber, std::string procedureName) : StatementNode(statementNumber) {
        this->procedureName = procedureName;
    }

    std::string getProcedureName();

    static std::shared_ptr<CallNode> createCallNode(int statementNumber, std::string procedureName);
};