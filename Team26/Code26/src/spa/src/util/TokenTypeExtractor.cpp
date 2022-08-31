#include "TokenTypeExtractor.h"

std::unordered_map<std::string, TokenType> TokenTypeExtractor::terminalTokenMap = {
        { "(", TokenType::LParenToken },
        { ")", TokenType::RParenToken },
        { "{", TokenType::LCurlyToken },
        { "}", TokenType::RCurlyToken },
        { "=", TokenType::AssignToken },
        { ">", TokenType::RelationToken },
        { "<", TokenType::RelationToken },
        { ">=", TokenType::RelationToken },
        { "<=", TokenType::RelationToken },
        { "==", TokenType::RelationToken },
        { "!=", TokenType::RelationToken },
        { "!", TokenType::CondToken },
        { "||", TokenType::CondToken },
        { "&", TokenType::CondToken },
        { "+", TokenType::OpToken },
        { "-", TokenType::OpToken },
        { "/", TokenType::FactorToken },
        { "*", TokenType::FactorToken },
        { "%", TokenType::FactorToken },
        { ";", TokenType::SemiColonToken },
};

std::unordered_map<std::string, TokenType> TokenTypeExtractor::nonTerminalTokenMap = {
        { "procedure", TokenType::ProcedureToken },
        { "read", TokenType::ReadToken },
        { "print", TokenType::PrintToken },
        { "while", TokenType::WhileToken },
        { "if", TokenType::IfToken },
        { "then", TokenType::ThenToken },
        { "else", TokenType::ElseToken },
        { "call", TokenType::CallToken },
};

Token TokenTypeExtractor::createTerminal(std::string s) {
    if (terminalTokenMap.count(s)) {
        TokenType tokenType = terminalTokenMap.at(s);
        return {s, tokenType};
    } else {
        // TODO: Does ErrorToken store the string s?
        return {s, TokenType::ErrorToken};
    }
}

Token TokenTypeExtractor::createNonTerminal(std::string s) {
    if (nonTerminalTokenMap.count(s)) {
        TokenType tokenType = nonTerminalTokenMap.at(s);
        return {s, tokenType};
    } else {
        return {s, TokenType::NameToken};
    }
}

Token TokenTypeExtractor::createConst(std::string s) {
    return {s, TokenType::ConstToken};
}