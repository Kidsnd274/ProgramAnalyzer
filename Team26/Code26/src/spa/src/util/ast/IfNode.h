#include <memory>
#include <utility>
#include <vector>
#include "StatementNode.h"
#include "TNode.h"

class IfNode : public StatementNode {
private:
    std::shared_ptr<TNode> conditionalExpression;
    std::vector<std::shared_ptr<StatementNode>> ifStatementList;
    std::vector<std::shared_ptr<StatementNode>> elseStatementList;

public:
    IfNode(int statementNumber, std::shared_ptr<TNode> conditionalExpression,
           std::vector<std::shared_ptr<StatementNode>> ifStatementList,
           std::vector<std::shared_ptr<StatementNode>> elseStatementList) : StatementNode(statementNumber, statementType::IF) {
        this->conditionalExpression = std::move(conditionalExpression);
        this->ifStatementList = std::move(ifStatementList);
        this->elseStatementList = std::move(elseStatementList);
    }

    std::shared_ptr<TNode> getConditionalExpression();
    std::vector<std::shared_ptr<StatementNode>> getIfStatementList();
    std::vector<std::shared_ptr<StatementNode>> getElseStatementList();

    static std::shared_ptr<IfNode> createIfNode(int statementNumber, std::shared_ptr<TNode> conditionalExpression,
                                                std::vector<std::shared_ptr<StatementNode>> ifStatementList,
                                                std::vector<std::shared_ptr<StatementNode>> elseStatementList);
};
