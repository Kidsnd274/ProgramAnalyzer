#include "catch.hpp"
#include "util/Lexer.h"
#include "sp/SourceProcessor.h"
#include "sp/Parser.h"
#include <iostream>

TEST_CASE("Test checkExpressionString") {
    SECTION("Positive") {
        std::string exprString = "x + 1";
        REQUIRE(SourceProcessor::checkExpressionString(exprString) == true);
    }

    SECTION("Positive 2") {
        std::string exprString = "thisisavariable + 12313211 + hehehaha";
        REQUIRE(SourceProcessor::checkExpressionString(exprString) == true);
    }

    SECTION("Positive 3") {
        std::string exprString = "thisisavariable+12313211+hehehaha";
        REQUIRE(SourceProcessor::checkExpressionString(exprString) == true);
    }

    SECTION("Negative 1") {
        std::string exprString = "x,, + 1";
        REQUIRE(SourceProcessor::checkExpressionString(exprString) == false);
    }

    SECTION("Negative 2") {
        std::string exprString = "thisisavariable ++ 12313211 + hehehaha";
        REQUIRE(SourceProcessor::checkExpressionString(exprString) == false);
    }
    SECTION("Negative 3") {
        std::string exprString = "thisisavaria.ble + 12313211 + hehehaha";
        REQUIRE(SourceProcessor::checkExpressionString(exprString) == false);
    }
}

TEST_CASE("Test parseExpressionFromString") {
    SECTION("Simple Test") {
        std::string exprString = "x + 1";

        std::shared_ptr<TNode> correctTNode = TNode::createTerm(1, "+", TNode::createVariableName(1, "x"), TNode::createConstantValue(1, "1"));
        std::shared_ptr<TNode> generatedTNode = SourceProcessor::parseExpressionFromString(exprString);

        REQUIRE(TNode::isSameTree(correctTNode, generatedTNode));
    }

    SECTION("Slightly more advanced test") {
        std::string exprString = "1 + x * 4 * 8 + 12";

        std::shared_ptr<TNode> node1 = TNode::createTerm(1, "*", TNode::createVariableName(1, "x"), TNode::createConstantValue(1, "4"));
        std::shared_ptr<TNode> node2 = TNode::createTerm(1, "*", node1, TNode::createConstantValue(1, "8"));
        std::shared_ptr<TNode> node3 = TNode::createTerm(1, "+", TNode::createConstantValue(1, "1"), node2);
        std::shared_ptr<TNode> correctTNode = TNode::createTerm(1, "+", node3, TNode::createConstantValue(1, "12"));
        std::shared_ptr<TNode> generatedTNode = SourceProcessor::parseExpressionFromString(exprString);

        REQUIRE(TNode::isSameTree(correctTNode, generatedTNode));
    }
}


