#include "Tokenizer.h"

namespace QPS {
    std::vector<std::pair<TokenType, std::string>> matchingRules = {{ WHITESPACE, "^(\\s+)" },
                                                                    { NAME, "^([a-zA-Z]\\w*)\\b" },
                                                                    { INTEGER, "^(\\d+)" },
                                                                    { SEMICOLON, "^(;)" },
                                                                    { COMMA, "^(,)" },
                                                                    { LPAREN, "^(\\()" },
                                                                    { RPAREN, "^(\\))" },
                                                                    {STAR, "^(\\*)"},
                                                                    { UNDERSCORE, "^(_)" },
                                                                    { DOUBLE_QUOTE, "^(\")" },
                                                                    {DOT, "^(\\.)"},
                                                                    {HASHTAG, "^(\\#)"},
                                                                    { SINGLE_EQ, "^(=)" },
                                                                    { GT, "^(>)" },
                                                                    { LT, "^(<)" },
                                                                    { PLUS, "^(\\+)" },
                                                                    { MINUS, "^(-)" },
                                                                    { MULTIPLY, "^(\\*)" },
                                                                    { DIVIDE, "^(\\/)" },
                                                                    { MODULE, "^(%)" },
                                                                    };


    Token createToken(TokenType t, std::string nameValue) {
        Token token{};
        token.tokenType = t;
        token.nameValue = std::move(nameValue);
        return token;
    }

    bool tokenize(std::string queryString, std::vector<Token> &tokens) {
        std::vector<Token> tokenizedResult;
        std::smatch match;
        while (!queryString.empty()) {
            bool regex_match = std::regex_search(queryString, match, std::regex(matchingRules[0].second));
            if (regex_match) {
                queryString.erase(0, match.str().size());
                continue;
            }
            regex_match = std::regex_search(queryString, match, std::regex(matchingRules[1].second));
            Token t;
            if (regex_match) {
                t = createToken(NAME, match.str());
                queryString.erase(0, match.str().size());
                tokenizedResult.push_back(t);
                continue;
            }
            regex_match = std::regex_search(queryString, match, std::regex(matchingRules[2].second));
            if (regex_match) {
                t = createToken(INTEGER, match.str());
                queryString.erase(0, match.str().size());
                tokenizedResult.push_back(t);
                continue;
            }

            if (queryString[0] == ';') {
                t = createToken(SEMICOLON, ";");
            } else if (queryString[0] == ',') {
                t = createToken(COMMA, ",");
            } else if (queryString[0] == '(') {
                t = createToken(LPAREN, "(");
            } else if (queryString[0] == ')') {
                t = createToken(RPAREN, ")");
            } else if (queryString[0] == '*') {
                t = createToken(STAR, "*");
            } else if (queryString[0] == '_') {
                t = createToken(UNDERSCORE, "_");
            } else if (queryString[0] == '.') {
                t = createToken(DOT, ".");
            } else if (queryString[0] == '#') {
                t = createToken(HASHTAG, "#");
            } else if (queryString[0] == '=') {
                t = createToken(SINGLE_EQ, "=");
            } else if (queryString[0] == '>') {
                t = createToken(GT, ">");
            } else if (queryString[0] == '<') {
                t = createToken(LT, "<");
            } else if (queryString[0] == '+') {
                t = createToken(PLUS, "+");
            } else if (queryString[0] == '-') {
                t = createToken(MINUS, "-");
            } else if (queryString[0] == '/') {
                t = createToken(DIVIDE, "/");
            } else if (queryString[0] == '%') {
                t = createToken(MODULE, "%");
            } else if (queryString[0] == '\"') {
                t = createToken(DOUBLE_QUOTE, "\"");
                tokenizedResult.push_back(t);
                queryString.erase(0, 1);
                int pos_next_qoute = 0;
                bool empty_expression = true;
                while (queryString[pos_next_qoute] != '\"') {
                    if (queryString[pos_next_qoute] != ' ') {
                        empty_expression = false;
                    }
                    pos_next_qoute++;
                }
                std::string expression = queryString.substr(0, pos_next_qoute);
                if (!empty_expression) {
                    t = createToken(NAME, expression);
                }
                queryString.erase(0, pos_next_qoute);
                tokenizedResult.push_back(t);
                t = createToken(DOUBLE_QUOTE, "\"");
            }
            tokenizedResult.push_back(t);
            queryString.erase(0, 1);
        }
        std::copy(tokenizedResult.begin(), tokenizedResult.end(), std::back_inserter(tokens));
        return true;
    }

}  // namespace QPS
