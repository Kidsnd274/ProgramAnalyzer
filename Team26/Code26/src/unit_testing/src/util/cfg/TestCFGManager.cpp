#include "catch.hpp"
#include "util/cfg/CFGManager.h"

TEST_CASE("Simple Test Case") {
    CFGManager testManager;
    testManager.addStandardNode(1);
    testManager.addStandardNode(2);
    testManager.finalizeFinalNode();
    CFGHeadPtr createdCFG = testManager.getCurrentCFG();

    CFGHeadPtr correctCFG = CFGHead::createNewCFG();
    correctCFG->connectNode(CFGNode::node(1), CFGNode::node(2));
    correctCFG->initializeFinalNode(CFGNode::node(2));

    SECTION("Check for correct CFG") {
        REQUIRE(*createdCFG == *correctCFG);
    }

    SECTION("Check ifFirstStatementInCFG") {
        REQUIRE(createdCFG->isFirstStatementInCFG(1));
    }
}

TEST_CASE("If test case") {
    CFGManager testManager;
    testManager.addStandardNode(1);
    testManager.addStandardNode(2);
    testManager.finalizeIfPortionOfIfStatement(1);
    testManager.addStandardNode(3);
    testManager.finalizeElsePortionOfIfStatement(1);
    testManager.finalizeFinalNode();
    CFGHeadPtr createdCFG = testManager.getCurrentCFG();

    CFGHeadPtr correctCFG = CFGHead::createNewCFG();
    correctCFG->connectNode(CFGNode::node(1), CFGNode::node(2));
    correctCFG->connectNode(CFGNode::node(1), CFGNode::node(3));
    correctCFG->connectNode(CFGNode::node(2), CFGNode::dummyNode(1));
    correctCFG->connectNode(CFGNode::node(3), CFGNode::dummyNode(1));
    correctCFG->initializeFinalNode(CFGNode::dummyNode(1));

    REQUIRE(*createdCFG == *correctCFG);
}

TEST_CASE("While test case") {
    CFGManager testManager;
    testManager.addStandardNode(1);
    testManager.addStandardNode(2);
    testManager.finalizeWhileStatement(1);
    testManager.finalizeFinalNode();
    CFGHeadPtr createdCFG = testManager.getCurrentCFG();

    CFGHeadPtr correctCFG = CFGHead::createNewCFG();
    correctCFG->connectNode(CFGNode::node(1), CFGNode::node(2));
    correctCFG->connectNode(CFGNode::node(2), CFGNode::node(1));
    correctCFG->connectNode(CFGNode::node(1), CFGNode::dummyNode(1));
    correctCFG->initializeFinalNode(CFGNode::dummyNode(1));

    REQUIRE(*createdCFG == *correctCFG);
}

TEST_CASE("Mixed test case") {
    CFGManager testManager;
    testManager.createNewCFG();
    testManager.addStandardNode(1);
    testManager.addStandardNode(2);
    testManager.addStandardNode(3);
    testManager.finalizeIfPortionOfIfStatement(2);
    testManager.addStandardNode(4);
    testManager.finalizeElsePortionOfIfStatement(2);
    testManager.addStandardNode(5);
    testManager.addStandardNode(6);
    testManager.finalizeWhileStatement(5);
    testManager.addStandardNode(7);
    testManager.finalizeFinalNode();
    CFGHeadPtr createdCFG = testManager.getCurrentCFG();

    CFGHeadPtr correctCFG = CFGHead::createNewCFG();
    correctCFG->connectNode(CFGNode::node(1), CFGNode::node(2));
    correctCFG->connectNode(CFGNode::node(2), CFGNode::node(3));
    correctCFG->connectNode(CFGNode::node(3), CFGNode::dummyNode(2));
    correctCFG->connectNode(CFGNode::node(2), CFGNode::node(4));
    correctCFG->connectNode(CFGNode::node(4), CFGNode::dummyNode(2));
    correctCFG->connectNode(CFGNode::dummyNode(2), CFGNode::node(5));
    correctCFG->connectNode(CFGNode::node(5), CFGNode::node(6));
    correctCFG->connectNode(CFGNode::node(6), CFGNode::node(5));
    correctCFG->connectNode(CFGNode::node(5), CFGNode::dummyNode(5));
    correctCFG->connectNode(CFGNode::dummyNode(5), CFGNode::node(7));
    correctCFG->initializeFinalNode(CFGNode::node(7));

    REQUIRE(*createdCFG == *correctCFG);
}

TEST_CASE("Test finalize node") {
    SECTION("Normal node last") {
        CFGManager testManager;
        testManager.createNewCFG();
        testManager.addStandardNode(1);
        testManager.addStandardNode(2);
        testManager.finalizeFinalNode();
        CFGHeadPtr createdCFG = testManager.getCurrentCFG();

        CFGHeadPtr correctCFG = CFGHead::createNewCFG();
        correctCFG->connectNode(CFGNode::node(1), CFGNode::node(2));
        correctCFG->initializeFinalNode(CFGNode::node(2));

        REQUIRE(*createdCFG == *correctCFG);
    }

    SECTION("Dummy node last") {
        CFGManager testManager;
        testManager.createNewCFG();
        testManager.addStandardNode(1);
        testManager.addDummyNode(1);
        testManager.finalizeFinalNode();
        CFGHeadPtr createdCFG = testManager.getCurrentCFG();

        CFGHeadPtr correctCFG = CFGHead::createNewCFG();
        correctCFG->connectNode(CFGNode::node(1), CFGNode::dummyNode(1));
        correctCFG->initializeFinalNode(CFGNode::dummyNode(1));

        REQUIRE(*createdCFG == *correctCFG);
    }
}

TEST_CASE("Test Next in CFGManager") {
    CFGManager testManager;
    testManager.createNewCFG();
    testManager.addStandardNode(1);
    testManager.addStandardNode(2);
    testManager.addStandardNode(3);
    testManager.finalizeIfPortionOfIfStatement(2);
    testManager.addStandardNode(4);
    testManager.finalizeElsePortionOfIfStatement(2);
    testManager.addStandardNode(5);
    testManager.addStandardNode(6);
    testManager.finalizeWhileStatement(5);
    testManager.addStandardNode(7);
    testManager.finalizeFinalNode();
    CFGHeadPtr createdCFG = testManager.getCurrentCFG();

    REQUIRE(createdCFG->isNext(1,2));
    REQUIRE(createdCFG->isNext(2,3));
    REQUIRE_FALSE(createdCFG->isNext(2,1));
    REQUIRE(createdCFG->isNext(2,4));
    REQUIRE(createdCFG->isNext(3,5));
    REQUIRE(createdCFG->isNext(4,5));
    REQUIRE_FALSE(createdCFG->isNext(1,4));
    REQUIRE(createdCFG->isNext(5,6));
    REQUIRE(createdCFG->isNext(6,5));
    REQUIRE(createdCFG->isNext(5,7));
}

TEST_CASE("Test Reachable in CFGManager") {
    CFGManager testManager;
    testManager.createNewCFG();
    testManager.addStandardNode(1);
    testManager.addStandardNode(2);
    testManager.addStandardNode(3);
    testManager.finalizeIfPortionOfIfStatement(2);
    testManager.addStandardNode(4);
    testManager.finalizeElsePortionOfIfStatement(2);
    testManager.addStandardNode(5);
    testManager.addStandardNode(6);
    testManager.finalizeWhileStatement(5);
    testManager.addStandardNode(7);
    testManager.finalizeFinalNode();
    CFGHeadPtr createdCFG = testManager.getCurrentCFG();

    std::unordered_set<int> set1 = {2,3,4,5,6,7};
    std::unordered_set<int> set2 = {3,4,5,6,7};
    std::unordered_set<int> set3 = {5,6,7};
    std::unordered_set<int> set4 = {5,6,7};
    std::unordered_set<int> set5 = {5,6,7};
    std::unordered_set<int> set6 = {5,6,7};
    std::unordered_set<int> set7 = {};

    REQUIRE(createdCFG->getReachableNodes(1) == set1);
    REQUIRE(createdCFG->getReachableNodes(2) == set2);
    REQUIRE(createdCFG->getReachableNodes(3) == set3);
    REQUIRE(createdCFG->getReachableNodes(4) == set4);
    REQUIRE(createdCFG->getReachableNodes(5) == set5);
    REQUIRE(createdCFG->getReachableNodes(6) == set6);
    REQUIRE(createdCFG->getReachableNodes(7) == set7);
}

TEST_CASE("Test while if while while loop") {
    CFGManager testManager;
    testManager.createNewCFG();
    testManager.addStandardNode(1);
    testManager.addStandardNode(2);
    testManager.addStandardNode(3);
    testManager.addStandardNode(4);
    testManager.addStandardNode(5);
    testManager.addStandardNode(6);
    testManager.addStandardNode(7);
    testManager.addStandardNode(8);
    testManager.addStandardNode(9);
    testManager.finalizeWhileStatement(8);
    testManager.finalizeWhileStatement(6);
    testManager.finalizeIfPortionOfIfStatement(5);
    testManager.addStandardNode(10);
    testManager.finalizeElsePortionOfIfStatement(5);
    testManager.finalizeWhileStatement(1);
    testManager.finalizeFinalNode();
    CFGHeadPtr createdCFG = testManager.getCurrentCFG();

    CFGHeadPtr correctCFG = CFGHead::createNewCFG();
    correctCFG->connectNode(CFGNode::node(1), CFGNode::node(2));
    correctCFG->connectNode(CFGNode::node(2), CFGNode::node(3));
    correctCFG->connectNode(CFGNode::node(3), CFGNode::node(4));
    correctCFG->connectNode(CFGNode::node(4), CFGNode::node(5));
    correctCFG->connectNode(CFGNode::node(5), CFGNode::node(6));
    correctCFG->connectNode(CFGNode::node(6), CFGNode::node(7));
    correctCFG->connectNode(CFGNode::node(7), CFGNode::node(8));
    correctCFG->connectNode(CFGNode::node(8), CFGNode::node(9));
    correctCFG->connectNode(CFGNode::node(9), CFGNode::node(8));
    correctCFG->connectNode(CFGNode::node(8), CFGNode::dummyNode(8));
    correctCFG->connectNode(CFGNode::dummyNode(8), CFGNode::node(6));
    correctCFG->connectNode(CFGNode::node(6), CFGNode::dummyNode(6));
    correctCFG->connectNode(CFGNode::dummyNode(6), CFGNode::dummyNode(5));
    correctCFG->connectNode(CFGNode::node(5), CFGNode::node(10));
    correctCFG->connectNode(CFGNode::node(10), CFGNode::dummyNode(5));
    correctCFG->connectNode(CFGNode::dummyNode(5), CFGNode::node(1));
    correctCFG->connectNode(CFGNode::node(1), CFGNode::dummyNode(1));
    correctCFG->initializeFinalNode(CFGNode::dummyNode(1));

    REQUIRE(*createdCFG == *correctCFG);
}
