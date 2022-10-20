#include "util/cfg/CFGLogic.h"
#include "../../sp/stubs/PKBInterfaceStubForDE.h"
#include "catch.hpp"

TEST_CASE("Simple test to see if adjlist and dummyadjlist can be accessed") {
    CFGHeadPtr cfgTest = CFGHead::createNewCFG();
    cfgTest->connectNode(CFGNode::node(1), CFGNode::node(2));
    cfgTest->connectNode(CFGNode::node(2), CFGNode::node(3));
    cfgTest->initializeFinalNode(CFGNode::node(3));

    PKBInterface* pkbInterface = new PKBInterfaceStubForDE();
    CFGLogic cfgLogic(cfgTest, pkbInterface);

    SECTION("Test isStatementInCFG") {
        REQUIRE(cfgTest->isStatementInCFG(1) == cfgLogic.isStatementInCFG(1));
        REQUIRE(cfgTest->isStatementInCFG(2) == cfgLogic.isStatementInCFG(3));
        REQUIRE(cfgTest->isStatementInCFG(2) == cfgLogic.isStatementInCFG(3));
        REQUIRE(cfgTest->isStatementInCFG(2) == cfgLogic.isStatementInCFG(3));
    }
}
