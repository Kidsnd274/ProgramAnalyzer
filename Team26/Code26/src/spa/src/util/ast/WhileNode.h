#include <memory>
#include <utility>
#include <vector>
#include "StatementNode.h"
#include "TNode.h"

class WhileNode : public StatementNode {
private:
    std::shared_ptr<TNode> conditionalExpression;
    std::vector<std::shared_ptr<StatementNode>> statementList;

public:
    WhileNode(int statementNumber, std::shared_ptr<TNode> conditionalExpression,
            std::vector<std::shared_ptr<StatementNode>> statementList) : StatementNode(statementNumber, statementType::WHILE) {
        this->conditionalExpression = std::move(conditionalExpression);
        this->statementList = std::move(statementList);
    }

    std::shared_ptr<TNode> getConditionalExpression();
    std::vector<std::shared_ptr<StatementNode>> getStatementList();

    static std::shared_ptr<WhileNode> createWhileNode(int statementNumber, std::shared_ptr<TNode> conditionalExpression,
                                                      std::vector<std::shared_ptr<StatementNode>> statementList);
};
