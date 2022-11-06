#include "Tokenizer.h"
#include "qps/QueryPreprocessor.h"

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
        auto start = std::chrono::steady_clock::now();
        auto stop = std::chrono::steady_clock::now();
        auto duration = duration_cast<std::chrono::milliseconds>(stop - start);

        std::cout << "Time taken by start token: "
             << duration.count() << " milliseconds" << std::endl;
        std::vector<Token> tokenizedResult;
        std::smatch match;
        while (!queryString.empty()) {
            for (const std::pair<TokenType, std::string>& pair : matchingRules) {

                bool regex_match = std::regex_search(queryString, match, std::regex(pair.second));

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
                stop = std::chrono::steady_clock::now();
                duration = duration_cast<std::chrono::milliseconds>(stop - start);

//                std::cout << "Time taken by before string: "
//                          << duration.count() << " milliseconds" << std::endl;


                queryString.erase(0, match.str().size());

            }
        }
        std::copy(tokenizedResult.begin(), tokenizedResult.end(), std::back_inserter(tokens));
        stop = std::chrono::steady_clock::now();
        duration = duration_cast<std::chrono::milliseconds>(stop - start);

        std::cout << "Time taken by finish token: "
                  << duration.count() << " milliseconds" << std::endl;
        return true;
    }

} // Tokenization
