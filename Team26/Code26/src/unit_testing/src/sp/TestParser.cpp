#include "sp/Parser.h"
#include "util/TokenTypeExtractor.h"
#include "catch.hpp"
#include <vector>

std::vector<Token> validSimple = {TokenTypeExtractor::createNonTerminal("procedure"),
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
std::vector<Token> invalidSimple = {TokenTypeExtractor::createNonTerminal("procedure"),
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
TEST_CASE("Basic Parser Test with valid program", "This is to make sure that the current minimal parser does not throw a syntax error") {
    Parser p(validSimple);
    REQUIRE_NOTHROW(p.parseSimple());
}

TEST_CASE("Basic Parser Test with invalid program", "This is to make sure that the current minimal parser does throw a syntax error") {
    Parser p(invalidSimple);
    REQUIRE_NOTHROW(p.parseSimple());
}

