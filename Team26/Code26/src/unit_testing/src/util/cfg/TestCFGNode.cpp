#include "util/cfg/CFGNode.h"
#include "catch.hpp"

TEST_CASE("Test that == operator works") {
    SECTION("Positive") {
        CFGNode node1 = CFGNode::newNode(3);
        CFGNode node2 = CFGNode::newNode(3);
        REQUIRE(node1 == node2);
    }

    SECTION("Positive 2") {
        CFGNode node1 = CFGNode::newDummyNode(2);
        CFGNode node2 = CFGNode::newDummyNode(2);
        REQUIRE(node1 == node2);
    }

    SECTION("Negative") {
        CFGNode node1 = CFGNode::newDummyNode(2);
        CFGNode node2 = CFGNode::newDummyNode(1);
        REQUIRE(node1 != node2);
    }

    SECTION("Negative 2") {
        CFGNode node1 = CFGNode::newNode(1);
        CFGNode node2 = CFGNode::newDummyNode(1);
        REQUIRE(node1 != node2);
    }
}
