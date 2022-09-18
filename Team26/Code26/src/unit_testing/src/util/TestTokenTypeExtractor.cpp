#include "util/TokenTypeExtractor.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("Test_createTerminal_positive") {
    SECTION("SPToken Autotest") {
        for (const auto& [key, value] : TokenTypeExtractor::terminalTokenMap) {
            SPToken createdToken = TokenTypeExtractor::createTerminal(key);
            SPToken expectedToken = SPToken(key, value);
            REQUIRE(createdToken == expectedToken);
        }
    }

    SECTION("LParenToken") {
        std::string tokenString = "(";
        SPToken createdToken = TokenTypeExtractor::createTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::LParenToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("RParenToken") {
        std::string tokenString = ")";
        SPToken createdToken = TokenTypeExtractor::createTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::RParenToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("LCurlyToken") {
        std::string tokenString = "{";
        SPToken createdToken = TokenTypeExtractor::createTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::LCurlyToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("RCurlyToken") {
        std::string tokenString = "}";
        SPToken createdToken = TokenTypeExtractor::createTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::RCurlyToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("AssignToken") {
        std::string tokenString = "=";
        SPToken createdToken = TokenTypeExtractor::createTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::AssignToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("> RelationToken") {
        std::string tokenString = ">";
        SPToken createdToken = TokenTypeExtractor::createTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::RelationToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("< RelationToken") {
        std::string tokenString = "<";
        SPToken createdToken = TokenTypeExtractor::createTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::RelationToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION(">= RelationToken") {
        std::string tokenString = ">=";
        SPToken createdToken = TokenTypeExtractor::createTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::RelationToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("<= RelationToken") {
        std::string tokenString = "<=";
        SPToken createdToken = TokenTypeExtractor::createTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::RelationToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("== RelationToken") {
        std::string tokenString = "==";
        SPToken createdToken = TokenTypeExtractor::createTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::RelationToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("!= RelationToken") {
        std::string tokenString = "!=";
        SPToken createdToken = TokenTypeExtractor::createTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::RelationToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("! CondToken") {
        std::string tokenString = "!";
        SPToken createdToken = TokenTypeExtractor::createTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::CondToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("|| CondToken") {
        std::string tokenString = "||";
        SPToken createdToken = TokenTypeExtractor::createTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::CondToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("&& CondToken") {
        std::string tokenString = "&&";
        SPToken createdToken = TokenTypeExtractor::createTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::CondToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("+ OpToken") {
        std::string tokenString = "+";
        SPToken createdToken = TokenTypeExtractor::createTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::OpToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("- OpToken") {
        std::string tokenString = "-";
        SPToken createdToken = TokenTypeExtractor::createTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::OpToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("/ FactorToken") {
        std::string tokenString = "/";
        SPToken createdToken = TokenTypeExtractor::createTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::FactorToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("* FactorToken") {
        std::string tokenString = "*";
        SPToken createdToken = TokenTypeExtractor::createTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::FactorToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("% FactorToken") {
        std::string tokenString = "%";
        SPToken createdToken = TokenTypeExtractor::createTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::FactorToken);
        REQUIRE(createdToken == expectedToken);
    }
}

TEST_CASE("Test_createTerminal_negative") {
    std::string rubbish = "test";
    SPToken createdToken = TokenTypeExtractor::createTerminal(rubbish);
    SPToken expectedToken = SPToken(rubbish, SPTokenType::ErrorToken);
    REQUIRE(createdToken == expectedToken);
}

TEST_CASE("Test_createNonTerminal_positive") {
    SECTION("SPToken Autotest") {
        for (const auto& [key, value] : TokenTypeExtractor::nonTerminalTokenMap) {
            SPToken createdToken = TokenTypeExtractor::createNonTerminal(key);
            SPToken expectedToken = SPToken(key, value);
            REQUIRE(createdToken == expectedToken);
        }
    }

    SECTION("procedure SPToken") {
        std::string tokenString = "procedure";
        SPToken createdToken = TokenTypeExtractor::createNonTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::ProcedureToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("read SPToken") {
        std::string tokenString = "read";
        SPToken createdToken = TokenTypeExtractor::createNonTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::ReadToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("print SPToken") {
        std::string tokenString = "print";
        SPToken createdToken = TokenTypeExtractor::createNonTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::PrintToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("while SPToken") {
        std::string tokenString = "while";
        SPToken createdToken = TokenTypeExtractor::createNonTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::WhileToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("if SPToken") {
        std::string tokenString = "if";
        SPToken createdToken = TokenTypeExtractor::createNonTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::IfToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("then SPToken") {
        std::string tokenString = "then";
        SPToken createdToken = TokenTypeExtractor::createNonTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::ThenToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("else SPToken") {
        std::string tokenString = "else";
        SPToken createdToken = TokenTypeExtractor::createNonTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::ElseToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("Name SPToken") {
        std::string tokenString = "SomethingElse";
        SPToken createdToken = TokenTypeExtractor::createNonTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::NameToken);

        std::string tokenString2 = "var1231A";
        SPToken createdToken2 = TokenTypeExtractor::createNonTerminal(tokenString2);
        SPToken expectedToken2 = SPToken(tokenString2, SPTokenType::NameToken);
        REQUIRE(createdToken == expectedToken);
        REQUIRE(createdToken2 == expectedToken2);
    }

    SECTION("Call SPToken") {
        std::string tokenString = "call";
        SPToken createdToken = TokenTypeExtractor::createNonTerminal(tokenString);
        SPToken expectedToken = SPToken(tokenString, SPTokenType::CallToken);
        REQUIRE(createdToken == expectedToken);
    }
}

TEST_CASE("Test_createConst") {
    std::string tokenString = "9";
    SPToken createdToken = TokenTypeExtractor::createConst(tokenString);
    SPToken expectedToken = SPToken(tokenString, SPTokenType::ConstToken);
    REQUIRE(createdToken == expectedToken);
}