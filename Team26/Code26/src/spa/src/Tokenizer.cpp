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

    Token createToken(TokenType t, std::string nameValue, int integerValue) {
        Token token{};
        token.tokenType = t;
        token.nameValue = std::move(nameValue);
        token.integerValue = integerValue;
        return token;
    }

    std::vector<Token> tokenize(std::istream& stream, std::vector<Token> &tokens) {
        std::vector<Token> tokenizedResult;
        std::vector<std::string> splitString = splitToLines(stream);
//        std::vector<std::string> splitString = {"variable v1, v2,  v3;",  "Select v3"}; // for test only.
        for (std::string s : splitString) {
            std::smatch match;
            int length = s.size();
            bool isMatched = true;
            while (!s.empty() && isMatched) {
                isMatched = false;
                for (const std::pair<TokenType, std::string>& pair : matchingRules) {
                    if (std::regex_search(s, match, std::regex(pair.second))) {
                        isMatched = true;
                        Token t;
                        if (pair.first == NAME) {
                            t = createToken(NAME, match.str(), 0);
                            tokenizedResult.push_back(t);
                        } else if (pair.first == INTEGER) {
                           t = createToken(INTEGER, "", std::stoi(match.str()));
                            tokenizedResult.push_back(t);
                        } else if (pair.first == WHITESPACE){
                        } else {
                            t = createToken(pair.first, "", 0);
                            tokenizedResult.push_back(t);
                        }
                        s = s.substr(match.str().size());
                    }

                }
                if (!isMatched) {
                    std::cout << "syntax error";
                }
            }
        }
        std::copy(tokenizedResult.begin(), tokenizedResult.end(), std::back_inserter(tokens));

        std::cout << "finish tokenizing" << std::endl;
        return tokenizedResult;
    }

    bool isSuchThat(Token token) {
        return token.nameValue == "Such";
    }
} // Tokenization


//int main() {
//    std::vector<QPS::SPToken> tokens;
//    QPS::tokenize(std::cin, tokens);
//    for (QPS::SPToken t : tokens) {
//        std::string s = QPS::tokenMap.at(t.tokenType);
//        std::cout << s + " " << std::endl;
//    }
//
//    std::cout << "Start parsing query" << std::endl;
//    QPS::parseToken(tokens);
//}