#include "Tokenizer.h"
#include "QueryPreprocessor.h"

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
                                                                    { WHITESPACE, "^(\\s+)" } };
    std::vector<std::string> splitToLines(std::istream& stream) {
        std::string line;
        std::vector<std::string> splitResult;

        while(std::getline(std::cin, line)){
            if (line.empty()){
                break;
            }
            splitResult.push_back(line);
//            std::cout << line << std::endl;
        }

        return splitResult;
    }

    Token createToken(TokenType t, std::string nameValue) {
        Token token{};
        token.tokenType = t;
        token.nameValue = std::move(nameValue);
        return token;
    }

    std::vector<Token> tokenize(std::string queryString, std::vector<Token> &tokens) {
        std::vector<Token> tokenizedResult;
//        std::cout << "=====query string ====" << std::endl;
//        std::cout << queryString << std::endl;
//        std::vector<std::string> splitString = splitToLines(stream);
//        std::vector<std::string> splitString = {"variable v1, v2,  v3;",  "Select v3"}; // for test only.
        std::smatch match;
        bool isMatched = true;
        while (!queryString.empty() && isMatched) {
            isMatched = false;
            for (const std::pair<TokenType, std::string>& pair : matchingRules) {
                if (std::regex_search(queryString, match, std::regex(pair.second))) {
                    isMatched = true;
                    Token t;
                    if (pair.first == NAME) {
                        t = createToken(NAME, match.str());
                        tokenizedResult.push_back(t);
                    } else if (pair.first == INTEGER) {
                        t = createToken(INTEGER, match.str());
                        tokenizedResult.push_back(t);
                    } else if (pair.first == WHITESPACE){
                    } else {
                        std::cout << tokenMap.at(pair.first) << std::endl;
                        t = createToken(pair.first, match.str());
                        tokenizedResult.push_back(t);
                    }
                    queryString = queryString.substr(match.str().size());
                }

            }
            if (!isMatched) {
                std::cout << "syntax error";
            }
        }
        std::copy(tokenizedResult.begin(), tokenizedResult.end(), std::back_inserter(tokens));

//        std::cout << "finish tokenizing" << std::endl;
        return tokenizedResult;
    }

    bool isSuchThat(Token token) {
        return token.nameValue == "Such";
    }
} // Tokenization
//
//
//int main() {
//    std::vector<QPS::Token> tokens;
//    std::string queryString;
//    std::cin >> queryString;
//    QPS::tokenize(queryString, tokens);
//    for (QPS::Token t : tokens) {
//        std::string s = QPS::tokenMap.at(t.tokenType);
//        std::cout << s + " " << std::endl;
//    }
//
//    std::cout << "Start parsing query" << std::endl;
//    QPS::parseToken(tokens);
//}