#include "util/cfg/CFGHead.h"
#include "catch.hpp"

TEST_CASE("Test CFGHead creation") {
    CFGHeadPtr cfgTest = CFGHead::createNewCFG();
    cfgTest->connectNode(CFGNode::newNode(1), CFGNode::newNode(2));
    cfgTest->connectNode(CFGNode::newNode(2), CFGNode::newNode(3));

    SECTION("Test getEdges") {
        std::vector<CFGNode> node1 = {
                {CFGNode::newNode(2)}
        };
        std::vector<CFGNode> node2 = {
                {CFGNode::newNode(3)}
        };
        REQUIRE(node1 == cfgTest->getEdges(1));
        REQUIRE(node2 == cfgTest->getEdges(2));
        REQUIRE(cfgTest->getEdges(3).empty());
        REQUIRE(cfgTest->getEdges(4).empty());
    }

    SECTION("Test getDummyNodeEdges") {
        REQUIRE(cfgTest->getDummyNodeEdges(1).empty());
    }
}

TEST_CASE("Test CFGHead creation with dummy nodes") {

}
