#include "util/ast/TNode.h"
#include "catch.hpp"

std::shared_ptr<TNode> makeTNode(int statementNumber, NodeType nodeType, std::string value,
                                 std::shared_ptr<TNode> leftNode, std::shared_ptr<TNode> rightNode) {
    return std::make_shared<TNode>(statementNumber, nodeType, value, leftNode, rightNode);
}

TEST_CASE("Testing get and has methods") {
    SECTION("Testing Constant Value") { // Testing for nullptr and value return values
        std::shared_ptr<TNode> nodeToTest = makeTNode(0, NodeType::ConstantValue, "0", nullptr, nullptr);
        REQUIRE(!nodeToTest->hasLeftNode());
        REQUIRE(!nodeToTest->hasRightNode());
        REQUIRE(nodeToTest->getStatementNumber() == 0);
        REQUIRE(nodeToTest->getValue() == "0");
        REQUIRE(nodeToTest->getNodeType() == NodeType::ConstantValue);
    }

    SECTION("Testing Conditional Expression") { // Testing for getLeftNode and getRightNode
        std::shared_ptr<TNode> dummyLeftNode = makeTNode(1, NodeType::ConstantValue, "dummyLeft", nullptr, nullptr);
        std::shared_ptr<TNode> dummyRightNode = makeTNode(2, NodeType::ConstantValue, "dummyRight", nullptr, nullptr);
        std::shared_ptr<TNode> nodeToTest = makeTNode(0, NodeType::ConditionalExpression, "&&", dummyLeftNode, dummyRightNode);

        REQUIRE(nodeToTest->getStatementNumber() == 0);
        REQUIRE(nodeToTest->hasLeftNode());
        REQUIRE(nodeToTest->hasRightNode());
        REQUIRE(nodeToTest->getNodeType() == NodeType::ConditionalExpression);
        REQUIRE(nodeToTest->getValue() == "&&");
        REQUIRE(nodeToTest->getLeftNode() == dummyLeftNode);
        REQUIRE(nodeToTest->getRightNode() == dummyRightNode);
    }
}

TEST_CASE("Testing Static Constructors") {
    SECTION("Testing creating a Constant Value") {
        std::string constantValue = "100";
        std::shared_ptr<TNode> nodeToTest = TNode::createConstantValue(0, constantValue);
        REQUIRE(nodeToTest->getStatementNumber() == 0);
        REQUIRE(!nodeToTest->hasLeftNode());
        REQUIRE(!nodeToTest->hasRightNode());
        REQUIRE(nodeToTest->getNodeType() == NodeType::ConstantValue);
        REQUIRE(nodeToTest->getLeftNode() == nullptr);
        REQUIRE(nodeToTest->getRightNode() == nullptr);
        REQUIRE(nodeToTest->getValue() == constantValue);
    }

    SECTION("Testing creating a Variable Name") {
        std::string variableName = "myVariableName";
        std::shared_ptr<TNode> nodeToTest = TNode::createVariableName(0, variableName);
        REQUIRE(nodeToTest->getStatementNumber() == 0);
        REQUIRE(!nodeToTest->hasLeftNode());
        REQUIRE(!nodeToTest->hasRightNode());
        REQUIRE(nodeToTest->getNodeType() == NodeType::VariableName);
        REQUIRE(nodeToTest->getLeftNode() == nullptr);
        REQUIRE(nodeToTest->getRightNode() == nullptr);
        REQUIRE(nodeToTest->getValue() == variableName);
    }

    SECTION("Testing creating a Term") {
        std::string operand = "*";
        std::shared_ptr<TNode> dummyLeftNode = makeTNode(1, NodeType::ConstantValue, "dummyLeft", nullptr, nullptr);
        std::shared_ptr<TNode> dummyRightNode = makeTNode(2, NodeType::ConstantValue, "dummyRight", nullptr, nullptr);
        std::shared_ptr<TNode> nodeToTest = TNode::createTerm(0, operand, dummyLeftNode, dummyRightNode);
        REQUIRE(nodeToTest->getStatementNumber() == 0);
        REQUIRE(nodeToTest->hasLeftNode());
        REQUIRE(nodeToTest->hasRightNode());
        REQUIRE(nodeToTest->getNodeType() == NodeType::Term);
        REQUIRE(nodeToTest->getLeftNode() == dummyLeftNode);
        REQUIRE(nodeToTest->getRightNode() == dummyRightNode);
        REQUIRE(nodeToTest->getValue() == operand);
    }

    SECTION("Testing creating a Conditional Expression") {
        std::string operand = "&&";
        std::shared_ptr<TNode> dummyLeftNode = makeTNode(1, NodeType::ConstantValue, "dummyLeft", nullptr, nullptr);
        std::shared_ptr<TNode> dummyRightNode = makeTNode(2, NodeType::ConstantValue, "dummyRight", nullptr, nullptr);
        std::shared_ptr<TNode> nodeToTest = TNode::createConditionalExpression(0, operand, dummyLeftNode, dummyRightNode);
        REQUIRE(nodeToTest->getStatementNumber() == 0);
        REQUIRE(nodeToTest->hasLeftNode());
        REQUIRE(nodeToTest->hasRightNode());
        REQUIRE(nodeToTest->getNodeType() == NodeType::ConditionalExpression);
        REQUIRE(nodeToTest->getLeftNode() == dummyLeftNode);
        REQUIRE(nodeToTest->getRightNode() == dummyRightNode);
        REQUIRE(nodeToTest->getValue() == operand);
    }


    SECTION("Testing creating a Logical NOT Conditional Expression") {
        std::string operand = "!";
        std::shared_ptr<TNode> dummyLeftNode = makeTNode(1, NodeType::ConstantValue, "dummyLeft", nullptr, nullptr);
        std::shared_ptr<TNode> nodeToTest = TNode::createNOTConditionalExpression(0, operand, dummyLeftNode);
        REQUIRE(nodeToTest->getStatementNumber() == 0);
        REQUIRE(nodeToTest->hasLeftNode());
        REQUIRE(!nodeToTest->hasRightNode());         // Right Node should be nullptr
        REQUIRE(nodeToTest->getNodeType() == NodeType::ConditionalExpression);
        REQUIRE(nodeToTest->getLeftNode() == dummyLeftNode);
        REQUIRE(nodeToTest->getRightNode() == nullptr);         // Right Node should be nullptr
        REQUIRE(nodeToTest->getValue() == operand);
    }

    SECTION("Testing creating a Relational Expression") {
        std::string operand = "<";
        std::shared_ptr<TNode> dummyLeftNode = makeTNode(1, NodeType::ConstantValue, "dummyLeft", nullptr, nullptr);
        std::shared_ptr<TNode> dummyRightNode = makeTNode(2, NodeType::ConstantValue, "dummyRight", nullptr, nullptr);
        std::shared_ptr<TNode> nodeToTest = TNode::createRelationalExpression(0, operand, dummyLeftNode, dummyRightNode);
        REQUIRE(nodeToTest->getStatementNumber() == 0);
        REQUIRE(nodeToTest->hasLeftNode());
        REQUIRE(nodeToTest->hasRightNode());
        REQUIRE(nodeToTest->getNodeType() == NodeType::RelationalExpression);
        REQUIRE(nodeToTest->getLeftNode() == dummyLeftNode);
        REQUIRE(nodeToTest->getRightNode() == dummyRightNode);
        REQUIRE(nodeToTest->getValue() == operand);
    }
}
