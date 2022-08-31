#include <memory>
#include <vector>
#include "ConditionalOperatorNode.h"
#include "IStatementNode.h"

class IfNode : public IStatementNode {
private:
    std::shared_ptr<ConditionalOperatorNode> conditionalExpression;
    std::vector<std::shared_ptr<IStatementNode>> ifStatementList;
    std::vector<std::shared_ptr<IStatementNode>> elseStatementList;

public:
    IfNode(int sN, std::shared_ptr<ConditionalOperatorNode> cON,
           std::vector<std::shared_ptr<IStatementNode>> iSL,
           std::vector<std::shared_ptr<IStatementNode>> eSL) : IStatementNode(sN) {
        conditionalExpression = std::move(cON);
        ifStatementList = std::move(iSL);
        elseStatementList = std::move(eSL);
    }
};