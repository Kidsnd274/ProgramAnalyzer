#include "TNode.h"

int TNode::getStatementNumber() {
    return statementNumber;
}

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

bool TNode::isSameTree(const std::shared_ptr<TNode> &t1, const std::shared_ptr<TNode> &t2) {
    if (t1 == nullptr) {
        return t2 == nullptr;
    }

    if (t2 == nullptr) return false;

    if (t1->getNodeType() != t2->getNodeType() || t1->getValue() != t2->getValue()) {
        return false;
    }


    return isSameTree(t1->getLeftNode(), t2->getLeftNode()) && isSameTree(t1->getRightNode(), t2->getRightNode());
}

bool TNode::matchSubTree(const std::shared_ptr<TNode> &t1, const std::shared_ptr<TNode> &t2, const WildcardPosition pos) {
    if (t1 == nullptr) {
        return t2 == nullptr;
    }

    if (t2 == nullptr) {
        return pos != WildcardPosition::NONE;
    }

    if (isSameTree(t1, t2)) {
        return true;
    }

    switch (pos) {
        case WildcardPosition::NONE:
            return false;
        case WildcardPosition::LEFT:
            return matchSubTree(t1->getRightNode(), t2, WildcardPosition::LEFT);
        case WildcardPosition::RIGHT:
            return matchSubTree(t1->getLeftNode(), t2, WildcardPosition::RIGHT);
        case WildcardPosition::BOTH:
            return matchSubTree(t1->getLeftNode(), t2, WildcardPosition::BOTH) || matchSubTree(t1->getRightNode(), t2, WildcardPosition::BOTH);
        default:
            return false;  // Should not reach here
    }
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
