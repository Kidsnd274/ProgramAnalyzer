#include <string>
#include "catch.hpp"
#include "util/Lexer.h"
#include "sp/Parser.h"
#include <iostream>
std::string sample = "procedure Example {\n x = 2;\nz = 3;\ni = 5;\nwhile (i!=0) {\nx = x - 1;\nif (x==1) then {\nz = x + 1; }\nelse {\ny = z + x; }\nz = z + x + i;\ncall q;\ni = i - 1; }\ncall p; }\n\nprocedure p {\nif (x<0) then {\nwhile (i>0) {\nx = z * 3 + 2 * y;\ncall q;\ni = i - 1; }\nx = x + 1;\nz = x + z; }\nelse {\nz = 1; }\nz = z + x + i; }\n\nprocedure q {\nif (x==1) then {\nz = x + 1; }\nelse {\nx = z + x; } }";

TEST_CASE("Lexer into Parser valid SIMPLE") {
    Parser p(Lexer(sample).tokenize());
    REQUIRE_NOTHROW(p.parseSimple());
    std::cout << "Variables:\n";
    for(auto &s : p.variables) {
        std::cout << s << std::endl;
    }
    std::cout << "Constants:\n";
    for(auto &s : p.constants) {
        std::cout << s << std::endl;
    }
    std::cout << "Read:\n";
    for(auto &s : p.reads) {
        std::cout << s << std::endl;
    }
    std::cout << "Print:\n";
    for(auto &s : p.prints) {
        std::cout << s << std::endl;
    }
    std::cout << "While:\n";
    for(auto &s : p.whiles) {
        std::cout << s << std::endl;
    }
    std::cout << "Calls:\n";
    for(auto &s : p.calls) {
        std::cout << s << std::endl;
    }
    std::cout << "If:\n";
    for(auto &s : p.ifs) {
        std::cout << s << std::endl;
    }
}