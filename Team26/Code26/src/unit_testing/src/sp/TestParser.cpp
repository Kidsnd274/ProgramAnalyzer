#include "sp/Parser.h"
#include "catch.hpp"
#include "util/ast/TNode.h"
#include "pkb/PKBInterface.h"
#include <vector>

PKBInterface pkbInterface = PKBInterface();

std::vector<SPToken> validEasySimpleTokens = {SPToken("procedure", SPTokenType::ProcedureToken),
                                            SPToken("test", SPTokenType::NameToken),
                                            SPToken("{", SPTokenType::LCurlyToken),
                                            SPToken("read", SPTokenType::ReadToken),
                                            SPToken("x", SPTokenType::NameToken),
                                            SPToken(";", SPTokenType::SemiColonToken),
                                            SPToken("}", SPTokenType::RCurlyToken)};
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
std::vector<SPToken> invalidSimpleTokens = {SPToken("procedure", SPTokenType::ProcedureToken),
                                          SPToken("test", SPTokenType::NameToken),
                                          SPToken("{", SPTokenType::LCurlyToken),
                                          SPToken("if", SPTokenType::IfToken),
                                          SPToken("(", SPTokenType::LParenToken),
                                          SPToken("x", SPTokenType::NameToken),
                                          SPToken("<", SPTokenType::RelationToken),
                                          SPToken("=", SPTokenType::AssignToken),
                                          SPToken("y", SPTokenType::NameToken),
                                          SPToken(")", SPTokenType::RParenToken),
                                          SPToken("then", SPTokenType::ThenToken),
                                          SPToken("{", SPTokenType::LCurlyToken),
                                          SPToken("read", SPTokenType::ReadToken),
                                          SPToken("x", SPTokenType::NameToken),
                                          SPToken(";", SPTokenType::SemiColonToken),
                                          SPToken("}", SPTokenType::RCurlyToken),
                                          SPToken("else", SPTokenType::ElseToken),
                                          SPToken("{", SPTokenType::LCurlyToken),
                                          SPToken("read", SPTokenType::ReadToken),
                                          SPToken("y", SPTokenType::NameToken),
                                          SPToken(";", SPTokenType::SemiColonToken),
                                          SPToken("}", SPTokenType::RCurlyToken),
                                          SPToken("x", SPTokenType::NameToken),
                                          SPToken("=", SPTokenType::AssignToken),
                                          SPToken("x", SPTokenType::NameToken),
                                          SPToken("+", SPTokenType::OpToken),
                                          SPToken("1", SPTokenType::ConstToken),
                                          SPToken(";", SPTokenType::SemiColonToken),
                                          SPToken("}", SPTokenType::RCurlyToken)};
TEST_CASE("Basic Parser Test with valid program") {
    Parser p(validSimpleTokens, &pkbInterface);
    REQUIRE_NOTHROW(p.parseSimple());
}

TEST_CASE("Basic Parser Test with invalid program") {
    Parser p(invalidSimpleTokens, &pkbInterface);
    REQUIRE_THROWS(p.parseSimple());
}

// TODO need to implement a way to recursive compare StatementNodes/ProcedureNodes
//TEST_CASE("Parse basic procedure") {
//    Parser p(validSimpleTokens);
//    std::shared_ptr<ProcedureNode> actual(nullptr);
//    std::vector<std::shared_ptr<StatementNode>> stmtList = {std::make_shared<ReadNode>(1 , "x")};
//    std::shared_ptr<ProcedureNode> expected = std::make_shared<ProcedureNode>("test", stmtList);
//    REQUIRE_THROWS(actual = p.parseProcedure());
//}

TEST_CASE("Parse Assign") {
    std::vector<SPToken> v = {SPToken("x", SPTokenType::NameToken),
                            SPToken("=", SPTokenType::AssignToken),
                            SPToken("x", SPTokenType::NameToken),
                            SPToken("+", SPTokenType::OpToken),
                            SPToken("1", SPTokenType::ConstToken),
                            SPToken(";", SPTokenType::SemiColonToken)};
    Parser pa(v, &pkbInterface);
    REQUIRE_NOTHROW(pa.parseAssign());
}

TEST_CASE("Parse Print") {
    std::vector<SPToken> v = {SPToken("print", SPTokenType::PrintToken),
                            SPToken("x", SPTokenType::NameToken),
                            SPToken(";", SPTokenType::SemiColonToken)};
    Parser pp(v, &pkbInterface);
    REQUIRE_NOTHROW(pp.parsePrint());
}

TEST_CASE("Parse Read") {
    std::vector<SPToken> v = {SPToken("read", SPTokenType::PrintToken),
                            SPToken("x", SPTokenType::NameToken),
                            SPToken(";", SPTokenType::SemiColonToken)};
    Parser pr(v, &pkbInterface);
    REQUIRE_NOTHROW(pr.parseRead());
}

TEST_CASE("Parse Expression") {
    SECTION("1 operator") {
        std::vector<SPToken> v = {SPToken("x", SPTokenType::NameToken),
                                SPToken("+", SPTokenType::OpToken),
                                SPToken("1", SPTokenType::ConstToken),
                                SPToken(";", SPTokenType::SemiColonToken)};
        Parser pr(v, &pkbInterface);
        std::shared_ptr<TNode> expected =
                TNode::createTerm(1, "+", TNode::createVariableName(1, "x"), TNode::createConstantValue(1, "1"));
        std::shared_ptr<TNode> actual(nullptr);
        REQUIRE_NOTHROW(actual = pr.parseExpression());
        REQUIRE(TNode::isSameTree(expected, actual));
    }

    SECTION("2 operators") {
        std::vector<SPToken> v = {SPToken("x", SPTokenType::NameToken),
                                SPToken("+", SPTokenType::OpToken),
                                SPToken("y", SPTokenType::NameToken),
                                SPToken("*", SPTokenType::FactorToken),
                                SPToken("3", SPTokenType::ConstToken),
                                SPToken(";", SPTokenType::SemiColonToken)};

        std::shared_ptr<TNode> expected =
                TNode::createTerm(1, "+", TNode::createVariableName(1, "x"),
                                  TNode::createTerm(1, "*",TNode::createVariableName(1, "y"),
                                                    TNode::createConstantValue(1, "3")));
        std::shared_ptr<TNode> actual(nullptr);
        Parser pr(v, &pkbInterface);
        REQUIRE_NOTHROW(actual = pr.parseExpression());
        REQUIRE(TNode::isSameTree(expected, actual));
    }

    SECTION("3 operators") {
        std::vector<SPToken> v = {SPToken("z", SPTokenType::NameToken),
                                SPToken("*", SPTokenType::FactorToken),
                                SPToken("x", SPTokenType::NameToken),
                                SPToken("+", SPTokenType::OpToken),
                                SPToken("y", SPTokenType::NameToken),
                                SPToken("/", SPTokenType::FactorToken),
                                SPToken("3", SPTokenType::ConstToken),
                                SPToken(";", SPTokenType::SemiColonToken)};
        std::shared_ptr<TNode> expected =
                TNode::createTerm(1, "+", TNode::createTerm(1, "*", TNode::createVariableName(1, "z"),
                                                            TNode::createVariableName(1, "x")),
                                  TNode::createTerm(1, "/",TNode::createVariableName(1, "y"),
                                                    TNode::createConstantValue(1, "3")));
        std::shared_ptr<TNode> actual(nullptr);
        Parser pr(v, &pkbInterface);
        REQUIRE_NOTHROW(actual = pr.parseExpression());
        REQUIRE(TNode::isSameTree(expected, actual));
    }

    SECTION("3 operators with minus") {
        std::vector<SPToken> v = {SPToken("z", SPTokenType::NameToken),
                                SPToken("-", SPTokenType::FactorToken),
                                SPToken("x", SPTokenType::NameToken),
                                SPToken("+", SPTokenType::OpToken),
                                SPToken("y", SPTokenType::NameToken),
                                SPToken("/", SPTokenType::FactorToken),
                                SPToken("3", SPTokenType::ConstToken),
                                SPToken(";", SPTokenType::SemiColonToken)};
        std::shared_ptr<TNode> expected =
                TNode::createTerm(1, "+", TNode::createTerm(1, "-", TNode::createVariableName(1, "z"),
                                                            TNode::createVariableName(1, "x")),
                                  TNode::createTerm(1, "/",TNode::createVariableName(1, "y"),
                                                    TNode::createConstantValue(1, "3")));
        std::shared_ptr<TNode> actual(nullptr);
        Parser pr(v, &pkbInterface);
        REQUIRE_NOTHROW(actual = pr.parseExpression());
        REQUIRE(TNode::isSameTree(expected, actual));
    }
    //TODO this test case is broken... should not accept this
//    SECTION("1 operator but invalid") {
//        std::vector<SPToken> v = {SPToken("x", SPTokenType::NameToken),
//                                SPToken("y", SPTokenType::NameToken),
//                                SPToken("+", SPTokenType::OpToken),
//                                SPToken("1", SPTokenType::ConstToken),
//                                SPToken(";", SPTokenType::SemiColonToken)};
//        Parser pr(v);
//        REQUIRE_NOTHROW(pr.parseExpression());
//    }
}

TEST_CASE("Parse If") {
    std::vector<SPToken> v = {SPToken("if", SPTokenType::IfToken),
                            SPToken("(", SPTokenType::LParenToken),
                            SPToken("x", SPTokenType::NameToken),
                            SPToken("<", SPTokenType::RelationToken),
                            SPToken("y", SPTokenType::NameToken),
                            SPToken(")", SPTokenType::RParenToken),
                            SPToken("then", SPTokenType::ThenToken),
                            SPToken("{", SPTokenType::LCurlyToken),
                            SPToken("read", SPTokenType::ReadToken),
                            SPToken("x", SPTokenType::NameToken),
                            SPToken(";", SPTokenType::SemiColonToken),
                            SPToken("}", SPTokenType::RCurlyToken),
                            SPToken("else", SPTokenType::ElseToken),
                            SPToken("{", SPTokenType::LCurlyToken),
                            SPToken("print", SPTokenType::ReadToken),
                            SPToken("y", SPTokenType::NameToken),
                            SPToken(";", SPTokenType::SemiColonToken),
                            SPToken("}", SPTokenType::RCurlyToken)};
    Parser pr(v, &pkbInterface);
    REQUIRE_NOTHROW(pr.parseIf());
}

TEST_CASE("Parse While") {
    std::vector<SPToken> v = {SPToken("while", SPTokenType::WhileToken),
                            SPToken("(", SPTokenType::LParenToken),
                            SPToken("x", SPTokenType::NameToken),
                            SPToken("<=", SPTokenType::RelationToken),
                            SPToken("y", SPTokenType::NameToken),
                            SPToken(")", SPTokenType::RParenToken),
                            SPToken("{", SPTokenType::LCurlyToken),
                            SPToken("read", SPTokenType::ReadToken),
                            SPToken("x", SPTokenType::NameToken),
                            SPToken(";", SPTokenType::SemiColonToken),
                            SPToken("}", SPTokenType::RCurlyToken)};
    Parser pr(v, &pkbInterface);
    REQUIRE_NOTHROW(pr.parseWhile());
}

TEST_CASE("Parse Call") {
    std::vector<SPToken> v = {SPToken("call", SPTokenType::CallToken),
                            SPToken("DummyProcedure", SPTokenType::NameToken),
                            SPToken(";", SPTokenType::SemiColonToken),};
    Parser pr(v, &pkbInterface);
    REQUIRE_NOTHROW(pr.parseCall());
}

TEST_CASE("Parse Cond") {
    SECTION("Simple Condition") {
        std::vector<SPToken> v = {SPToken("x", SPTokenType::NameToken),
                                SPToken("<=", SPTokenType::RelationToken),
                                SPToken("y", SPTokenType::NameToken)};
        Parser pr(v, &pkbInterface);
        REQUIRE_NOTHROW(pr.parseCond());
    }

    SECTION("Negation Condition") {
        std::vector<SPToken> v = {SPToken("!", SPTokenType::CondToken),
                                SPToken("(", SPTokenType::LParenToken),
                                SPToken("x", SPTokenType::NameToken),
                                SPToken("<=", SPTokenType::RelationToken),
                                SPToken("y", SPTokenType::NameToken),
                                SPToken(")", SPTokenType::RParenToken)};
        Parser pr(v, &pkbInterface);
        REQUIRE_NOTHROW(pr.parseCond());
    }

    SECTION("invalid Cond at the front") {
        std::vector<SPToken> v = {SPToken("||", SPTokenType::CondToken),
                                SPToken("(", SPTokenType::LParenToken),
                                SPToken("x", SPTokenType::NameToken),
                                SPToken("<=", SPTokenType::RelationToken),
                                SPToken("y", SPTokenType::NameToken),
                                SPToken(")", SPTokenType::RParenToken)};
        Parser pr(v, &pkbInterface);
        REQUIRE_THROWS(pr.parseCond());
    }

    SECTION("And Condition") {
        std::vector<SPToken> v = {SPToken("(", SPTokenType::LParenToken),
                                SPToken("!", SPTokenType::CondToken),
                                SPToken("(", SPTokenType::LParenToken),
                                SPToken("x", SPTokenType::NameToken),
                                SPToken("<=", SPTokenType::RelationToken),
                                SPToken("y", SPTokenType::NameToken),
                                SPToken(")", SPTokenType::RParenToken),
                                SPToken(")", SPTokenType::RParenToken),
                                SPToken("&&", SPTokenType::CondToken),
                                SPToken("(", SPTokenType::LParenToken),
                                SPToken("z", SPTokenType::NameToken),
                                SPToken(">", SPTokenType::RelationToken),
                                SPToken("y", SPTokenType::NameToken),
                                SPToken(")", SPTokenType::RParenToken)};
        Parser pr(v, &pkbInterface);
        REQUIRE_NOTHROW(pr.parseCond());
    }

    SECTION("And Condition") {
        std::vector<SPToken> v = {SPToken("(", SPTokenType::LParenToken),
                                SPToken("!", SPTokenType::CondToken),
                                SPToken("(", SPTokenType::LParenToken),
                                SPToken("x", SPTokenType::NameToken),
                                SPToken("<=", SPTokenType::RelationToken),
                                SPToken("y", SPTokenType::NameToken),
                                SPToken(")", SPTokenType::RParenToken),
                                SPToken(")", SPTokenType::RParenToken),
                                SPToken("||", SPTokenType::CondToken),
                                SPToken("(", SPTokenType::LParenToken),
                                SPToken("z", SPTokenType::NameToken),
                                SPToken(">", SPTokenType::RelationToken),
                                SPToken("y", SPTokenType::NameToken),
                                SPToken(")", SPTokenType::RParenToken)};
        Parser pr(v, &pkbInterface);
        REQUIRE_NOTHROW(pr.parseCond());
    }
}
