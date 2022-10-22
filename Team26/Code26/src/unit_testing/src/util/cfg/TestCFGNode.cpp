#include "util/cfg/CFGNode.h"
#include "catch.hpp"

TEST_CASE("Test that == operator works") {
    SECTION("Positive") {
        CFGNode node1 = CFGNode::node(3);
        CFGNode node2 = CFGNode::node(3);
        REQUIRE(node1 == node2);
    }

    SECTION("Positive 2") {
        CFGNode node1 = CFGNode::dummyNode(2);
        CFGNode node2 = CFGNode::dummyNode(2);
        REQUIRE(node1 == node2);
    }

    SECTION("Negative") {
        CFGNode node1 = CFGNode::dummyNode(2);
        CFGNode node2 = CFGNode::dummyNode(1);
        REQUIRE(node1 != node2);
    }

    SECTION("Negative 2") {
        CFGNode node1 = CFGNode::node(1);
        CFGNode node2 = CFGNode::dummyNode(1);
        REQUIRE(node1 != node2); // test gh actions
    }
}

TEST_CASE("Null node type") {
    REQUIRE(CFGNode(-1, CFGNodeType::NullNode).isNullNode());
}
