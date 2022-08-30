//
// Created by 冯准懿 on 2022/8/30.
//
#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <utility>
#include "Tokenizer.h"

namespace Tokenization {
    std::map<TokenType, std::string> m = {
            { LBRACE, "LBRACE" },
            { RBRACE, "RBRACE" },
            { LPAREN, "LPAREN" },
            { RPAREN, "RPAREN" },
            { SEMICOLON, "SEMICOLON" },
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

    std::vector<std::pair<TokenType, std::string>> matchingRules = {{ LBRACE, "^(\\{)" },
                                                                    { RBRACE, "^(\\})" },
                                                                    { LPAREN, "^(\\()" },
                                                                    { RPAREN, "^(\\))" },
                                                                    { SEMICOLON, "^(;)" },
                                                                    { COMMA, "^(,)" },
                                                                    { UNDERSCORE, "^(_)" },
                                                                    { DOUBLE_QUOTE, "^(\")" },
                                                                    { NOT_EQ, "^(!=)" },
                                                                    { NOT, "^(!)" },
                                                                    { DOUBLE_EQ, "^(==)" },
                                                                    { SINGLE_EQ, "^(=)" },
                                                                    { DOUBLE_AND, "^(&&)" },
                                                                    { DOUBLE_OR, "^(\\|\\|)" },
                                                                    { GTE, "^(>=)" },
                                                                    { GT, "^(>)" },
                                                                    { LTE, "^(<=)" },
                                                                    { LT, "^(<)" },
                                                                    { PLUS, "^(\\+)" },
                                                                    { MINUS, "^(-)" },
                                                                    { MULTIPLY, "^(\\*)" },
                                                                    { DIVIDE, "^(\\/)" },
                                                                    { MODULE, "^(%)" },
                                                                    { NAME, "^([a-zA-Z]\\w*)\\b" },
                                                                    { INTEGER, "^(\\d+)" },

                                                                    { WHITESPACE, "^(\\s+)" } };
    std::vector<std::string> splitToLines(std::istream& stream) {
        std::vector<std::string> splitResult;
        std::string currLine;
        while (std::getline(stream, currLine)) {
            std::cout << currLine;
            splitResult.push_back(currLine);
        }
        return splitResult;
    }

    Token createToken(TokenType t, int lineNUmber, int inLinePosition, std::string nameValue, int integerValue) {
        Token token{};
        token.tokenType = t;
        token.lineNumber = lineNUmber;
        token.inLinePosition = inLinePosition;
        token.nameValue = std::move(nameValue);
        token.integerValue = integerValue;
        return token;
    }

    std::vector<Token> tokenize(std::istream& stream) {
        std::vector<Token> tokenizedResult;
//        std::vector<std::string> splitString = splitToLines(stream);
        std::vector<std::string> splitString = {"select v such that uses(a, v) 223 _ 3 <= >=", "hhhh"};

        int lineNumber = 0;
        for (std::string s : splitString) {
            std::smatch match;
            int length = s.size();
            bool isMatched = true;
            while (!s.empty() && isMatched) {
                isMatched = false;
                for (const std::pair<TokenType, std::string>& pair : matchingRules) {
                    if (std::regex_search(s, match, std::regex(pair.second))) {
                        isMatched = true;
                        int pos = length - s.size();
                        Token t;
                        if (pair.first == NAME) {
                            t = createToken(NAME, lineNumber, pos, match.str(), 0);
                        } else if (pair.first == INTEGER) {
                           t = createToken(INTEGER, lineNumber, pos, "", std::stoi(match.str()));
                        } else {
                            t = createToken(pair.first, lineNumber, pos, "", 0);
                        }
                        tokenizedResult.push_back(t);
                        s = s.substr(match.str().size());
                    }

                }
                if (!isMatched) {
                    std::cout << "syntax error";
                }
            }
            lineNumber++;
        }
        return tokenizedResult;

    }
} // Tokenization

int main() {
    std::vector<Tokenization::Token> tokens = Tokenization::tokenize(std::cin);
    for (Tokenization::Token t : tokens) {
        std::string s = Tokenization::m.at(t.tokenType);
        std::cout << s + " ";
    }

}