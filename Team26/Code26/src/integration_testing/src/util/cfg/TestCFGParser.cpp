#include "sp/Parser.h"
#include "catch.hpp"

TEST_CASE("Simple CFG Generation Test") {
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

    PKBInterface pkbInterface = PKBInterface();
    auto cfgManager = std::make_shared<CFGManager>();
    Parser testParser(validSimpleTokens, &pkbInterface, cfgManager);
    testParser.parseSimple();
    CFGHeadPtr createdCFG = cfgManager->getCurrentCFG();

    CFGHeadPtr correctCFG = CFGHead::createNewCFG();
    correctCFG->connectNode(CFGNode::node(1), CFGNode::node(2));
    correctCFG->initializeFinalNode(CFGNode::node(2));

    REQUIRE(*createdCFG == *correctCFG);
}

TEST_CASE("CFG Generation Test - test all simple statements") {
    std::vector<SPToken> v = {SPToken("procedure", SPTokenType::ProcedureToken),
                              SPToken("test", SPTokenType::NameToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("read", SPTokenType::ReadToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken)};

    PKBInterface pkbInterface = PKBInterface();
    auto cfgManager = std::make_shared<CFGManager>();
    Parser testParser(v, &pkbInterface, cfgManager);
    testParser.parseSimple();
    CFGHeadPtr createdCFG = cfgManager->getCurrentCFG();

    CFGHeadPtr correctCFG = CFGHead::createNewCFG();
    correctCFG->connectNode(CFGNode::node(1), CFGNode::node(2));
    correctCFG->connectNode(CFGNode::node(2), CFGNode::node(3));
    correctCFG->initializeFinalNode(CFGNode::node(3));

    REQUIRE(*createdCFG == *correctCFG);
}

TEST_CASE("CFG Generation Test - test calls") {
    std::vector<SPToken> v = {SPToken("procedure", SPTokenType::ProcedureToken),
                              SPToken("dummyProcedure", SPTokenType::NameToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("read", SPTokenType::ReadToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("procedure", SPTokenType::ProcedureToken),
                              SPToken("test", SPTokenType::NameToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("call", SPTokenType::CallToken),
                              SPToken("dummyProcedure", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("read", SPTokenType::ReadToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken)};

    PKBInterface pkbInterface = PKBInterface();
    auto cfgManager = std::make_shared<CFGManager>();
    Parser testParser(v, &pkbInterface, cfgManager);
    testParser.parseSimple();
    CFGHeadPtr createdCFG = cfgManager->getCurrentCFG();

    CFGHeadPtr correctCFG = CFGHead::createNewCFG();
    correctCFG->connectNode(CFGNode::node(2), CFGNode::node(3));
    correctCFG->connectNode(CFGNode::node(3), CFGNode::node(4));
    correctCFG->initializeFinalNode(CFGNode::node(4));

    REQUIRE(*createdCFG == *correctCFG);
}

TEST_CASE("CFG Generation Test - Simple If Statement") {
    std::vector<SPToken> v = {SPToken("procedure", SPTokenType::ProcedureToken),
                              SPToken("test", SPTokenType::NameToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("if", SPTokenType::IfToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("then", SPTokenType::ThenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("else", SPTokenType::ElseToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken)};

    PKBInterface pkbInterface = PKBInterface();
    auto cfgManager = std::make_shared<CFGManager>();
    Parser testParser(v, &pkbInterface, cfgManager);
    testParser.parseSimple();
    CFGHeadPtr createdCFG = cfgManager->getCurrentCFG();

    CFGHeadPtr correctCFG = CFGHead::createNewCFG();
    correctCFG->connectNode(CFGNode::node(1), CFGNode::node(2));
    correctCFG->connectNode(CFGNode::node(1), CFGNode::node(3));
    correctCFG->connectNode(CFGNode::node(2), CFGNode::dummyNode(1));
    correctCFG->connectNode(CFGNode::node(3), CFGNode::dummyNode(1));
    correctCFG->initializeFinalNode(CFGNode::dummyNode(1));

    REQUIRE(*createdCFG == *correctCFG);
}

TEST_CASE("CFG Generation Test - Simple While Statement") {
    std::vector<SPToken> v = {SPToken("procedure", SPTokenType::ProcedureToken),
                              SPToken("test", SPTokenType::NameToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("while", SPTokenType::WhileToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken)};

    PKBInterface pkbInterface = PKBInterface();
    auto cfgManager = std::make_shared<CFGManager>();
    Parser testParser(v, &pkbInterface, cfgManager);
    testParser.parseSimple();
    CFGHeadPtr createdCFG = cfgManager->getCurrentCFG();

    CFGHeadPtr correctCFG = CFGHead::createNewCFG();
    correctCFG->connectNode(CFGNode::node(1), CFGNode::node(2));
    correctCFG->connectNode(CFGNode::node(2), CFGNode::node(1));
    correctCFG->connectNode(CFGNode::node(1), CFGNode::dummyNode(1));
    correctCFG->initializeFinalNode(CFGNode::dummyNode(1));

    REQUIRE(*createdCFG == *correctCFG);
}

TEST_CASE("CFG Generation Test - Advanced nested if/while statements") {
    std::vector<SPToken> v = {SPToken("procedure", SPTokenType::ProcedureToken),
                              SPToken("test", SPTokenType::NameToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("read", SPTokenType::ReadToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("if", SPTokenType::IfToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("then", SPTokenType::ThenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("read", SPTokenType::ReadToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("if", SPTokenType::IfToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("then", SPTokenType::ThenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("else", SPTokenType::ElseToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("else", SPTokenType::ElseToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("while", SPTokenType::WhileToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("while", SPTokenType::WhileToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("if", SPTokenType::IfToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("then", SPTokenType::ThenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("else", SPTokenType::ElseToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken)};

    PKBInterface pkbInterface = PKBInterface();
    auto cfgManager = std::make_shared<CFGManager>();
    Parser testParser(v, &pkbInterface, cfgManager);
    REQUIRE_NOTHROW(testParser.parseSimple());
    CFGHeadPtr createdCFG = cfgManager->getCurrentCFG();

    CFGHeadPtr correctCFG = CFGHead::createNewCFG();
    correctCFG->connectNode(CFGNode::node(1), CFGNode::node(2));
    correctCFG->connectNode(CFGNode::node(2), CFGNode::node(3));
    correctCFG->connectNode(CFGNode::node(3), CFGNode::node(4));
    correctCFG->connectNode(CFGNode::node(4), CFGNode::node(5));
    correctCFG->connectNode(CFGNode::node(5), CFGNode::dummyNode(4));
    correctCFG->connectNode(CFGNode::node(4), CFGNode::node(6));
    correctCFG->connectNode(CFGNode::node(6), CFGNode::dummyNode(4));
    correctCFG->connectNode(CFGNode::dummyNode(4), CFGNode::dummyNode(2));
    correctCFG->connectNode(CFGNode::node(2), CFGNode::node(7));
    correctCFG->connectNode(CFGNode::node(7), CFGNode::node(8));
    correctCFG->connectNode(CFGNode::node(8), CFGNode::node(7));
    correctCFG->connectNode(CFGNode::node(7), CFGNode::dummyNode(7));
    correctCFG->connectNode(CFGNode::dummyNode(7), CFGNode::dummyNode(2));
    correctCFG->connectNode(CFGNode::dummyNode(2), CFGNode::node(9));
    correctCFG->connectNode(CFGNode::node(9), CFGNode::node(10));
    correctCFG->connectNode(CFGNode::node(10), CFGNode::node(11));
    correctCFG->connectNode(CFGNode::node(11), CFGNode::dummyNode(10));
    correctCFG->connectNode(CFGNode::node(10), CFGNode::node(12));
    correctCFG->connectNode(CFGNode::node(12), CFGNode::dummyNode(10));
    correctCFG->connectNode(CFGNode::dummyNode(10), CFGNode::node(9));
    correctCFG->connectNode(CFGNode::node(9), CFGNode::dummyNode(9));
    correctCFG->initializeFinalNode(CFGNode::dummyNode(9));

    REQUIRE(*createdCFG == *correctCFG);
}

TEST_CASE("CFG Generation test - Test while if while while loop") {
    std::vector<SPToken> v = {SPToken("procedure", SPTokenType::ProcedureToken),
                              SPToken("test", SPTokenType::NameToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("while", SPTokenType::WhileToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("read", SPTokenType::ReadToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("read", SPTokenType::ReadToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("read", SPTokenType::ReadToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("if", SPTokenType::IfToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("then", SPTokenType::ThenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("while", SPTokenType::WhileToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("read", SPTokenType::ReadToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("while", SPTokenType::WhileToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("read", SPTokenType::ReadToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("else", SPTokenType::ElseToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("read", SPTokenType::ReadToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
    };
    PKBInterface pkbInterface = PKBInterface();
    auto cfgManager = std::make_shared<CFGManager>();
    Parser testParser(v, &pkbInterface, cfgManager);

    REQUIRE_NOTHROW(testParser.parseSimple());

    CFGHeadPtr createdCFG = cfgManager->getCurrentCFG();

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

//    std::cout << createdCFG->returnAllEdgesInString() << endl;
//    std::cout << correctCFG->returnAllEdgesInString() << endl;

    REQUIRE(*createdCFG == *correctCFG);

    SECTION("Simple Next tests") {
        REQUIRE(createdCFG->isNext(1,2));
        REQUIRE(createdCFG->isNext(5,6));
        REQUIRE(createdCFG->isNext(5,10));
        REQUIRE(createdCFG->isNext(6,1));
    }
}

TEST_CASE("Next test with 3 nesting levels") {
    std::vector<SPToken> v = {SPToken("procedure", SPTokenType::ProcedureToken),
                              SPToken("iloveprofsanka", SPTokenType::NameToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("read", SPTokenType::ReadToken),
                              SPToken("read", SPTokenType::ReadToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("while", SPTokenType::WhileToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken(">=", SPTokenType::RelationToken),
                              SPToken("0", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken("procedure", SPTokenType::ProcedureToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("if", SPTokenType::IfToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("<", SPTokenType::RelationToken),
                              SPToken("50", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("then", SPTokenType::ThenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("if", SPTokenType::IfToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("&&", SPTokenType::CondToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken("<", SPTokenType::RelationToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("then", SPTokenType::ThenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("then", SPTokenType::ThenToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken("-", SPTokenType::OpToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("else", SPTokenType::ElseToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("while", SPTokenType::WhileToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("k", SPTokenType::NameToken),
                              SPToken(">=", SPTokenType::RelationToken),
                              SPToken("0", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("call", SPTokenType::CallToken),
                              SPToken("%", SPTokenType::FactorToken),
                              SPToken("60", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("else", SPTokenType::ElseToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("while", SPTokenType::WhileToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("pencil", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("7", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken("if", SPTokenType::IfToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken("done", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken)
    };

    PKBInterface pkbInterface = PKBInterface();
    auto cfgManager = std::make_shared<CFGManager>();
    Parser testParser(v, &pkbInterface, cfgManager);

    REQUIRE_NOTHROW(testParser.parseSimple());

    CFGHeadPtr createdCFG = cfgManager->getCurrentCFG();

    REQUIRE(createdCFG->isNext(1,2));
    REQUIRE(createdCFG->isNext(2,11));
    REQUIRE(createdCFG->isNext(2,3));
    REQUIRE(createdCFG->isNext(3,4));
    REQUIRE(createdCFG->isNext(4,5));
    REQUIRE(createdCFG->isNext(4,9));
    REQUIRE(createdCFG->isNext(5,6));
    REQUIRE(createdCFG->isNext(5,7));
    REQUIRE(createdCFG->isNext(6,2));
    REQUIRE(createdCFG->isNext(7,8));
    REQUIRE(createdCFG->isNext(7,2));
    REQUIRE(createdCFG->isNext(8,7));
    REQUIRE(createdCFG->isNext(9,10));
    REQUIRE(createdCFG->isNext(9,2));
    REQUIRE(createdCFG->isNext(10,9));
}

TEST_CASE("Next test with 4 nesting levels") {
    std::vector<SPToken> v = {SPToken("procedure", SPTokenType::ProcedureToken),
                              SPToken("iloveprofsanka", SPTokenType::NameToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("read", SPTokenType::ReadToken),
                              SPToken("read", SPTokenType::ReadToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("while", SPTokenType::WhileToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken(">=", SPTokenType::RelationToken),
                              SPToken("0", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken("procedure", SPTokenType::ProcedureToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("if", SPTokenType::IfToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("<", SPTokenType::RelationToken),
                              SPToken("50", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("then", SPTokenType::ThenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("if", SPTokenType::IfToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("&&", SPTokenType::CondToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken("<", SPTokenType::RelationToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("then", SPTokenType::ThenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("then", SPTokenType::ThenToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken("-", SPTokenType::OpToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("else", SPTokenType::ElseToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("if", SPTokenType::IfToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("k", SPTokenType::NameToken),
                              SPToken(">=", SPTokenType::RelationToken),
                              SPToken("0", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("then", SPTokenType::ThenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("call", SPTokenType::CallToken),
                              SPToken("%", SPTokenType::FactorToken),
                              SPToken("60", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("else", SPTokenType::ElseToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("else", SPTokenType::ElseToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("50", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("else", SPTokenType::ElseToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("while", SPTokenType::WhileToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("pencil", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("7", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken("if", SPTokenType::IfToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken("done", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken)
    };

    PKBInterface pkbInterface = PKBInterface();
    auto cfgManager = std::make_shared<CFGManager>();
    Parser testParser(v, &pkbInterface, cfgManager);

    REQUIRE_NOTHROW(testParser.parseSimple());

    CFGHeadPtr createdCFG = cfgManager->getCurrentCFG();

    REQUIRE(createdCFG->isNext(1,2));
    REQUIRE(createdCFG->isNext(2,12));
    REQUIRE(createdCFG->isNext(2,3));
    REQUIRE(createdCFG->isNext(3,4));
    REQUIRE(createdCFG->isNext(4,5));
    REQUIRE(createdCFG->isNext(4,10));
    REQUIRE(createdCFG->isNext(5,6));
    REQUIRE(createdCFG->isNext(5,7));
    REQUIRE(createdCFG->isNext(6,2));
    REQUIRE(createdCFG->isNext(7,8));
    REQUIRE(createdCFG->isNext(7,9));
    REQUIRE_FALSE(createdCFG->isNext(7,2));
    REQUIRE(createdCFG->isNext(8,2));
    REQUIRE(createdCFG->isNext(9,2));
    REQUIRE(createdCFG->isNext(10, 11));
    REQUIRE(createdCFG->isNext(10,2));
    REQUIRE(createdCFG->isNext(11,10));
}