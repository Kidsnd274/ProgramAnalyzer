#include "TokenTypeExtractor.h"

std::unordered_map<std::string, SPTokenType> TokenTypeExtractor::terminalTokenMap = {
        { "(",  SPTokenType::LParenToken },
        { ")",  SPTokenType::RParenToken },
        { "{",  SPTokenType::LCurlyToken },
        { "}",  SPTokenType::RCurlyToken },
        { "=",  SPTokenType::AssignToken },
        { ">",  SPTokenType::RelationToken },
        { "<",  SPTokenType::RelationToken },
        { ">=", SPTokenType::RelationToken },
        { "<=", SPTokenType::RelationToken },
        { "==", SPTokenType::RelationToken },
        { "!=", SPTokenType::RelationToken },
        { "!",  SPTokenType::CondToken },
        { "||", SPTokenType::CondToken },
        { "&&", SPTokenType::CondToken },
        { "+",  SPTokenType::OpToken },
        { "-",  SPTokenType::OpToken },
        { "/",  SPTokenType::FactorToken },
        { "*",  SPTokenType::FactorToken },
        { "%",  SPTokenType::FactorToken },
        { ";",  SPTokenType::SemiColonToken },
};

std::unordered_map<std::string, SPTokenType> TokenTypeExtractor::nonTerminalTokenMap = {
        { "procedure", SPTokenType::ProcedureToken },
        { "read",      SPTokenType::ReadToken },
        { "print",     SPTokenType::PrintToken },
        { "while",     SPTokenType::WhileToken },
        { "if",        SPTokenType::IfToken },
        { "then",      SPTokenType::ThenToken },
        { "else",      SPTokenType::ElseToken },
        { "call",      SPTokenType::CallToken },
};

SPToken TokenTypeExtractor::createTerminal(std::string s) {
    if (terminalTokenMap.count(s)) {
        SPTokenType tokenType = terminalTokenMap.at(s);
        return {s, tokenType};
    } else {
        // TODO: Does ErrorToken store the string s?
        return {s, SPTokenType::ErrorToken};
    }
}

SPToken TokenTypeExtractor::createNonTerminal(std::string s) {
    if (nonTerminalTokenMap.count(s)) {
        SPTokenType tokenType = nonTerminalTokenMap.at(s);
        return {s, tokenType};
    } else {
        return {s, SPTokenType::NameToken};
    }
}

bool isValidInteger(std::string &s) {
    if(s.size() > 1 && s[0] == '0') return false;
    return true;
}

SPToken TokenTypeExtractor::createConst(std::string s) {
    if(!isValidInteger(s)) {
        throw SyntaxErrorException();
    }

    return {s, SPTokenType::ConstToken};
}
