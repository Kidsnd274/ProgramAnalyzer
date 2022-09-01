#include "sp/Parser.h"
#include "catch.hpp"
#include <vector>

std::vector<Token> validEasySimpleTokens = {Token("procedure", TokenType::ProcedureToken),
                                            Token("test", TokenType::NameToken),
                                            Token("{", TokenType::LCurlyToken),
                                            Token("read", TokenType::ReadToken),
                                            Token("x", TokenType::NameToken),
                                            Token(";", TokenType::SemiColonToken),
                                            Token("}", TokenType::RCurlyToken)};
std::vector<Token> validSimpleTokens = {Token("procedure", TokenType::ProcedureToken),
                                        Token("test", TokenType::NameToken),
                                        Token("{", TokenType::LCurlyToken),
                                        Token("read", TokenType::ReadToken),
                                        Token("x", TokenType::NameToken),
                                        Token(";", TokenType::SemiColonToken),
                                        Token("x", TokenType::NameToken),
                                        Token("=", TokenType::AssignToken),
                                        Token("x", TokenType::NameToken),
                                        Token("+", TokenType::OpToken),
                                        Token("1", TokenType::ConstToken),
                                        Token(";", TokenType::SemiColonToken),
                                        Token("}", TokenType::RCurlyToken)};
std::vector<Token> invalidSimpleTokens = {Token("procedure", TokenType::ProcedureToken),
                                          Token("test", TokenType::NameToken),
                                          Token("{", TokenType::LCurlyToken),
                                          Token("if", TokenType::IfToken),
                                          Token("(", TokenType::LParenToken),
                                          Token("x", TokenType::NameToken),
                                          Token("<", TokenType::RelationToken),
                                          Token("=", TokenType::AssignToken),
                                          Token("y", TokenType::NameToken),
                                          Token(")", TokenType::RParenToken),
                                          Token("then", TokenType::ThenToken),
                                          Token("{", TokenType::LCurlyToken),
                                          Token("read", TokenType::ReadToken),
                                          Token("x", TokenType::NameToken),
                                          Token(";", TokenType::SemiColonToken),
                                          Token("}", TokenType::RCurlyToken),
                                          Token("else", TokenType::ElseToken),
                                          Token("{", TokenType::LCurlyToken),
                                          Token("read", TokenType::ReadToken),
                                          Token("y", TokenType::NameToken),
                                          Token(";", TokenType::SemiColonToken),
                                          Token("}", TokenType::RCurlyToken),
                                          Token("x", TokenType::NameToken),
                                          Token("=", TokenType::AssignToken),
                                          Token("x", TokenType::NameToken),
                                          Token("+", TokenType::OpToken),
                                          Token("1", TokenType::ConstToken),
                                          Token(";", TokenType::SemiColonToken),
                                          Token("}", TokenType::RCurlyToken)};
TEST_CASE("Basic Parser Test with valid program", "This is to make sure that the current minimal parser does not throw a syntax error") {
    Parser p(validSimpleTokens);
    REQUIRE_NOTHROW(p.parseSimple());
}

TEST_CASE("Basic Parser Test with invalid program", "This is to make sure that the current minimal parser does throw a syntax error") {
    Parser p(invalidSimpleTokens);
    REQUIRE_THROWS(p.parseSimple());
}

TEST_CASE("Parse Assign") {
    std::vector<Token> v = {Token("x", TokenType::NameToken),
                            Token("=", TokenType::AssignToken),
                            Token("x", TokenType::NameToken),
                            Token("+", TokenType::OpToken),
                            Token("1", TokenType::ConstToken),
                            Token(";", TokenType::SemiColonToken)};
    std::unordered_set<std::string> var = {"x"};
    std::unordered_set<std::string> cons = {"1"};
    Parser pa(v);
    REQUIRE_NOTHROW(pa.parseAssign());
    REQUIRE(var == pa.variables);
    REQUIRE(cons == pa.constants);
}

TEST_CASE("Parse Print") {
    std::vector<Token> v = {Token("print", TokenType::PrintToken),
                            Token("x", TokenType::NameToken),
                            Token(";", TokenType::SemiColonToken)};
    std::unordered_set<std::string> var = {"x"};
    Parser pp(v);
    REQUIRE_NOTHROW(pp.parsePrint());
    REQUIRE(var == pp.variables);
}

TEST_CASE("Parse Read") {
    std::vector<Token> v = {Token("read", TokenType::PrintToken),
                            Token("x", TokenType::NameToken),
                            Token(";", TokenType::SemiColonToken)};
    std::unordered_set<std::string> var = {"x"};
    Parser pr(v);
    REQUIRE_NOTHROW(pr.parseRead());
    REQUIRE(var == pr.variables);
}

TEST_CASE("Parse Expression") {
    SECTION("1 operator") {
        std::vector<Token> v = {Token("x", TokenType::NameToken),
                                Token("+", TokenType::OpToken),
                                Token("1", TokenType::ConstToken)};
        std::unordered_set<std::string> var = {"x"};
        std::unordered_set<std::string> cons = {"1"};
        Parser pr(v);
        REQUIRE_NOTHROW(pr.parseExpression());
        REQUIRE(var == pr.variables);
        REQUIRE(cons == pr.constants);
    }

    SECTION("2 operators") {
        std::vector<Token> v = {Token("x", TokenType::NameToken),
                                Token("+", TokenType::OpToken),
                                Token("y", TokenType::NameToken),
                                Token("*", TokenType::FactorToken),
                                Token("3", TokenType::ConstToken)};
        std::unordered_set<std::string> var = {"x", "y"};
        std::unordered_set<std::string> cons = {"3"};
        Parser pr(v);
        REQUIRE_NOTHROW(pr.parseExpression());
        REQUIRE(var == pr.variables);
        REQUIRE(cons == pr.constants);
    }
    //TODO this test case is broken... should not accept this
//    SECTION("1 operator but invalid") {
//        std::vector<Token> v = {Token("x", TokenType::NameToken),
//                                Token("y", TokenType::NameToken),
//                                Token("+", TokenType::OpToken),
//                                Token("1", TokenType::ConstToken)};
//        Parser pr(v);
//        REQUIRE_NOTHROW(pr.parseExpression());
//    }
}

TEST_CASE("Parse If") {
    std::vector<Token> v = {Token("if", TokenType::IfToken),
                            Token("(", TokenType::LParenToken),
                            Token("x", TokenType::NameToken),
                            Token("<", TokenType::RelationToken),
                            Token("y", TokenType::NameToken),
                            Token(")", TokenType::RParenToken),
                            Token("then", TokenType::ThenToken),
                            Token("{", TokenType::LCurlyToken),
                            Token("read", TokenType::ReadToken),
                            Token("x", TokenType::NameToken),
                            Token(";", TokenType::SemiColonToken),
                            Token("}", TokenType::RCurlyToken),
                            Token("else", TokenType::ElseToken),
                            Token("{", TokenType::LCurlyToken),
                            Token("print", TokenType::ReadToken),
                            Token("y", TokenType::NameToken),
                            Token(";", TokenType::SemiColonToken),
                            Token("}", TokenType::RCurlyToken)};
    std::unordered_set<std::string> var = {"x", "y"};
    std::unordered_set<std::string> cons;
    Parser pr(v);
    REQUIRE_NOTHROW(pr.parseIf());
    REQUIRE(var == pr.variables);
    REQUIRE(cons == pr.constants);
}

TEST_CASE("Parse While") {
    std::vector<Token> v = {Token("while", TokenType::WhileToken),
                            Token("(", TokenType::LParenToken),
                            Token("x", TokenType::NameToken),
                            Token("<=", TokenType::RelationToken),
                            Token("y", TokenType::NameToken),
                            Token(")", TokenType::RParenToken),
                            Token("{", TokenType::LCurlyToken),
                            Token("read", TokenType::ReadToken),
                            Token("x", TokenType::NameToken),
                            Token(";", TokenType::SemiColonToken),
                            Token("}", TokenType::RCurlyToken)};
    std::unordered_set<std::string> var = {"x", "y"};
    std::unordered_set<std::string> cons;
    Parser pr(v);
    REQUIRE_NOTHROW(pr.parseWhile());
    REQUIRE(var == pr.variables);
    REQUIRE(cons == pr.constants);
}

TEST_CASE("Parse Call") {
    std::vector<Token> v = {Token("call", TokenType::CallToken),
                            Token("DummyProcedure", TokenType::NameToken),
                            Token(";", TokenType::SemiColonToken),};
    Parser pr(v);
    REQUIRE_NOTHROW(pr.parseCall());
}

TEST_CASE("Parse Cond") {
    SECTION("Simple Condition") {
        std::vector<Token> v = {Token("x", TokenType::NameToken),
                                Token("<=", TokenType::RelationToken),
                                Token("y", TokenType::NameToken)};
        std::unordered_set<std::string> var = {"x", "y"};
        Parser pr(v);
        REQUIRE_NOTHROW(pr.parseCond());
        REQUIRE(var == pr.variables);
    }

    SECTION("Negation Condition") {
        std::vector<Token> v = {Token("!", TokenType::CondToken),
                                Token("(", TokenType::LParenToken),
                                Token("x", TokenType::NameToken),
                                Token("<=", TokenType::RelationToken),
                                Token("y", TokenType::NameToken),
                                Token(")", TokenType::RParenToken)};
        std::unordered_set<std::string> var = {"x", "y"};
        Parser pr(v);
        REQUIRE_NOTHROW(pr.parseCond());
        REQUIRE(var == pr.variables);
    }

    SECTION("invalid Cond at the front") {
        std::vector<Token> v = {Token("||", TokenType::CondToken),
                                Token("(", TokenType::LParenToken),
                                Token("x", TokenType::NameToken),
                                Token("<=", TokenType::RelationToken),
                                Token("y", TokenType::NameToken),
                                Token(")", TokenType::RParenToken)};
        Parser pr(v);
        REQUIRE_THROWS(pr.parseCond());
    }

    SECTION("And Condition") {
        std::vector<Token> v = {Token("(", TokenType::LParenToken),
                                Token("!", TokenType::CondToken),
                                Token("(", TokenType::LParenToken),
                                Token("x", TokenType::NameToken),
                                Token("<=", TokenType::RelationToken),
                                Token("y", TokenType::NameToken),
                                Token(")", TokenType::RParenToken),
                                Token(")", TokenType::RParenToken),
                                Token("&&", TokenType::CondToken),
                                Token("(", TokenType::LParenToken),
                                Token("z", TokenType::NameToken),
                                Token(">", TokenType::RelationToken),
                                Token("y", TokenType::NameToken),
                                Token(")", TokenType::RParenToken)};
        std::unordered_set<std::string> var = {"x", "y", "z"};
        Parser pr(v);
        REQUIRE_NOTHROW(pr.parseCond());
        REQUIRE(var == pr.variables);
    }

    SECTION("OR Condition") {
        std::vector<Token> v = {Token("(", TokenType::LParenToken),
                                Token("!", TokenType::CondToken),
                                Token("(", TokenType::LParenToken),
                                Token("x", TokenType::NameToken),
                                Token("<=", TokenType::RelationToken),
                                Token("y", TokenType::NameToken),
                                Token(")", TokenType::RParenToken),
                                Token(")", TokenType::RParenToken),
                                Token("||", TokenType::CondToken),
                                Token("(", TokenType::LParenToken),
                                Token("z", TokenType::NameToken),
                                Token(">", TokenType::RelationToken),
                                Token("y", TokenType::NameToken),
                                Token(")", TokenType::RParenToken)};
        std::unordered_set<std::string> var = {"x", "y", "z"};
        Parser pr(v);
        REQUIRE_NOTHROW(pr.parseCond());
        REQUIRE(var == pr.variables);
    }
}
