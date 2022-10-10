#ifndef SPA_TOKENIZER_H
#define SPA_TOKENIZER_H

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <regex>
#include <utility>
#include "QueryProcessorTypes.h"

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
        STAR,
        WILDCARD_TOKEN,
        DOT,
        HASHTAG
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
            { WILDCARD_TOKEN, "WILDCARD"},
            {DOT, "DOT"},
            {HASHTAG, "HASHTAG"}
    };

    struct Token {
        TokenType tokenType;
        std::string nameValue;
    };

    bool tokenize(std::string queryString, std::vector<Token> &tokens);
    Token createToken(TokenType t, int lineNUmber, int inLinePosition, std::string nameValue, int integerValue);
}

#endif //SPA_TOKENIZER_H