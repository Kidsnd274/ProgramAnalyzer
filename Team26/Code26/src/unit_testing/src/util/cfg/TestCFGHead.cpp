#include "util/cfg/CFGHead.h"
#include "catch.hpp"

TEST_CASE("Test CFGHead creation") {
    CFGHeadPtr cfgTest = CFGHead::createNewCFG();
    cfgTest->connectNode(CFGNode::node(1), CFGNode::node(2));
    cfgTest->connectNode(CFGNode::node(2), CFGNode::node(3));

    SECTION("Test getEdges") {
        std::vector<CFGNode> node1 = {
                {CFGNode::node(2)}
        };
        std::vector<CFGNode> node2 = {
                {CFGNode::node(3)}
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
    CFGHeadPtr cfgTest = CFGHead::createNewCFG();
    cfgTest->connectNode(CFGNode::node(1), CFGNode::node(2));
    cfgTest->connectNode(CFGNode::node(2), CFGNode::dummyNode(2));
    cfgTest->connectNode(CFGNode::dummyNode(2), CFGNode::node(3));

    SECTION("Test getEdges") {
        std::vector<CFGNode> node1 = {
                {CFGNode::node(2)}
        };
        std::vector<CFGNode> node2 = {
                {CFGNode::dummyNode(2)}
        };
        REQUIRE(node1 == cfgTest->getEdges(1));
        REQUIRE(node2 == cfgTest->getEdges(2));
        REQUIRE(cfgTest->getEdges(3).empty());
    }

    SECTION("Test getDummyNodeEdges") {
        std::vector<CFGNode> node1 = {
                {CFGNode::node(3)}
        };
        REQUIRE(node1 == cfgTest->getDummyNodeEdges(2));
    }
}

TEST_CASE("Test == operator") {
    SECTION("Positive") {
        CFGHeadPtr cfgTest = CFGHead::createNewCFG();
        cfgTest->connectNode(CFGNode::node(1), CFGNode::node(2));
        cfgTest->connectNode(CFGNode::node(2), CFGNode::node(3));

        CFGHeadPtr cfgTest2 = CFGHead::createNewCFG();
        cfgTest2->connectNode(CFGNode::node(1), CFGNode::node(2));
        cfgTest2->connectNode(CFGNode::node(2), CFGNode::node(3));

        REQUIRE(*cfgTest == *cfgTest2);
    }

    SECTION("Negative") {
        CFGHeadPtr cfgTest = CFGHead::createNewCFG();
        cfgTest->connectNode(CFGNode::node(1), CFGNode::node(2));
        cfgTest->connectNode(CFGNode::node(2), CFGNode::node(3));

        CFGHeadPtr cfgTest2 = CFGHead::createNewCFG();
        cfgTest2->connectNode(CFGNode::node(1), CFGNode::node(2));

        REQUIRE(*cfgTest != *cfgTest2);
    }

    SECTION("Positive 2") {
        CFGHeadPtr cfgTest = CFGHead::createNewCFG();
        cfgTest->connectNode(CFGNode::node(1), CFGNode::node(2));
        cfgTest->connectNode(CFGNode::node(1), CFGNode::node(3));
        cfgTest->connectNode(CFGNode::node(2), CFGNode::dummyNode(1));
        cfgTest->connectNode(CFGNode::node(2), CFGNode::dummyNode(3));

        // Order changed
        CFGHeadPtr cfgTest2 = CFGHead::createNewCFG();
        cfgTest2->connectNode(CFGNode::node(1), CFGNode::node(3));
        cfgTest2->connectNode(CFGNode::node(1), CFGNode::node(2));
        cfgTest2->connectNode(CFGNode::node(2), CFGNode::dummyNode(1));
        cfgTest2->connectNode(CFGNode::node(2), CFGNode::dummyNode(3));

        REQUIRE(*cfgTest == *cfgTest2);
    }
}
