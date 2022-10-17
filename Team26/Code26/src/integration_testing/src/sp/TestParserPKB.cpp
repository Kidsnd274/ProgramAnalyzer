#include "sp/Parser.h"
#include "util/cfg/StatementNumberNotFoundException.h"
#include "catch.hpp"

TEST_CASE("Test Parser passing CFG to PKB successfully after Parser dies") {
    PKBInterface *pkbInterface = new PKBInterface();
    SECTION("Parsing simple test case") {
        std::vector<SPToken> validSimpleTokens = {SPToken("procedure", SPTokenType::ProcedureToken),
                                                  SPToken("test", SPTokenType::NameToken),
                                                  SPToken("{", SPTokenType::LCurlyToken),
                                                  SPToken("read", SPTokenType::ReadToken),
                                                  SPToken("x", SPTokenType::NameToken),
                                                  SPToken(";", SPTokenType::SemiColonToken),
                                                  SPToken("x", SPTokenType::NameToken),
                                                  SPToken("=", SPTokenType::AssignToken),
                                                  SPToken("x", SPTokenType::NameToken),
                                                  SPToken("+", SPTokenType::OpToken),
                                                  SPToken("1", SPTokenType::ConstToken),
                                                  SPToken(";", SPTokenType::SemiColonToken),
                                                  SPToken("}", SPTokenType::RCurlyToken)};

        Parser *testParser = new Parser(validSimpleTokens, pkbInterface);
        testParser->parseSimple();

        delete testParser;
        testParser = nullptr;
    }
    CFGHeadPtr createdCFG = pkbInterface->getCfgOfProcedure("test");

    CFGHeadPtr correctCFG = CFGHead::createNewCFG();
    correctCFG->connectNode(CFGNode::node(1), CFGNode::node(2));
    correctCFG->initializeFinalNode(CFGNode::node(2));

    REQUIRE(*createdCFG == *correctCFG);

    EDGES edges = createdCFG->getEdges(1);
    EDGES edges2 = correctCFG->getEdges(1);

    REQUIRE(CFGHead::compareEdgesEquality(edges, edges2));

    REQUIRE(createdCFG->getEdges(2).empty());
    REQUIRE_THROWS_AS(createdCFG->getEdges(3), StatementNumberNotFoundException);

    delete pkbInterface;
    pkbInterface = nullptr;
}
