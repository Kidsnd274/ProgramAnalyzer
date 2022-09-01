#include <memory>
#include <string>
#include "StatementNode.h"
#include "TNode.h"

class AssignNode : public StatementNode {
private:
    std::string variableName;
    std::shared_ptr<TNode> expression;

public:
    AssignNode(int statementNumber, std::string variableName, std::shared_ptr<TNode> expression) : StatementNode(statementNumber) {
        this->variableName = std::move(variableName);
        this->expression = std::move(expression);
    }

    std::string getVariableName();
    std::shared_ptr<TNode> getExpression();
};
