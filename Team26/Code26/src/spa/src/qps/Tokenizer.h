#ifndef SPA_TOKENIZER_H
#define SPA_TOKENIZER_H

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <regex>
#include <utility>
#include "qps/QueryStruct.h"
#include "qps/QueryProcessorTypes.h"

namespace QPS {
    enum TokenType {
        LBRACE,
        RBRACE,
        SEMICOLON,
        LPAREN,
        RPAREN,
        COMMA,
        UNDERSCORE,
        DOUBLE_QUOTE,
        SINGLE_QUOTE,
        DOUBLE_EQ,
        SINGLE_EQ,
        AND,
        DOUBLE_AND,
        DOUBLE_OR,
        NOT_EQ,
        NOT,
        LT,
        GT,
        LTE,
        GTE,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        MODULE,
        NAME,
        INTEGER,
        WHITESPACE,
        STAR
    };

    const std::map<TokenType, std::string> tokenMap = {
            { LBRACE, "LBRACE" },
            { RBRACE, "RBRACE" },
            { LPAREN, "LPAREN" },
            { RPAREN, "RPAREN" },
            { SEMICOLON, "SEMICOLON" },
            {STAR, "STAR"},
            { COMMA, "COMMA" },
            { UNDERSCORE, "UNDERSCORE" },
            { DOUBLE_QUOTE, "DOUBLE_QUOTE" },
            { SINGLE_EQ, "SINGLE_EQ" },
            { NOT, "NOT" },
            { DOUBLE_AND, "DOUBLE_AND" },
            { DOUBLE_OR, "DOUBLE_OR" },
            { DOUBLE_EQ, "DOUBLE_EQ" },
            { NOT_EQ, "NOT_EQ" },
            { GT, "GT" },
            { GTE, "GTE" },
            { LT, "LT" },
            { LTE, "LTE" },
            { PLUS, "PLUS" },
            { MINUS, "MINUS" },
            { MULTIPLY, "MULTIPLY" },
            { DIVIDE, "DIV" },
            { MODULE, "MOD" },
            { NAME, "NAME" },
            { INTEGER, "INTEGER" },
            { WHITESPACE, "WHITESPACE" },
    };

    struct Token {
        TokenType tokenType;
        std::string nameValue;
    };

    std::vector<Token> tokenize(std::string queryString, std::vector<Token> &tokens);
    Token createToken(TokenType t, int lineNUmber, int inLinePosition, std::string nameValue, int integerValue);
    bool isSuchThat(Token token);
}

#endif //SPA_TOKENIZER_H