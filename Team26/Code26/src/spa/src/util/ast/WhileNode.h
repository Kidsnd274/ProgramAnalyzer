#include <memory>
#include <vector>
#include "ConditionalOperatorNode.h"
#include "IStatementNode.h"

class WhileNode : public IStatementNode {
private:
    std::shared_ptr<ConditionalOperatorNode> conditionalExpression;
    std::vector<std::shared_ptr<IStatementNode>> statementList;

public:
    WhileNode(int sN, std::shared_ptr<ConditionalOperatorNode> cON,
            std::vector<std::shared_ptr<IStatementNode>> sl) : IStatementNode(sN) {
        conditionalExpression = std::move(cON);
        statementList = std::move(sl);
    };
};