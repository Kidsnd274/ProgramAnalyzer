#include "Tokenizer.h"
#include "qps/QueryPreprocessor.h"

namespace QPS {
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
                                                                    {STAR, "^(\\*)"},
                                                                    { WHITESPACE, "^(\\s+)" },
                                                                    {DOT, "^(\\.)"},
                                                                    {HASHTAG, "^(\\#)"}};


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
            for (const std::pair<TokenType, std::string>& pair : matchingRules) {
                bool regex_match = std::regex_search(queryString, match, std::regex(pair.second));
                // not matched token
                if (!regex_match) {
                    continue;
                }

                // ignore white space
                if (pair.first == WHITESPACE) {
                    queryString = queryString.substr(match.str().size());
                    continue;
                }

                Token t;
                if (pair.first == NAME) {
                    t = createToken(NAME, match.str());
                    tokenizedResult.push_back(t);
                } else if (pair.first == INTEGER) {
                    t = createToken(INTEGER, match.str());
                    tokenizedResult.push_back(t);
                } else {
                    t = createToken(pair.first, match.str());
                    tokenizedResult.push_back(t);
                }
                queryString = queryString.substr(match.str().size());
            }
        }
        std::copy(tokenizedResult.begin(), tokenizedResult.end(), std::back_inserter(tokens));
        return true;
    }

} // Tokenization
