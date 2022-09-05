#include "util/Lexer.h"
#include "catch.hpp"
#include <vector>

std::string validSimple = "procedure test {\n  read x;\n  x = x + 1;\n}";
std::string invalidSimple = "procedure test {\n  if(x < = y) then {\n read x;\n} else {\n read y;\n }\n   x = x + 1;\n}";

TEST_CASE("Basic Lexer test on valid SIMPLE") {
    Lexer lexer(validSimple);
    std::vector<SPToken> res = lexer.tokenize();
    std::vector<SPToken> expected = {TokenTypeExtractor::createNonTerminal("procedure"),
                                     TokenTypeExtractor::createNonTerminal("test"),
                                     TokenTypeExtractor::createTerminal("{"),
                                     TokenTypeExtractor::createNonTerminal("read"),
                                     TokenTypeExtractor::createNonTerminal("x"),
                                     TokenTypeExtractor::createTerminal(";"),
                                     TokenTypeExtractor::createNonTerminal("x"),
                                     TokenTypeExtractor::createTerminal("="),
                                     TokenTypeExtractor::createNonTerminal("x"),
                                     TokenTypeExtractor::createTerminal("+"),
                                     TokenTypeExtractor::createConst("1"),
                                     TokenTypeExtractor::createTerminal(";"),
                                     TokenTypeExtractor::createTerminal("}")};

    REQUIRE(res == expected);
}

TEST_CASE("Basic Lexer test on an invalid SIMPLE", "This is a test for a very small and basic SIMPLE program that should parse the <= into < and =") {
    Lexer lexer(invalidSimple);
    std::vector<SPToken> res = lexer.tokenize();
    std::vector<SPToken> expected = {TokenTypeExtractor::createNonTerminal("procedure"),
                                     TokenTypeExtractor::createNonTerminal("test"),
                                     TokenTypeExtractor::createTerminal("{"),
                                     TokenTypeExtractor::createNonTerminal("if"),
                                     TokenTypeExtractor::createTerminal("("),
                                     TokenTypeExtractor::createNonTerminal("x"),
                                     TokenTypeExtractor::createTerminal("<"),
                                     TokenTypeExtractor::createTerminal("="),
                                     TokenTypeExtractor::createNonTerminal("y"),
                                     TokenTypeExtractor::createTerminal(")"),
                                     TokenTypeExtractor::createNonTerminal("then"),
                                     TokenTypeExtractor::createTerminal("{"),
                                     TokenTypeExtractor::createNonTerminal("read"),
                                     TokenTypeExtractor::createNonTerminal("x"),
                                     TokenTypeExtractor::createTerminal(";"),
                                     TokenTypeExtractor::createTerminal("}"),
                                     TokenTypeExtractor::createNonTerminal("else"),
                                     TokenTypeExtractor::createTerminal("{"),
                                     TokenTypeExtractor::createNonTerminal("read"),
                                     TokenTypeExtractor::createNonTerminal("y"),
                                     TokenTypeExtractor::createTerminal(";"),
                                     TokenTypeExtractor::createTerminal("}"),
                                     TokenTypeExtractor::createNonTerminal("x"),
                                     TokenTypeExtractor::createTerminal("="),
                                     TokenTypeExtractor::createNonTerminal("x"),
                                     TokenTypeExtractor::createTerminal("+"),
                                     TokenTypeExtractor::createConst("1"),
                                     TokenTypeExtractor::createTerminal(";"),
                                     TokenTypeExtractor::createTerminal("}")};
    REQUIRE(res == expected);
}