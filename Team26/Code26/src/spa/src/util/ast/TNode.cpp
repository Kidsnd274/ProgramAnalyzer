#include "TNode.h"

int TNode::getStatementNumber() {
    return statementNumber;
}

// TODO: For Samuel, double check that this is the correct way of checking if a shared_ptr is nullptr (eg. ConstantValue node type shld return this as false)
bool TNode::hasLeftNode() {
    return leftNode != nullptr;
}

bool TNode::hasRightNode() {
    return rightNode != nullptr;
}

NodeType TNode::getNodeType() {
    return nodeType;
}

std::shared_ptr<TNode> TNode::getLeftNode() {
    return leftNode;
}

std::shared_ptr<TNode> TNode::getRightNode() {
    return rightNode;
}

std::string TNode::getValue() {
    return value;
}

// Static Constructors
std::shared_ptr<TNode> TNode::createConstantValue(int statementNumber, std::string value) {
    return std::make_shared<TNode>(statementNumber, NodeType::ConstantValue, value, nullptr, nullptr);
}

std::shared_ptr<TNode> TNode::createVariableName(int statementNumber, std::string variableName) {
    return std::make_shared<TNode>(statementNumber, NodeType::VariableName, variableName, nullptr, nullptr);
}

std::shared_ptr<TNode> TNode::createTerm(int statementNumber, std::string operand, std::shared_ptr<TNode> leftNode,
                                         std::shared_ptr<TNode> rightNode) {
    return std::make_shared<TNode>(statementNumber, NodeType::Term, operand, leftNode, rightNode);
}

std::shared_ptr<TNode> TNode::createConditionalExpression(int statementNumber, std::string compareOperand,
                                                          std::shared_ptr<TNode> leftNode,
                                                          std::shared_ptr<TNode> rightNode) {
    return std::make_shared<TNode>(statementNumber, NodeType::ConditionalExpression, compareOperand, leftNode, rightNode);
}

std::shared_ptr<TNode> TNode::createNOTConditionalExpression(int statementNumber, std::string logicalNotOperand,
                                                                    std::shared_ptr<TNode> conditionalExpression) {
    return std::make_shared<TNode>(statementNumber, NodeType::ConditionalExpression, logicalNotOperand,
                                   conditionalExpression, nullptr);
}

std::shared_ptr<TNode> TNode::createRelationalExpression(int statementNumber, std::string relationOperand,
                                                         std::shared_ptr<TNode> leftNode,
                                                         std::shared_ptr<TNode> rightNode) {
    return std::make_shared<TNode>(statementNumber, NodeType::RelationalExpression, relationOperand,
                                   leftNode, rightNode);
}
