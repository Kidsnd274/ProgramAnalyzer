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
    testParser.parseSimple();
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

    REQUIRE(*createdCFG == *correctCFG);
}
