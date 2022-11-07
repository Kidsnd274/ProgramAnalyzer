#ifndef SPA_TOKENIZER_H
#define SPA_TOKENIZER_H

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <regex>
#include <utility>
#include "QueryProcessorTypes.h"

namespace QPS {
    enum TokenType {
        SEMICOLON,
        LPAREN,
        RPAREN,
        COMMA,
        UNDERSCORE,
        DOUBLE_QUOTE,
        SINGLE_EQ,
        LT,
        GT,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        MODULE,
        NAME,
        INTEGER,
        WHITESPACE,
        STAR,
        DOT,
        HASHTAG
    };

    const std::map<TokenType, std::string> tokenMap = {
            { LPAREN, "LBRACE" },
            { RPAREN, "RBRACE" },
            { SEMICOLON, "SEMICOLON" },
            {STAR, "STAR"},
            { COMMA, "COMMA" },
            { UNDERSCORE, "UNDERSCORE" },
            { DOUBLE_QUOTE, "DOUBLE_QUOTE" },
            { SINGLE_EQ, "SINGLE_EQ" },
            { GT, "GT" },
            { LT, "LT" },
            { PLUS, "PLUS" },
            { MINUS, "MINUS" },
            { MULTIPLY, "MULTIPLY" },
            { DIVIDE, "DIV" },
            { MODULE, "MOD" },
            { NAME, "NAME" },
            { INTEGER, "INTEGER" },
            { WHITESPACE, "WHITESPACE" },
            {DOT, "DOT"},
            {HASHTAG, "HASHTAG"}
    };

    struct Token {
        TokenType tokenType;
        std::string nameValue;
    };

    bool tokenize(std::string queryString, std::vector<Token> &tokens);
    Token createToken(TokenType t, std::string nameValue);
}  // namespace QPS

#endif  // SPA_TOKENIZER_H
