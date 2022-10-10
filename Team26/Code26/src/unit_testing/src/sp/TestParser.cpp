#include "sp/Parser.h"
#include "catch.hpp"
#include "util/ast/TNode.h"
#include "./stubs/PKBInterfaceStubForDE.h"
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

std::vector<SPToken> testFollowsStar = {SPToken("procedure", SPTokenType::ProcedureToken),
                                          SPToken("milestone1NestLevel1", SPTokenType::NameToken),
                                          SPToken("{", SPTokenType::LCurlyToken),
                                          SPToken("x", SPTokenType::NameToken),
                                          SPToken("=", SPTokenType::AssignToken),
                                          SPToken("x", SPTokenType::NameToken),
                                          SPToken("+", SPTokenType::OpToken),
                                          SPToken("1", SPTokenType::ConstToken),
                                          SPToken(";", SPTokenType::SemiColonToken),
                                          SPToken("print", SPTokenType::PrintToken),
                                          SPToken("y", SPTokenType::NameToken),
                                          SPToken(";", SPTokenType::SemiColonToken),
                                          SPToken("read", SPTokenType::ReadToken),
                                          SPToken("y", SPTokenType::NameToken),
                                          SPToken(";", SPTokenType::SemiColonToken),
                                          SPToken("if", SPTokenType::IfToken),
                                          SPToken("(", SPTokenType::LParenToken),
                                          SPToken("x", SPTokenType::NameToken),
                                          SPToken("<", SPTokenType::RelationToken),
                                          SPToken("1", SPTokenType::ConstToken),
                                          SPToken(")", SPTokenType::RParenToken),
                                          SPToken("then", SPTokenType::ThenToken),
                                          SPToken("{", SPTokenType::LCurlyToken),
                                          SPToken("x", SPTokenType::NameToken),
                                          SPToken("=", SPTokenType::AssignToken),
                                          SPToken("x", SPTokenType::NameToken),
                                          SPToken("+", SPTokenType::OpToken),
                                          SPToken("1", SPTokenType::ConstToken),
                                          SPToken(";", SPTokenType::SemiColonToken),
                                          SPToken("print", SPTokenType::PrintToken),
                                          SPToken("y", SPTokenType::NameToken),
                                          SPToken(";", SPTokenType::SemiColonToken),
                                          SPToken("read", SPTokenType::ReadToken),
                                          SPToken("y", SPTokenType::NameToken),
                                          SPToken(";", SPTokenType::SemiColonToken),
                                          SPToken("}", SPTokenType::RCurlyToken),
                                          SPToken("else", SPTokenType::ElseToken),
                                          SPToken("{", SPTokenType::LCurlyToken),
                                          SPToken("print", SPTokenType::PrintToken),
                                          SPToken("y", SPTokenType::NameToken),
                                          SPToken(";", SPTokenType::SemiColonToken),
                                          SPToken("x", SPTokenType::NameToken),
                                          SPToken("=", SPTokenType::AssignToken),
                                          SPToken("x", SPTokenType::NameToken),
                                          SPToken("+", SPTokenType::OpToken),
                                          SPToken("1", SPTokenType::ConstToken),
                                          SPToken(";", SPTokenType::SemiColonToken),
                                          SPToken("read", SPTokenType::ReadToken),
                                          SPToken("y", SPTokenType::NameToken),
                                          SPToken(";", SPTokenType::SemiColonToken),
                                          SPToken("}", SPTokenType::RCurlyToken),
                                          SPToken("while", SPTokenType::WhileToken),
                                          SPToken("(", SPTokenType::LParenToken),
                                          SPToken("x", SPTokenType::NameToken),
                                          SPToken("<", SPTokenType::RelationToken),
                                          SPToken("1", SPTokenType::ConstToken),
                                          SPToken(")", SPTokenType::RParenToken),
                                          SPToken("{", SPTokenType::LCurlyToken),
                                          SPToken("x", SPTokenType::NameToken),
                                          SPToken("=", SPTokenType::AssignToken),
                                          SPToken("x", SPTokenType::NameToken),
                                          SPToken("+", SPTokenType::OpToken),
                                          SPToken("1", SPTokenType::ConstToken),
                                          SPToken(";", SPTokenType::SemiColonToken),
                                          SPToken("print", SPTokenType::PrintToken),
                                          SPToken("y", SPTokenType::NameToken),
                                          SPToken(";", SPTokenType::SemiColonToken),
                                          SPToken("read", SPTokenType::ReadToken),
                                          SPToken("y", SPTokenType::NameToken),
                                          SPToken(";", SPTokenType::SemiColonToken),
                                          SPToken("}", SPTokenType::RCurlyToken),
                                          SPToken("}", SPTokenType::RCurlyToken)};

std::vector<SPToken> testVariableNamesAreKeywords = {
        SPToken("procedure", SPTokenType::ProcedureToken),
        SPToken("procedure", SPTokenType::ProcedureToken),
        SPToken("{", SPTokenType::LCurlyToken),
        SPToken("print", SPTokenType::PrintToken),
        SPToken("=", SPTokenType::AssignToken),
        SPToken("read", SPTokenType::ReadToken),
        SPToken("+", SPTokenType::OpToken),
        SPToken("1", SPTokenType::ConstToken),
        SPToken(";", SPTokenType::SemiColonToken),
        SPToken("read", SPTokenType::ReadToken),
        SPToken("print", SPTokenType::PrintToken),
        SPToken(";", SPTokenType::SemiColonToken),
        SPToken("print", SPTokenType::PrintToken),
        SPToken("read", SPTokenType::ReadToken),
        SPToken(";", SPTokenType::SemiColonToken),
        SPToken("if", SPTokenType::IfToken),
        SPToken("(", SPTokenType::LParenToken),
        SPToken("if", SPTokenType::IfToken),
        SPToken(">", SPTokenType::RelationToken),
        SPToken("1", SPTokenType::ConstToken),
        SPToken(")", SPTokenType::RParenToken),
        SPToken("then", SPTokenType::ThenToken),
        SPToken("{", SPTokenType::LCurlyToken),
        SPToken("else", SPTokenType::ElseToken),
        SPToken("=", SPTokenType::AssignToken),
        SPToken("else", SPTokenType::ElseToken),
        SPToken("+", SPTokenType::OpToken),
        SPToken("1", SPTokenType::ConstToken),
        SPToken(";", SPTokenType::SemiColonToken),
        SPToken("}", SPTokenType::RCurlyToken),
        SPToken("else", SPTokenType::ElseToken),
        SPToken("{", SPTokenType::LCurlyToken),
        SPToken("if", SPTokenType::IfToken),
        SPToken("=", SPTokenType::AssignToken),
        SPToken("if", SPTokenType::IfToken),
        SPToken("+", SPTokenType::OpToken),
        SPToken("1", SPTokenType::ConstToken),
        SPToken(";", SPTokenType::SemiColonToken),
        SPToken("}", SPTokenType::RCurlyToken),
        SPToken("while", SPTokenType::WhileToken),
        SPToken("(", SPTokenType::LParenToken),
        SPToken("while", SPTokenType::WhileToken),
        SPToken(">", SPTokenType::RelationToken),
        SPToken("1", SPTokenType::ConstToken),
        SPToken(")", SPTokenType::RParenToken),
        SPToken("{", SPTokenType::LCurlyToken),
        SPToken("while", SPTokenType::WhileToken),
        SPToken("=", SPTokenType::AssignToken),
        SPToken("while", SPTokenType::WhileToken),
        SPToken("+", SPTokenType::OpToken),
        SPToken("1", SPTokenType::ConstToken),
        SPToken(";", SPTokenType::SemiColonToken),
        SPToken("}", SPTokenType::RCurlyToken),
        SPToken("}", SPTokenType::RCurlyToken)
};

TEST_CASE("Basic Parser Test with valid program with keywords as variable names") {
    Parser p(testVariableNamesAreKeywords, &pkbInterface);
    REQUIRE_NOTHROW(p.parseSimple());
}

TEST_CASE("Basic Parser Test with valid program") {
    Parser p(validSimpleTokens, &pkbInterface);
    REQUIRE_NOTHROW(p.parseSimple());
}

TEST_CASE("Basic Parser Test with invalid program") {
    Parser p(invalidSimpleTokens, &pkbInterface);
    REQUIRE_THROWS(p.parseSimple());
}

TEST_CASE("Testing Follows*") {
    auto *pkbInterfaceStub = new PKBInterfaceStubForDE();
    Parser p(testFollowsStar, pkbInterfaceStub);
    REQUIRE_NOTHROW(p.parseSimple());
    REQUIRE(pkbInterfaceStub->statements[1] == pkbInterfaceStub->statements[2]);
    REQUIRE(pkbInterfaceStub->statements[2] == pkbInterfaceStub->statements[3]);
    REQUIRE(pkbInterfaceStub->statements[3] == pkbInterfaceStub->statements[4]);
    REQUIRE_FALSE(pkbInterfaceStub->statements[4] == pkbInterfaceStub->statements[5]);
    REQUIRE(pkbInterfaceStub->statements[4] == pkbInterfaceStub->statements[11]);
    REQUIRE(pkbInterfaceStub->statements[5] == pkbInterfaceStub->statements[6]);
    REQUIRE(pkbInterfaceStub->statements[6] == pkbInterfaceStub->statements[7]);
    REQUIRE_FALSE(pkbInterfaceStub->statements[7] == pkbInterfaceStub->statements[8]);
    REQUIRE(pkbInterfaceStub->statements[8] == pkbInterfaceStub->statements[9]);
    REQUIRE(pkbInterfaceStub->statements[9] == pkbInterfaceStub->statements[10]);
    REQUIRE_FALSE(pkbInterfaceStub->statements[10] == pkbInterfaceStub->statements[1]);
    REQUIRE_FALSE(pkbInterfaceStub->statements[10] == pkbInterfaceStub->statements[11]);
    REQUIRE_FALSE(pkbInterfaceStub->statements[10] == pkbInterfaceStub->statements[13]);
    REQUIRE(pkbInterfaceStub->statements[12] == pkbInterfaceStub->statements[13]);
    REQUIRE(pkbInterfaceStub->statements[13] == pkbInterfaceStub->statements[14]);
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
    SECTION("variable names not keywords") {
        std::vector<SPToken> v = {SPToken("x", SPTokenType::NameToken),
                                  SPToken("=", SPTokenType::AssignToken),
                                  SPToken("x", SPTokenType::NameToken),
                                  SPToken("+", SPTokenType::OpToken),
                                  SPToken("1", SPTokenType::ConstToken),
                                  SPToken(";", SPTokenType::SemiColonToken)};
        Parser pa(v, &pkbInterface);
        REQUIRE_NOTHROW(pa.parseAssign(1));
    }

    SECTION("variable names are keywords") {
        std::vector<SPToken> v = {SPToken("read", SPTokenType::ReadToken),
                                  SPToken("=", SPTokenType::AssignToken),
                                  SPToken("while", SPTokenType::WhileToken),
                                  SPToken("+", SPTokenType::OpToken),
                                  SPToken("1", SPTokenType::ConstToken),
                                  SPToken(";", SPTokenType::SemiColonToken)};
        Parser pa(v, &pkbInterface);
        REQUIRE_NOTHROW(pa.parseAssign(1));
    }
}

TEST_CASE("Parse Print") {
    SECTION("variable names not keywords") {
        std::vector<SPToken> v = {SPToken("print", SPTokenType::PrintToken),
                                  SPToken("x", SPTokenType::NameToken),
                                  SPToken(";", SPTokenType::SemiColonToken)};
        Parser pp(v, &pkbInterface);
        REQUIRE_NOTHROW(pp.parsePrint(1));
    }

    SECTION("variable names are keywords") {
        std::vector<SPToken> v = {SPToken("print", SPTokenType::PrintToken),
                                  SPToken("if", SPTokenType::IfToken),
                                  SPToken(";", SPTokenType::SemiColonToken)};
        Parser pp(v, &pkbInterface);
        REQUIRE_NOTHROW(pp.parsePrint(1));
    }
}

TEST_CASE("Parse Read") {
    SECTION("variable names not keywords") {
        std::vector<SPToken> v = {SPToken("read", SPTokenType::ReadToken),
                                  SPToken("x", SPTokenType::NameToken),
                                  SPToken(";", SPTokenType::SemiColonToken)};
        Parser pr(v, &pkbInterface);
        REQUIRE_NOTHROW(pr.parseRead(1));
    }

    SECTION("variable names are keywords") {
        std::vector<SPToken> v = {SPToken("read", SPTokenType::ReadToken),
                                  SPToken("print", SPTokenType::PrintToken),
                                  SPToken(";", SPTokenType::SemiColonToken)};
        Parser pr(v, &pkbInterface);
        REQUIRE_NOTHROW(pr.parseRead(1));
    }
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
                            SPToken("print", SPTokenType::PrintToken),
                            SPToken("y", SPTokenType::NameToken),
                            SPToken(";", SPTokenType::SemiColonToken),
                            SPToken("}", SPTokenType::RCurlyToken)};
    Parser pr(v, &pkbInterface);
    REQUIRE_NOTHROW(pr.parseIf(1));
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
    REQUIRE_NOTHROW(pr.parseWhile(1));
}

TEST_CASE("Parse Call") {
    SECTION("No semantic Error") {
        std::vector<SPToken> v = {SPToken("procedure", SPTokenType::ProcedureToken),
                                  SPToken("testCall", SPTokenType::NameToken),
                                  SPToken("{", SPTokenType::LCurlyToken),
                                  SPToken("call", SPTokenType::CallToken),
                                  SPToken("DummyProcedure", SPTokenType::NameToken),
                                  SPToken(";", SPTokenType::SemiColonToken),
                                  SPToken("}", SPTokenType::RCurlyToken),
                                  SPToken("procedure", SPTokenType::ProcedureToken),
                                  SPToken("DummyProcedure", SPTokenType::NameToken),
                                  SPToken("{", SPTokenType::LCurlyToken),
                                  SPToken("read", SPTokenType::ReadToken),
                                  SPToken("x", SPTokenType::NameToken),
                                  SPToken(";", SPTokenType::SemiColonToken),
                                  SPToken("}", SPTokenType::RCurlyToken)};
        Parser pr(v, &pkbInterface);
        REQUIRE_NOTHROW(pr.parseSimple());
    }

    SECTION("SEMANTIC ERROR: call to non-existent procedure") {
        std::vector<SPToken> v = {SPToken("procedure", SPTokenType::ProcedureToken),
                                  SPToken("testCall", SPTokenType::NameToken),
                                  SPToken("{", SPTokenType::LCurlyToken),
                                  SPToken("call", SPTokenType::CallToken),
                                  SPToken("DummyProcedure", SPTokenType::NameToken),
                                  SPToken(";", SPTokenType::SemiColonToken),
                                  SPToken("}", SPTokenType::RCurlyToken),
                                  SPToken("procedure", SPTokenType::ProcedureToken),
                                  SPToken("test1", SPTokenType::NameToken),
                                  SPToken("{", SPTokenType::LCurlyToken),
                                  SPToken("read", SPTokenType::ReadToken),
                                  SPToken("x", SPTokenType::NameToken),
                                  SPToken(";", SPTokenType::SemiColonToken),
                                  SPToken("}", SPTokenType::RCurlyToken)};
        Parser pr(v, &pkbInterface);
        REQUIRE_THROWS_AS(pr.parseSimple(), SemanticErrorException);
    }

    SECTION("SEMANTIC ERROR: recursive call") {
        std::vector<SPToken> v = {SPToken("procedure", SPTokenType::ProcedureToken),
                                  SPToken("testCall", SPTokenType::NameToken),
                                  SPToken("{", SPTokenType::LCurlyToken),
                                  SPToken("call", SPTokenType::CallToken),
                                  SPToken("DummyProcedure", SPTokenType::NameToken),
                                  SPToken(";", SPTokenType::SemiColonToken),
                                  SPToken("}", SPTokenType::RCurlyToken),
                                  SPToken("procedure", SPTokenType::ProcedureToken),
                                  SPToken("DummyProcedure", SPTokenType::NameToken),
                                  SPToken("{", SPTokenType::LCurlyToken),
                                  SPToken("call", SPTokenType::CallToken),
                                  SPToken("DummyProcedure", SPTokenType::NameToken),
                                  SPToken(";", SPTokenType::SemiColonToken),
                                  SPToken("}", SPTokenType::RCurlyToken)};
        Parser pr(v, &pkbInterface);
        REQUIRE_THROWS_AS(pr.parseSimple(), SemanticErrorException);
    }

    SECTION("SEMANTIC ERROR: cyclic call") {
        std::vector<SPToken> v = {SPToken("procedure", SPTokenType::ProcedureToken),
                                  SPToken("testCall", SPTokenType::NameToken),
                                  SPToken("{", SPTokenType::LCurlyToken),
                                  SPToken("call", SPTokenType::CallToken),
                                  SPToken("DummyProcedure", SPTokenType::NameToken),
                                  SPToken(";", SPTokenType::SemiColonToken),
                                  SPToken("}", SPTokenType::RCurlyToken),
                                  SPToken("procedure", SPTokenType::ProcedureToken),
                                  SPToken("DummyProcedure", SPTokenType::NameToken),
                                  SPToken("{", SPTokenType::LCurlyToken),
                                  SPToken("call", SPTokenType::CallToken),
                                  SPToken("cyclicTest", SPTokenType::NameToken),
                                  SPToken(";", SPTokenType::SemiColonToken),
                                  SPToken("}", SPTokenType::RCurlyToken),
                                  SPToken("procedure", SPTokenType::ProcedureToken),
                                  SPToken("cyclicTest", SPTokenType::NameToken),
                                  SPToken("{", SPTokenType::LCurlyToken),
                                  SPToken("call", SPTokenType::CallToken),
                                  SPToken("testCall", SPTokenType::NameToken),
                                  SPToken(";", SPTokenType::SemiColonToken),
                                  SPToken("}", SPTokenType::RCurlyToken)};
        Parser pr(v, &pkbInterface);
        REQUIRE_THROWS_AS(pr.parseSimple(), SemanticErrorException);
    }
}

TEST_CASE("Parse Cond") {
    SECTION("Simple Condition") {
        std::vector<SPToken> v = {SPToken("x", SPTokenType::NameToken),
                                SPToken("<=", SPTokenType::RelationToken),
                                SPToken("y", SPTokenType::NameToken),
                                SPToken(")", SPTokenType::RParenToken)};
        Parser pr(v, &pkbInterface);
        REQUIRE_NOTHROW(pr.parseCond());
    }

    SECTION("Harder Condition") {
        std::vector<SPToken> v = {SPToken("x", SPTokenType::NameToken),
                                  SPToken("+", SPTokenType::OpToken),
                                  SPToken("y", SPTokenType::NameToken),
                                  SPToken("*", SPTokenType::FactorToken),
                                  SPToken("3", SPTokenType::ConstToken),
                                  SPToken("<=", SPTokenType::RelationToken),
                                  SPToken("y", SPTokenType::NameToken),
                                  SPToken("-", SPTokenType::OpToken),
                                  SPToken("z", SPTokenType::NameToken),
                                  SPToken("/", SPTokenType::FactorToken),
                                  SPToken("test1", SPTokenType::NameToken),
                                  SPToken(")", SPTokenType::RParenToken)};
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

TEST_CASE("Test Parsing Expression and retrieving TNode using static method") {
    SECTION("Simple Test") {
        std::string exprString = "x + 1;";

        std::shared_ptr<TNode> correctTNode = TNode::createTerm(1, "+", TNode::createVariableName(1, "x"), TNode::createConstantValue(1, "1"));
        std::shared_ptr<TNode> generatedTNode = Parser::parseExpressionFromString(exprString);

        REQUIRE(TNode::isSameTree(correctTNode, generatedTNode));
    }

    SECTION("Slightly more advanced test") {
        std::string exprString = "1 + x * 4 * 8 + 12;";

        std::shared_ptr<TNode> node1 = TNode::createTerm(1, "*", TNode::createVariableName(1, "x"), TNode::createConstantValue(1, "4"));
        std::shared_ptr<TNode> node2 = TNode::createTerm(1, "*", node1, TNode::createConstantValue(1, "8"));
        std::shared_ptr<TNode> node3 = TNode::createTerm(1, "+", TNode::createConstantValue(1, "1"), node2);
        std::shared_ptr<TNode> correctTNode = TNode::createTerm(1, "+", node3, TNode::createConstantValue(1, "12"));
        std::shared_ptr<TNode> generatedTNode = Parser::parseExpressionFromString(exprString);

        REQUIRE(TNode::isSameTree(correctTNode, generatedTNode));
    }
}
