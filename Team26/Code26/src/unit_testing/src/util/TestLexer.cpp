#include "util/Lexer.h"
#include "catch.hpp"
#include <vector>
using namespace std;

string validSimple = "procedure test {\n  read x;\n  x = x + 1;\n}";

// TODO: Test case is outdated and doesn't test tokenize() with vector<Token>
//TEST_CASE("Basic Lexer test on valid SIMPLE", "This is a test for a very small and basic SIMPLE program") {
//    Lexer lexer(validSimple);
//    vector<string> res = lexer.tokenize();
//    vector<string> expected = {"procedure", "test", "{", "read", "x", ";", "x", "=", "x", "+", "1", ";", "}"};
//    REQUIRE(res == expected);
//}