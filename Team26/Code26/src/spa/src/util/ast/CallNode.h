#include <memory>
#include <string>
#include "StatementNode.h"

class CallNode : public StatementNode {
private:
    std::string procedureName;

public:
    CallNode(int statementNumber, std::string procedureName) : StatementNode(statementNumber, statementType::CALL) {
        this->procedureName = procedureName;
    }

    std::string getProcedureName();

    static std::shared_ptr<CallNode> createCallNode(int statementNumber, std::string procedureName);
};
