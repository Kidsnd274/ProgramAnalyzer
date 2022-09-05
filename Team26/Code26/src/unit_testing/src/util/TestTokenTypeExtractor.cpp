#include "util/TokenTypeExtractor.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("Test_createTerminal_positive") {
    SECTION("Token Autotest") {
        for (const auto& [key, value] : TokenTypeExtractor::terminalTokenMap) {
            Token createdToken = TokenTypeExtractor::createTerminal(key);
            Token expectedToken = Token(key, value);
            REQUIRE(createdToken == expectedToken);
        }
    }

    SECTION("LParenToken") {
        std::string tokenString = "(";
        Token createdToken = TokenTypeExtractor::createTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::LParenToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("RParenToken") {
        std::string tokenString = ")";
        Token createdToken = TokenTypeExtractor::createTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::RParenToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("LCurlyToken") {
        std::string tokenString = "{";
        Token createdToken = TokenTypeExtractor::createTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::LCurlyToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("RCurlyToken") {
        std::string tokenString = "}";
        Token createdToken = TokenTypeExtractor::createTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::RCurlyToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("AssignToken") {
        std::string tokenString = "=";
        Token createdToken = TokenTypeExtractor::createTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::AssignToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("> RelationToken") {
        std::string tokenString = ">";
        Token createdToken = TokenTypeExtractor::createTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::RelationToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("< RelationToken") {
        std::string tokenString = "<";
        Token createdToken = TokenTypeExtractor::createTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::RelationToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION(">= RelationToken") {
        std::string tokenString = ">=";
        Token createdToken = TokenTypeExtractor::createTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::RelationToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("<= RelationToken") {
        std::string tokenString = "<=";
        Token createdToken = TokenTypeExtractor::createTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::RelationToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("== RelationToken") {
        std::string tokenString = "==";
        Token createdToken = TokenTypeExtractor::createTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::RelationToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("!= RelationToken") {
        std::string tokenString = "!=";
        Token createdToken = TokenTypeExtractor::createTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::RelationToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("! CondToken") {
        std::string tokenString = "!";
        Token createdToken = TokenTypeExtractor::createTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::CondToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("|| CondToken") {
        std::string tokenString = "||";
        Token createdToken = TokenTypeExtractor::createTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::CondToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("&& CondToken") {
        std::string tokenString = "&&";
        Token createdToken = TokenTypeExtractor::createTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::CondToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("+ OpToken") {
        std::string tokenString = "+";
        Token createdToken = TokenTypeExtractor::createTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::OpToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("- OpToken") {
        std::string tokenString = "-";
        Token createdToken = TokenTypeExtractor::createTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::OpToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("/ FactorToken") {
        std::string tokenString = "/";
        Token createdToken = TokenTypeExtractor::createTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::FactorToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("* FactorToken") {
        std::string tokenString = "*";
        Token createdToken = TokenTypeExtractor::createTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::FactorToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("% FactorToken") {
        std::string tokenString = "%";
        Token createdToken = TokenTypeExtractor::createTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::FactorToken);
        REQUIRE(createdToken == expectedToken);
    }
}

TEST_CASE("Test_createTerminal_negative") {
    std::string rubbish = "test";
    Token createdToken = TokenTypeExtractor::createTerminal(rubbish);
    Token expectedToken = Token(rubbish, TokenType::ErrorToken);
    REQUIRE(createdToken == expectedToken);
}

TEST_CASE("Test_createNonTerminal_positive") {
    SECTION("Token Autotest") {
        for (const auto& [key, value] : TokenTypeExtractor::nonTerminalTokenMap) {
            Token createdToken = TokenTypeExtractor::createNonTerminal(key);
            Token expectedToken = Token(key, value);
            REQUIRE(createdToken == expectedToken);
        }
    }

    SECTION("procedure Token") {
        std::string tokenString = "procedure";
        Token createdToken = TokenTypeExtractor::createNonTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::ProcedureToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("read Token") {
        std::string tokenString = "read";
        Token createdToken = TokenTypeExtractor::createNonTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::ReadToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("print Token") {
        std::string tokenString = "print";
        Token createdToken = TokenTypeExtractor::createNonTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::PrintToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("while Token") {
        std::string tokenString = "while";
        Token createdToken = TokenTypeExtractor::createNonTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::WhileToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("if Token") {
        std::string tokenString = "if";
        Token createdToken = TokenTypeExtractor::createNonTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::IfToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("then Token") {
        std::string tokenString = "then";
        Token createdToken = TokenTypeExtractor::createNonTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::ThenToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("else Token") {
        std::string tokenString = "else";
        Token createdToken = TokenTypeExtractor::createNonTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::ElseToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("Name Token") {
        std::string tokenString = "SomethingElse";
        Token createdToken = TokenTypeExtractor::createNonTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::NameToken);
        REQUIRE(createdToken == expectedToken);
    }

    SECTION("Call Token") {
        std::string tokenString = "call";
        Token createdToken = TokenTypeExtractor::createNonTerminal(tokenString);
        Token expectedToken = Token(tokenString, TokenType::CallToken);
        REQUIRE(createdToken == expectedToken);
    }
}

TEST_CASE("Test_createConst") {
    std::string tokenString = "9";
    Token createdToken = TokenTypeExtractor::createConst(tokenString);
    Token expectedToken = Token(tokenString, TokenType::ConstToken);
    REQUIRE(createdToken == expectedToken);
}