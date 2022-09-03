#include "Tokenizer.h"
#include "QueryPreprocessor.h"

namespace QPS {
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

    std::vector<Token> tokenize(std::istream& stream, std::vector<Token> &tokens) {
        std::vector<Token> tokenizedResult;
//        std::vector<std::string> splitString = splitToLines(stream);
        std::vector<std::string> splitString = {"variable v Select v"};

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
        std::copy(tokenizedResult.begin(), tokenizedResult.end(), std::back_inserter(tokens));
        return tokenizedResult;
    }

    bool isSuchThat(Token token) {
        return token.nameValue == "Such";
    }
} // Tokenization


int main() {
    std::vector<QPS::Token> tokens;
    std::vector<int> tmp = {0, 0, 1, 2};
    QPS::tokenize(std::cin, tokens);
    std::cout << typeid(tmp).name() << std::endl;
    for (QPS::Token t : tokens) {
        std::string s = QPS::m.at(t.tokenType);
        std::cout << s + " ";
    }


    std::cout << "Start parsing query";
    QPS::parseToken(tokens);
}