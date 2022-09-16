#include <string>
#include "catch.hpp"
#include "util/Lexer.h"
#include "sp/Parser.h"
std::string sampleText = "procedure Example {\n x = 2;\nz = 3;\ni = 5;\nwhile (i!=0) {\nx = x - 1;\nif (x==1) then {\nz = x + 1; }\nelse {\ny = z + x; }\nz = z + x + i;\ncall q;\ni = i - 1; }\ncall p; }\n\nprocedure p {\nif (x<0) then {\nwhile (i>0) {\nx = z * 3 + 2 * y;\ncall q;\ni = i - 1; }\nx = x + 1;\nz = x + z; }\nelse {\nz = 1; }\nz = z + x + i; }\n\nprocedure q {\nif (x==1) then {\nz = x + 1; }\nelse {\nx = z + x; } }";
std::string testsprint1 = "procedure sprint1 {\n read x;\n print y;\n x = x + 1;\n if(x < y) then {\n x = z + y * 3;\n y = x + 1;\n z = x + 5;\n } else {\n print p;\n x = 3 + 4;\n z = x + 3;\n }\n z = x + y;\n}";
std::string variableNamesAsKeywords = "procedure procedure {\n print = read + 1;\n read print;\n print read;\n if (if > 1) then {\n else = else + 1;\n } else {\n if = if + 1;\n }\n while (while > 1) {\n while = while + 1;\n }\n }";
PKBInterface pkbInterface;


TEST_CASE("Lexer into Parser valid SIMPLE") {
    Parser p(Lexer(variableNamesAsKeywords).tokenize(), &pkbInterface);
    REQUIRE_NOTHROW(p.parseSimple());
}

TEST_CASE("Lexer into Parser valid SIMPLE") {
    Parser p(Lexer(sampleText).tokenize(), &pkbInterface);
    REQUIRE_NOTHROW(p.parseSimple());
}

TEST_CASE("test sprint 1") {
    Parser p(Lexer(testsprint1).tokenize(), &pkbInterface);
    REQUIRE_NOTHROW(p.parseSimple());
}