#include <string>
#include "catch.hpp"
#include "util/Lexer.h"
#include "sp/Parser.h"
std::string sampleText = "procedure Example {\n x = 2;\nz = 3;\ni = 5;\nwhile (i!=0) {\nx = x - 1;\nif (x==1) then {\nz = x + 1; }\nelse {\ny = z + x; }\nz = z + x + i;\ncall q;\ni = i - 1; }\ncall p; }\n\nprocedure p {\nif (x<0) then {\nwhile (i>0) {\nx = z * 3 + 2 * y;\ncall q;\ni = i - 1; }\nx = x + 1;\nz = x + z; }\nelse {\nz = 1; }\nz = z + x + i; }\n\nprocedure q {\nif (x==1) then {\nz = x + 1; }\nelse {\nx = z + x; } }";
std::string testsprint1 = "procedure sprint1 {\n read x;\n print y;\n x = x + 1;\n if(x < y) then {\n x = z + y * 3;\n y = x + 1;\n z = x + 5;\n } else {\n print p;\n x = 3 + 4;\n z = x + 3;\n }\n z = x + y;\n}";
std::string variableNamesAsKeywords = "procedure procedure {\n print = read + 1;\n read print;\n print read;\n if (if > 1) then {\n else = else + 1;\n } else {\n if = if + 1;\n }\n while (while > 1) {\n while = while + 1;\n }\n }";
std::string testMS1 = "procedure hard2 {\n while ((x>1)&&(y>2)) {\n if (x > 1) then {\n z = x * 3 - 2;\n if (y < 10) then {\n z = x + y + 1 * 2;\n } else {\n read z;\n print z;\n }\n read x;\n while (x * 1 - 4 < 11) {\n a  = b + 1;\n if (x > 10 - y) then {\n b = a + 2;\n } else {\n x = a + b;\n }\n print a;\n print b;\n }\n read y;\n } else {\n read x;\n print y;\n }\n }\n\n x = y + a + b;\nprint x;\n print y;\n print a;\n\n}";
std::string multipleProceduresTest = "procedure main { flag = 0; } procedure readPoint { read x;read y;}procedure printResults {print flag;print cenX;print cenY;print normSq;} procedure computeCentroid {count = 0;cenX = 0;cenY = 0;call readPoint;while ((x != 0) && (y != 0)) {count = count + 1;cenX = cenX + x;cenY = cenY + y;call readPoint;}if (count == 0) then {flag = 1;} else {cenX = cenX / count;cenY = cenY / count;}normSq = cenX * cenX + cenY * cenY;}";
PKBInterface pkbInterface;

TEST_CASE("test ms1") {
    Parser p(Lexer(testMS1).tokenize(), &pkbInterface);
    REQUIRE_NOTHROW(p.parseSimple());
}

TEST_CASE("Test variable name as keywords") {
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

TEST_CASE("Test multiple procedures") {
    Parser p(Lexer(multipleProceduresTest).tokenize(), &pkbInterface);
    REQUIRE_NOTHROW(p.parseSimple());
}