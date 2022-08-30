#pragma once

#include "TokenTypeExtractor.h"

std::map<std::string, TokenType> terminalTokenMap = {
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
        { "/", TokenType::OpToken },
        { "*", TokenType::OpToken },
        { "%", TokenType::OpToken },
};

std::map<std::string, TokenType> nonTerminalTokenMap = {
        { "procedure", TokenType::ProcedureToken },
        { "read", TokenType::ReadToken },
        { "print", TokenType::PrintToken },
        { "while", TokenType::WhileToken },
        { "if", TokenType::IfToken },
};

Token TokenTypeExtractor::createTerminalToken(std::string s) {
    if (terminalTokenMap.count(s)) {
        TokenType tokenType = terminalTokenMap.at(s);
        return {s, tokenType};
    } else {
        return {"Error", TokenType::ErrorToken};
    }
}

// TODO: This function repeats the above one, consider merging them!
Token TokenTypeExtractor::createNonTerminalToken(std::string s) {
    if (nonTerminalTokenMap.count(s)) {
        TokenType tokenType = nonTerminalTokenMap.at(s);
        return {s, tokenType};
    } else {
        return {s, TokenType::NameToken};
    }
}

Token TokenTypeExtractor::createConstToken(std::string s) {
    return {s, TokenType::ConstToken};
}