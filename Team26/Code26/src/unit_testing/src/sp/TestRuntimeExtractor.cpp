#include "catch.hpp"
#include "sp/rte/RuntimeExtractor.h"
#include "./stubs/PKBInterfaceStubForDE.h"
#include "sp/Parser.h"

TEST_CASE("Simple Next* test") {
    std::vector<SPToken> v = {SPToken("procedure", SPTokenType::ProcedureToken),
                              SPToken("iloveprofsanka", SPTokenType::NameToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("read", SPTokenType::ReadToken),
                              SPToken("read", SPTokenType::ReadToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("while", SPTokenType::WhileToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken(">=", SPTokenType::RelationToken),
                              SPToken("0", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken("procedure", SPTokenType::ProcedureToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("if", SPTokenType::IfToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("<", SPTokenType::RelationToken),
                              SPToken("50", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("then", SPTokenType::ThenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("if", SPTokenType::IfToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("&&", SPTokenType::CondToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken("<", SPTokenType::RelationToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("then", SPTokenType::ThenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("then", SPTokenType::ThenToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken("-", SPTokenType::OpToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("else", SPTokenType::ElseToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("while", SPTokenType::WhileToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("k", SPTokenType::NameToken),
                              SPToken(">=", SPTokenType::RelationToken),
                              SPToken("0", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("call", SPTokenType::CallToken),
                              SPToken("%", SPTokenType::FactorToken),
                              SPToken("60", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("else", SPTokenType::ElseToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("while", SPTokenType::WhileToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("pencil", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("7", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken("if", SPTokenType::IfToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken("done", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken)
    };

    PKBInterfaceStubForDE *pkbInterface = new PKBInterfaceStubForDE();
    auto cfgManager = std::make_shared<CFGManager>();
    Parser testParser(v, pkbInterface, cfgManager);
    REQUIRE_NOTHROW(testParser.parseSimple());

    CFGHeadPtr createdCFG = cfgManager->getCurrentCFG();

    RuntimeExtractor rte(pkbInterface);
    rte.computeNextStar(createdCFG, 1);
    std::unordered_set<STMT_NUM> stmt1 = {2,11,3,4,5,6,7,8,9,10};
    std::unordered_set<STMT_NUM> stmt2 = {2,11,3,4,5,6,7,8,9,10};
    std::unordered_set<STMT_NUM> stmt3 = {2,11,3,4,5,6,7,8,9,10};
    std::unordered_set<STMT_NUM> stmt4 = {2,11,3,4,5,6,7,8,9,10};
    std::unordered_set<STMT_NUM> stmt5 = {2,11,3,4,5,6,7,8,9,10};
    std::unordered_set<STMT_NUM> stmt6 = {2,11,3,4,5,6,7,8,9,10};
    std::unordered_set<STMT_NUM> stmt7 = {2,11,3,4,5,6,7,8,9,10};
    std::unordered_set<STMT_NUM> stmt8 = {2,11,3,4,5,6,7,8,9,10};
    std::unordered_set<STMT_NUM> stmt9 = {2,11,3,4,5,6,7,8,9,10};
    std::unordered_set<STMT_NUM> stmt10 = {2,11,3,4,5,6,7,8,9,10};
    std::unordered_set<STMT_NUM> stmt11 = {};
    std::unordered_map<STMT_NUM, std::unordered_set<STMT_NUM>> correctMap =  {
            {1, stmt1},
            {2, stmt2},
            {3, stmt3},
            {4, stmt4},
            {5, stmt5},
            {6, stmt6},
            {7, stmt7},
            {8, stmt8},
            {9, stmt9},
            {10, stmt10},
            {11, stmt11},
    };
    for(auto &[f,s] : pkbInterface->nextStarCache) {
        std::cout << to_string(f) << ": ";
        for(auto i : s) {
            std::cout << to_string(i) << " ";
        }
        std::cout << std::endl;
    }
}