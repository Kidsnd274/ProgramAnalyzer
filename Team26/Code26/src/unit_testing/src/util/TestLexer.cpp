#include "util/Lexer.h"
#include "catch.hpp"
#include <vector>

std::string validSimple = "procedure test {\n  read x;\n  x = x + 1;\n}";

TEST_CASE("Basic Lexer test on valid SIMPLE", "This is a test for a very small and basic SIMPLE program") {
    Lexer lexer(validSimple);
    std::vector<Token> res = lexer.tokenize();
    std::vector<Token> expected = {TokenTypeExtractor::createNonTerminal("procedure"),
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