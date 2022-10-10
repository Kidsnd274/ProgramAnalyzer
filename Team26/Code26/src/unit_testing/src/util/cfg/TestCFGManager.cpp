#include "catch.hpp"
#include "util/cfg/CFGManager.h"

TEST_CASE("Simple Test Case") {
    CFGManager testManager;
    testManager.addStandardNode(1);
    testManager.addStandardNode(2);
    CFGHeadPtr createdCFG = testManager.getCurrentCFG();

    CFGHeadPtr correctCFG = CFGHead::createNewCFG();
    correctCFG->connectNode(CFGNode::node(1), CFGNode::node(2));

    REQUIRE(*createdCFG == *correctCFG);
}

TEST_CASE("If test case") {
    CFGManager testManager;
    testManager.addStandardNode(1);
    testManager.addStandardNode(2);
    testManager.finalizeIfPortionOfIfStatement(1);
    testManager.addStandardNode(3);
    testManager.finalizeElsePortionOfIfStatement(1);
    CFGHeadPtr createdCFG = testManager.getCurrentCFG();

    CFGHeadPtr correctCFG = CFGHead::createNewCFG();
    correctCFG->connectNode(CFGNode::node(1), CFGNode::node(2));
    correctCFG->connectNode(CFGNode::node(1), CFGNode::node(3));
    correctCFG->connectNode(CFGNode::node(2), CFGNode::dummyNode(1));
    correctCFG->connectNode(CFGNode::node(3), CFGNode::dummyNode(1));

    REQUIRE(*createdCFG == *correctCFG);
}

TEST_CASE("While test case") {
    CFGManager testManager;
    testManager.addStandardNode(1);
    testManager.addStandardNode(2);
    testManager.finalizeWhileStatement(1);
    CFGHeadPtr createdCFG = testManager.getCurrentCFG();

    CFGHeadPtr correctCFG = CFGHead::createNewCFG();
    correctCFG->connectNode(CFGNode::node(1), CFGNode::node(2));
    correctCFG->connectNode(CFGNode::node(2), CFGNode::node(1));
    correctCFG->connectNode(CFGNode::node(1), CFGNode::dummyNode(1));

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
