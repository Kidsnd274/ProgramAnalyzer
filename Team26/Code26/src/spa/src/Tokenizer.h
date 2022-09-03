#ifndef SPA_TOKENIZER_H
#define SPA_TOKENIZER_H

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <regex>
#include <utility>
#include "QueryStruct.h"
#include "QueryPreprocessor.h"

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

    };

    struct Token {
        TokenType tokenType;
        int lineNumber;
        int inLinePosition;
        std::string nameValue;
        int integerValue;
    };

    std::vector<Token> tokenize(std::istream& string);
    Token createToken(TokenType t, int lineNUmber, int inLinePosition, std::string nameValue, int integerValue);
    bool isSuchThat(Token token);



}

#endif //SPA_TOKENIZER_H