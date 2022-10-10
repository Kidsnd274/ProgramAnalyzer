#include "util/cfg/CFGHead.h"
#include "util/cfg/StatementNumberNotFoundException.h"
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
        REQUIRE_THROWS_AS(cfgTest->getEdges(3), StatementNumberNotFoundException);
        REQUIRE_THROWS_AS(cfgTest->getEdges(4), StatementNumberNotFoundException);
    }

    SECTION("Test getDummyNodeEdges") {
        REQUIRE_THROWS_AS(cfgTest->getDummyNodeEdge(1), StatementNumberNotFoundException);
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
        REQUIRE_THROWS_AS(cfgTest->getEdges(3), StatementNumberNotFoundException);
    }

    SECTION("Test getDummyNodeEdges") {
        REQUIRE(CFGNode::node(3) == cfgTest->getDummyNodeEdge(2));
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

TEST_CASE("Test final node") {
    SECTION("Normal node last") {
        CFGHeadPtr cfgTest = CFGHead::createNewCFG();
        cfgTest->connectNode(CFGNode::node(1), CFGNode::node(2));
        cfgTest->initializeFinalNode(CFGNode::node(2));

        REQUIRE(cfgTest->getEdges(2).empty());
    }

    SECTION("Dummy node last") {
        CFGHeadPtr cfgTest = CFGHead::createNewCFG();
        cfgTest->connectNode(CFGNode::node(1), CFGNode::dummyNode(1));
        cfgTest->initializeFinalNode(CFGNode::dummyNode(1));

        REQUIRE(cfgTest->getDummyNodeEdge(1).isNullNode());
    }
}
