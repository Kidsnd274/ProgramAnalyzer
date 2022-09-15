#ifndef SPA_UTIL_AST_TNODE_H
#define SPA_UTIL_AST_TNODE_H

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
    bool hasLeftNode();
    bool hasRightNode();
    NodeType getNodeType();
    std::shared_ptr<TNode> getLeftNode();
    std::shared_ptr<TNode> getRightNode();
    std::string getValue();

    static bool isSameTree(const std::shared_ptr<TNode> &t1, const std::shared_ptr<TNode> &t2);

    /**
     * Return true if t2 is a subtree of t1.
     *
     * @return bool
     */
    static bool isSubTree(const std::shared_ptr<TNode> &t1, const std::shared_ptr<TNode> &t2);

    // Static Constructors
    static std::shared_ptr<TNode> createConstantValue(int statementNumber, std::string value);
    static std::shared_ptr<TNode> createVariableName(int statementNumber, std::string variableName);
    static std::shared_ptr<TNode> createTerm(int statementNumber, std::string operand, std::shared_ptr<TNode> leftNode,
                                             std::shared_ptr<TNode> rightNode);
    static std::shared_ptr<TNode> createConditionalExpression(int statementNumber, std::string compareOperand,
                                                              std::shared_ptr<TNode> leftNode,
                                                              std::shared_ptr<TNode> rightNode);
    static std::shared_ptr<TNode> createNOTConditionalExpression(int statementNumber, std::string logicalNotOperand,
                                                                        std::shared_ptr<TNode> conditionalExpression);
    static std::shared_ptr<TNode> createRelationalExpression(int statementNumber, std::string relationOperand,
                                                             std::shared_ptr<TNode> leftNode,
                                                             std::shared_ptr<TNode> rightNode);
};
#endif
