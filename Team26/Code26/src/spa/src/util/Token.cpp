#pragma once

#include "Token.h"

//Token Token::createTerminal(std::string s) {
//    if(s == "(") {
//        return LParenToken(s);
//    } else if(s == ")") {
//        return RParenToken(s);
//    } else if(s == "{") {
//        return LCurlyToken(s);
//    } else if(s == "}") {
//        return RCurlyToken(s);
//    } else if(s == "=") {
//        return AssignToken(s);
//    } else if(s == ">" || s == "<" || s == ">=" || s == "<=" || s == "==" || s == "!=") {
//        return RelationToken(s);
//    } else if(s == "!" || s == "||" || s == "&") {
//        return CondToken(s);
//    } else if(s == "+" || s == "-" || s == "/" || s == "*" || s == "%") {
//        return OpToken(s);
//    } else {
//        return ErrorToken(s);
//    }
//}
//
//Token Token::createNonTerminal(std::string s) {
//    if(s == "procedure") {
//       return ProcedureToken(s);
//    } else if (s == "read") {
//        return ReadToken(s);
//    } else if (s == "print") {
//        return PrintToken(s);
//    } else if (s == "while") {
//        return WhileToken(s);
//    } else if (s == "if") {
//        return IfToken(s);
//    } else {
//        return NameToken(s);
//    }
//}
//
//Token Token::createConstToken(std::string s) {
//    return ConstToken(s);
//}