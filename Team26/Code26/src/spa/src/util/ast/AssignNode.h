#ifndef SPA_UTIL_AST_ASSIGNNODE_H
#define SPA_UTIL_AST_ASSIGNNODE_H

#include <memory>
#include <string>
#include <utility>
#include "StatementNode.h"
#include "TNode.h"

class AssignNode : public StatementNode {
private:
    std::string variableName;
    std::shared_ptr<TNode> expression;

public:
    AssignNode(int statementNumber, std::string variableName, std::shared_ptr<TNode> expression) : StatementNode(statementNumber, statementType::ASSIGN) {
        this->variableName = std::move(variableName);
        this->expression = std::move(expression);
    }

    std::string getVariableName();
    std::shared_ptr<TNode> getExpression();

    static std::shared_ptr<AssignNode> createAssignNode(int statementNumber, std::string variableName,
                                                        std::shared_ptr<TNode> expression);
};
#endif
