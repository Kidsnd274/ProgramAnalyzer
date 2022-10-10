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

TEST_CASE("Test Next") {
    CFGHeadPtr cfgTest = CFGHead::createNewCFG();
    cfgTest->connectNode(CFGNode::node(1), CFGNode::node(2));
    cfgTest->connectNode(CFGNode::node(2), CFGNode::node(3));
    cfgTest->connectNode(CFGNode::node(3), CFGNode::node(1));
    cfgTest->connectNode(CFGNode::node(1), CFGNode::dummyNode(1));
    cfgTest->connectNode(CFGNode::dummyNode(1), CFGNode::node(4));
    cfgTest->connectNode(CFGNode::node(4), CFGNode::node(5));
    cfgTest->connectNode(CFGNode::node(4), CFGNode::node(6));
    cfgTest->connectNode(CFGNode::node(5), CFGNode::dummyNode(4));
    cfgTest->connectNode(CFGNode::node(6), CFGNode::dummyNode(4));
    cfgTest->initializeFinalNode(CFGNode::dummyNode(4));

    REQUIRE(cfgTest->isNext(1,2));
    REQUIRE(cfgTest->isNext(2,3));
    REQUIRE_FALSE(cfgTest->isNext(2,1));
    REQUIRE(cfgTest->isNext(3,1));
    REQUIRE(cfgTest->isNext(1,4));
    REQUIRE(cfgTest->isNext(4,5));
    REQUIRE(cfgTest->isNext(4,6));
    REQUIRE_FALSE(cfgTest->isNext(5,6));
    REQUIRE_FALSE(cfgTest->isNext(3,4));
    REQUIRE_FALSE(cfgTest->isNext(6,7));
}

TEST_CASE("Test Reachable") {
    CFGHeadPtr cfgTest = CFGHead::createNewCFG();
    cfgTest->connectNode(CFGNode::node(1), CFGNode::node(2));
    cfgTest->connectNode(CFGNode::node(2), CFGNode::node(3));
    cfgTest->connectNode(CFGNode::node(3), CFGNode::node(1));
    cfgTest->connectNode(CFGNode::node(1), CFGNode::dummyNode(1));
    cfgTest->connectNode(CFGNode::dummyNode(1), CFGNode::node(4));
    cfgTest->connectNode(CFGNode::node(4), CFGNode::node(5));
    cfgTest->connectNode(CFGNode::node(4), CFGNode::node(6));
    cfgTest->connectNode(CFGNode::node(5), CFGNode::dummyNode(4));
    cfgTest->connectNode(CFGNode::node(6), CFGNode::dummyNode(4));
    cfgTest->initializeFinalNode(CFGNode::dummyNode(4));

    std::unordered_set<int> set1 = {1,2,3,4,5,6};
    std::unordered_set<int> set2 = {1,2,3,4,5,6};
    std::unordered_set<int> set3 = {1,2,3,4,5,6};
    std::unordered_set<int> set4 = {4,5,6};
    std::unordered_set<int> set5 = {5};
    std::unordered_set<int> set6 = {6};

    REQUIRE(cfgTest->getReachableNodes(1) == set1);
    REQUIRE(cfgTest->getReachableNodes(2) == set2);
    REQUIRE(cfgTest->getReachableNodes(3) == set3);
    REQUIRE(cfgTest->getReachableNodes(4) == set4);
    REQUIRE(cfgTest->getReachableNodes(5) == set5);
    REQUIRE(cfgTest->getReachableNodes(6) == set6);
}
