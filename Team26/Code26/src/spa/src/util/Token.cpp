#pragma once

#include "Token.h"
#include "LParenToken.h"
#include "RParenToken.h"
#include "LCurlyToken.h"
#include "RCurlyToken.h"
#include "AssignToken.h"
#include "RelationToken.h"
#include "CondToken.h"
#include "OpToken.h"
#include "ErrorToken.h"

Token Token::createTerminal(std::string s) {
    if(s == "(") {
        return LParenToken(s);
    } else if(s == ")") {
        return RParenToken(s);
    } else if(s == "{") {
        return LCurlyToken(s);
    } else if(s == "}") {
        return RCurlyToken(s);
    } else if(s == "=") {
        return AssignToken(s);
    } else if(s == ">" || s == "<" || s == ">=" || s == "<=" || s == "==" || s == "!=") {
        return RelationToken(s);
    } else if(s == "!" || s == "||" || s == "&") {
        return CondToken(s);
    } else if(s == "+" || s == "-" || s == "/" || s == "*" || s == "%") {
        return OpToken(s);
    } else {
        return ErrorToken(s);
    }
}

Token Token::createNonTerminal(std::string s) {

}