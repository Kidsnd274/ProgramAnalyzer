#include <memory>
#include <string>
#include <utility>

enum class NodeType {
    Expression,
    ConditionalExpression,
    RelationalExpression,
    Term,
    VariableName,
    ConstantValue,
};

class TNode {
private:
    int statementNumber;
    NodeType nodeType;
    std::string value;
    std::shared_ptr<TNode> leftNode;
    std::shared_ptr<TNode> rightNode;

public:
    TNode(int statementNumber, NodeType nodeType, std::string value, std::shared_ptr<TNode> leftNode, std::shared_ptr<TNode> rightNode) {
        this->statementNumber = statementNumber;
        this->nodeType = nodeType;
        this->value = std::move(value);
        this->leftNode = std::move(leftNode);
        this->rightNode = std::move(rightNode);
    }

    int getStatementNumber();
    bool hasRightNode();
    bool hasLeftNode();
    bool hasValue();
    NodeType getNodeType();
    std::shared_ptr<TNode> getLeftNode();
    std::shared_ptr<TNode> getRightNode();
    std::string getValue();

    // Static Constructors
    static std::shared_ptr<TNode> createConstantValue(std::string value);
    static std::shared_ptr<TNode> createVariableName(std::string value);
    static std::shared_ptr<TNode> createTerm(std::string operand, std::shared_ptr<TNode> leftNode,
                                             std::shared_ptr<TNode> rightNode);
    static std::shared_ptr<TNode> createConditionalExpression(std::string compareOperand,
                                                              std::shared_ptr<TNode> leftNode,
                                                              std::shared_ptr<TNode> rightNode);
    static std::shared_ptr<TNode> createLogicalNotConditionalExpression(std::shared_ptr<TNode> conditionalExpression);
};