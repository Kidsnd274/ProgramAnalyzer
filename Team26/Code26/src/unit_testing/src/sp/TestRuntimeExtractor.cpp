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
    REQUIRE_FALSE(pkbInterface->hasNextStar(1));
    rte.computeNextStar(createdCFG, 1);
    REQUIRE_FALSE(pkbInterface->hasNextStar(2));
    rte.computeNextStar(createdCFG, 2);
    REQUIRE_FALSE(pkbInterface->hasNextStar(3));
    rte.computeNextStar(createdCFG, 3);
    REQUIRE_FALSE(pkbInterface->hasNextStar(4));
    rte.computeNextStar(createdCFG, 4);
    REQUIRE_FALSE(pkbInterface->hasNextStar(5));
    rte.computeNextStar(createdCFG, 5);
    REQUIRE_FALSE(pkbInterface->hasNextStar(6));
    rte.computeNextStar(createdCFG, 6);
    REQUIRE_FALSE(pkbInterface->hasNextStar(7));
    rte.computeNextStar(createdCFG, 7);
    REQUIRE_FALSE(pkbInterface->hasNextStar(8));
    rte.computeNextStar(createdCFG, 8);
    REQUIRE_FALSE(pkbInterface->hasNextStar(9));
    rte.computeNextStar(createdCFG, 9);
    REQUIRE_FALSE(pkbInterface->hasNextStar(10));
    rte.computeNextStar(createdCFG, 10);
    REQUIRE_FALSE(pkbInterface->hasNextStar(11));
    rte.computeNextStar(createdCFG, 11);

    REQUIRE(pkbInterface->hasNextStar(1));
    REQUIRE(pkbInterface->hasNextStar(2));
    REQUIRE(pkbInterface->hasNextStar(3));
    REQUIRE(pkbInterface->hasNextStar(4));
    REQUIRE(pkbInterface->hasNextStar(5));
    REQUIRE(pkbInterface->hasNextStar(6));
    REQUIRE(pkbInterface->hasNextStar(7));
    REQUIRE(pkbInterface->hasNextStar(8));
    REQUIRE(pkbInterface->hasNextStar(9));
    REQUIRE(pkbInterface->hasNextStar(10));
    REQUIRE(pkbInterface->hasNextStar(11));

    REQUIRE(pkbInterface->nextStarMap == correctMap);
}

TEST_CASE("Simple affects test") {
    std::vector<SPToken> v = {SPToken("procedure", SPTokenType::ProcedureToken),
                              SPToken("Second", SPTokenType::NameToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("0", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("i", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("5", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("while", SPTokenType::WhileToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("i", SPTokenType::NameToken),
                              SPToken("!=", SPTokenType::RelationToken),
                              SPToken("0", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("2", SPTokenType::ConstToken),
                              SPToken("*", SPTokenType::FactorToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("i", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("i", SPTokenType::NameToken),
                              SPToken("-", SPTokenType::OpToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("if", SPTokenType::IfToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("==", SPTokenType::RelationToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("then", SPTokenType::ThenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("else", SPTokenType::ElseToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("i", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("2", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("*", SPTokenType::FactorToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
    };

    PKBInterfaceStubForDE *pkbInterface = new PKBInterfaceStubForDE();
    auto cfgManager = std::make_shared<CFGManager>();
    Parser testParser(v, pkbInterface, cfgManager);
    REQUIRE_NOTHROW(testParser.parseSimple());

    CFGHeadPtr createdCFG = cfgManager->getCurrentCFG();

    RuntimeExtractor rte(pkbInterface);
    std::unordered_set<STMT_NUM> stmt1 = {4, 7, 9, 11};
    std::unordered_set<STMT_NUM> stmt2 = {5, 9};
    std::unordered_set<STMT_NUM> stmt4 = {4, 7, 9, 11};
    std::unordered_set<STMT_NUM> stmt5 = {5, 9};
    std::unordered_set<STMT_NUM> stmt7 = {9, 11};
    std::unordered_set<STMT_NUM> stmt8 = {9};
    std::unordered_set<STMT_NUM> stmt9 = {10, 11};
    std::unordered_set<STMT_NUM> stmt10 = {11};

    REQUIRE_FALSE(pkbInterface->hasAffects(1));
    rte.computeAffects(createdCFG, 1);
    REQUIRE_FALSE(pkbInterface->hasAffects(2));
    rte.computeAffects(createdCFG, 2);
    REQUIRE_FALSE(pkbInterface->hasAffects(4));
    rte.computeAffects(createdCFG, 4);
    REQUIRE_FALSE(pkbInterface->hasAffects(5));
    rte.computeAffects(createdCFG, 5);
    REQUIRE_FALSE(pkbInterface->hasAffects(7));
    rte.computeAffects(createdCFG, 7);
    REQUIRE_FALSE(pkbInterface->hasAffects(8));
    rte.computeAffects(createdCFG, 8);
    REQUIRE_FALSE(pkbInterface->hasAffects(9));
    rte.computeAffects(createdCFG, 9);
    REQUIRE_FALSE(pkbInterface->hasAffects(10));
    rte.computeAffects(createdCFG, 10);

    REQUIRE(pkbInterface->hasAffects(1));
    REQUIRE(pkbInterface->hasAffects(2));
    REQUIRE(pkbInterface->hasAffects(4));
    REQUIRE(pkbInterface->hasAffects(5));
    REQUIRE(pkbInterface->hasAffects(7));
    REQUIRE(pkbInterface->hasAffects(8));
    REQUIRE(pkbInterface->hasAffects(9));
    REQUIRE(pkbInterface->hasAffects(10));

    REQUIRE(pkbInterface->affectsMap[1] == stmt1);
    REQUIRE(pkbInterface->affectsMap[2] == stmt2);
    REQUIRE(pkbInterface->affectsMap[4] == stmt4);
    REQUIRE(pkbInterface->affectsMap[5] == stmt5);
    REQUIRE(pkbInterface->affectsMap[7] == stmt7);
    REQUIRE(pkbInterface->affectsMap[8] == stmt8);
    REQUIRE(pkbInterface->affectsMap[9] == stmt9);
    REQUIRE(pkbInterface->affectsMap[10] == stmt10);
}

TEST_CASE("Simple affects Star test") {
    std::vector<SPToken> v = {SPToken("procedure", SPTokenType::ProcedureToken),
                              SPToken("Second", SPTokenType::NameToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("0", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("i", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("5", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("while", SPTokenType::WhileToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("i", SPTokenType::NameToken),
                              SPToken("!=", SPTokenType::RelationToken),
                              SPToken("0", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("2", SPTokenType::ConstToken),
                              SPToken("*", SPTokenType::FactorToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("i", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("i", SPTokenType::NameToken),
                              SPToken("-", SPTokenType::OpToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("if", SPTokenType::IfToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("==", SPTokenType::RelationToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("then", SPTokenType::ThenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("else", SPTokenType::ElseToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("i", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("2", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("*", SPTokenType::FactorToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
    };

    PKBInterfaceStubForDE *pkbInterface = new PKBInterfaceStubForDE();
    auto cfgManager = std::make_shared<CFGManager>();
    Parser testParser(v, pkbInterface, cfgManager);
    REQUIRE_NOTHROW(testParser.parseSimple());

    CFGHeadPtr createdCFG = cfgManager->getCurrentCFG();

    RuntimeExtractor rte(pkbInterface);

    std::unordered_set<STMT_NUM> stmt1 = {4, 7, 9, 10, 11};
    std::unordered_set<STMT_NUM> stmt2 = {5, 9, 10, 11};
    std::unordered_set<STMT_NUM> stmt4 = {4, 7, 9, 10, 11};
    std::unordered_set<STMT_NUM> stmt5 = {5, 9, 10, 11};
    std::unordered_set<STMT_NUM> stmt7 = {9, 10, 11};
    std::unordered_set<STMT_NUM> stmt8 = {9, 10, 11};
    std::unordered_set<STMT_NUM> stmt9 = {10, 11};
    std::unordered_set<STMT_NUM> stmt10 = {11};
    std::unordered_set<STMT_NUM> stmt11 = {};

    REQUIRE_FALSE(pkbInterface->hasAffectsStar(1));
    REQUIRE_FALSE(pkbInterface->hasAffects(1));
    rte.computeAffectsStar(createdCFG, 1);
    REQUIRE_FALSE(pkbInterface->hasAffectsStar(2));
    REQUIRE(pkbInterface->hasAffects(2));
    rte.computeAffectsStar(createdCFG, 2);
    REQUIRE_FALSE(pkbInterface->hasAffectsStar(4));
    REQUIRE(pkbInterface->hasAffects(4));
    rte.computeAffectsStar(createdCFG, 4);
    REQUIRE_FALSE(pkbInterface->hasAffectsStar(5));
    REQUIRE(pkbInterface->hasAffects(5));
    rte.computeAffectsStar(createdCFG, 5);
    REQUIRE_FALSE(pkbInterface->hasAffectsStar(7));
    REQUIRE(pkbInterface->hasAffects(7));
    rte.computeAffectsStar(createdCFG, 7);
    REQUIRE_FALSE(pkbInterface->hasAffectsStar(8));
    REQUIRE(pkbInterface->hasAffects(8));
    rte.computeAffectsStar(createdCFG, 8);
    REQUIRE_FALSE(pkbInterface->hasAffectsStar(9));
    REQUIRE(pkbInterface->hasAffects(9));
    rte.computeAffectsStar(createdCFG, 9);
    REQUIRE_FALSE(pkbInterface->hasAffectsStar(10));
    REQUIRE(pkbInterface->hasAffects(10));
    rte.computeAffectsStar(createdCFG, 10);
    REQUIRE_FALSE(pkbInterface->hasAffectsStar(11));
    REQUIRE(pkbInterface->hasAffects(11));
    rte.computeAffectsStar(createdCFG, 11);

    REQUIRE(pkbInterface->hasAffects(1));
    REQUIRE(pkbInterface->hasAffects(2));
    REQUIRE(pkbInterface->hasAffects(4));
    REQUIRE(pkbInterface->hasAffects(5));
    REQUIRE(pkbInterface->hasAffects(7));
    REQUIRE(pkbInterface->hasAffects(8));
    REQUIRE(pkbInterface->hasAffects(9));
    REQUIRE(pkbInterface->hasAffects(10));
    REQUIRE(pkbInterface->hasAffects(11));

    REQUIRE(pkbInterface->hasAffectsStar(1));
    REQUIRE(pkbInterface->hasAffectsStar(2));
    REQUIRE(pkbInterface->hasAffectsStar(4));
    REQUIRE(pkbInterface->hasAffectsStar(5));
    REQUIRE(pkbInterface->hasAffectsStar(7));
    REQUIRE(pkbInterface->hasAffectsStar(8));
    REQUIRE(pkbInterface->hasAffectsStar(9));
    REQUIRE(pkbInterface->hasAffectsStar(10));
    REQUIRE(pkbInterface->hasAffectsStar(11));

    REQUIRE(pkbInterface->affectsStarMap[1] == stmt1);
    REQUIRE(pkbInterface->affectsStarMap[2] == stmt2);
    REQUIRE(pkbInterface->affectsStarMap[4] == stmt4);
    REQUIRE(pkbInterface->affectsStarMap[5] == stmt5);
    REQUIRE(pkbInterface->affectsStarMap[7] == stmt7);
    REQUIRE(pkbInterface->affectsStarMap[8] == stmt8);
    REQUIRE(pkbInterface->affectsStarMap[9] == stmt9);
    REQUIRE(pkbInterface->affectsStarMap[10] == stmt10);
}

TEST_CASE("2 procedure affects/affects* test") {
    std::vector<SPToken> v = {SPToken("procedure", SPTokenType::ProcedureToken),
                              SPToken("Second", SPTokenType::NameToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("0", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("i", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("5", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("while", SPTokenType::WhileToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("i", SPTokenType::NameToken),
                              SPToken("!=", SPTokenType::RelationToken),
                              SPToken("0", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("2", SPTokenType::ConstToken),
                              SPToken("*", SPTokenType::FactorToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("call", SPTokenType::CallToken),
                              SPToken("Third", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("i", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("i", SPTokenType::NameToken),
                              SPToken("-", SPTokenType::OpToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("if", SPTokenType::IfToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("==", SPTokenType::RelationToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("then", SPTokenType::ThenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("else", SPTokenType::ElseToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("i", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("2", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("*", SPTokenType::FactorToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("procedure", SPTokenType::ProcedureToken),
                              SPToken("Third", SPTokenType::NameToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("i", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("5", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("v", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("print", SPTokenType::PrintToken),
                              SPToken("v", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken)
    };

    PKBInterfaceStubForDE *pkbInterface = new PKBInterfaceStubForDE();
    auto cfgManager = std::make_shared<CFGManager>();
    Parser testParser(v, pkbInterface, cfgManager);
    REQUIRE_NOTHROW(testParser.parseSimple());

    CFGHeadPtr createdCFG = pkbInterface->procedureToCFG["Second"];
    RuntimeExtractor rte(pkbInterface);

    SECTION("Affects test") {
        std::unordered_set<STMT_NUM> stmt1 = {4, 8, 10, 12};
        std::unordered_set<STMT_NUM> stmt2 = {10};
        std::unordered_set<STMT_NUM> stmt4 = {4, 8, 10, 12};
        std::unordered_set<STMT_NUM> stmt6 = {10};
        std::unordered_set<STMT_NUM> stmt8 = {10, 12};
        std::unordered_set<STMT_NUM> stmt9 = {10};
        std::unordered_set<STMT_NUM> stmt10 = {11, 12};
        std::unordered_set<STMT_NUM> stmt11 = {12};
        std::unordered_set<STMT_NUM> stmt12 = {};

        rte.computeAffects(createdCFG, 1);
        REQUIRE(pkbInterface->affectsMap[1] == stmt1);

        rte.computeAffects(createdCFG, 2);
        REQUIRE(pkbInterface->affectsMap[2] == stmt2);

        rte.computeAffects(createdCFG, 4);
        REQUIRE(pkbInterface->affectsMap[4] == stmt4);

        rte.computeAffects(createdCFG, 6);
        REQUIRE(pkbInterface->affectsMap[6] == stmt6);

        rte.computeAffects(createdCFG, 8);
        REQUIRE(pkbInterface->affectsMap[8] == stmt8);

        rte.computeAffects(createdCFG, 9);
        REQUIRE(pkbInterface->affectsMap[9] == stmt9);

        rte.computeAffects(createdCFG, 10);
        REQUIRE(pkbInterface->affectsMap[10] == stmt10);

        rte.computeAffects(createdCFG, 11);
        REQUIRE(pkbInterface->affectsMap[11] == stmt11);

        rte.computeAffects(createdCFG, 12);
        REQUIRE(pkbInterface->affectsMap[12] == stmt12);
    }

    SECTION("Affects* tests") {
        std::unordered_set<STMT_NUM> stmt1 = {4, 8, 10, 11, 12};
        std::unordered_set<STMT_NUM> stmt2 = {10, 11, 12};
        std::unordered_set<STMT_NUM> stmt4 = {4, 8, 10, 11, 12};
        std::unordered_set<STMT_NUM> stmt6 = {10, 11, 12};
        std::unordered_set<STMT_NUM> stmt8 = {10, 11, 12};
        std::unordered_set<STMT_NUM> stmt9 = {10, 11, 12};
        std::unordered_set<STMT_NUM> stmt10 = {11, 12};
        std::unordered_set<STMT_NUM> stmt11 = {12};
        std::unordered_set<STMT_NUM> stmt12 = {};

        rte.computeAffectsStar(createdCFG, 1);
        rte.computeAffectsStar(createdCFG, 2);
        rte.computeAffectsStar(createdCFG, 4);
        rte.computeAffectsStar(createdCFG, 6);
        rte.computeAffectsStar(createdCFG, 8);
        rte.computeAffectsStar(createdCFG, 9);
        rte.computeAffectsStar(createdCFG, 10);
        rte.computeAffectsStar(createdCFG, 11);
        rte.computeAffectsStar(createdCFG, 12);

        REQUIRE(pkbInterface->affectsStarMap[1] == stmt1);
        REQUIRE(pkbInterface->affectsStarMap[2] == stmt2);
        REQUIRE(pkbInterface->affectsStarMap[4] == stmt4);
        REQUIRE(pkbInterface->affectsStarMap[6] == stmt6);
        REQUIRE(pkbInterface->affectsStarMap[8] == stmt8);
        REQUIRE(pkbInterface->affectsStarMap[9] == stmt9);
        REQUIRE(pkbInterface->affectsStarMap[10] == stmt10);
        REQUIRE(pkbInterface->affectsStarMap[11] == stmt11);
        REQUIRE(pkbInterface->affectsStarMap[12] == stmt12);
    }
}

TEST_CASE("if-if and while-while loop") {
    std::vector<SPToken> v = {SPToken("procedure", SPTokenType::ProcedureToken),
                              SPToken("one", SPTokenType::NameToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("if", SPTokenType::IfToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("then", SPTokenType::ThenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("k", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("if", SPTokenType::IfToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("then", SPTokenType::ThenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("call", SPTokenType::CallToken),
                              SPToken("two", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("else", SPTokenType::ElseToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("call", SPTokenType::CallToken),
                              SPToken("three", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("k", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("else", SPTokenType::ElseToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("k", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("1", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("while", SPTokenType::WhileToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("k", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("while", SPTokenType::WhileToken),
                              SPToken("(", SPTokenType::LParenToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken(">", SPTokenType::RelationToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken(")", SPTokenType::RParenToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("z", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("call", SPTokenType::CallToken),
                              SPToken("three", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("k", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken("+", SPTokenType::OpToken),
                              SPToken("3", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("k", SPTokenType::NameToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("procedure", SPTokenType::ProcedureToken),
                              SPToken("two", SPTokenType::NameToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("x", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("15", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken),
                              SPToken("procedure", SPTokenType::ProcedureToken),
                              SPToken("three", SPTokenType::NameToken),
                              SPToken("{", SPTokenType::LCurlyToken),
                              SPToken("y", SPTokenType::NameToken),
                              SPToken("=", SPTokenType::AssignToken),
                              SPToken("30", SPTokenType::ConstToken),
                              SPToken(";", SPTokenType::SemiColonToken),
                              SPToken("}", SPTokenType::RCurlyToken)
    };

    PKBInterfaceStubForDE *pkbInterface = new PKBInterfaceStubForDE();
    auto cfgManager = std::make_shared<CFGManager>();
    Parser testParser(v, pkbInterface, cfgManager);
    REQUIRE_NOTHROW(testParser.parseSimple());

    CFGHeadPtr createdCFG = pkbInterface->procedureToCFG["one"];
    RuntimeExtractor rte(pkbInterface);

    SECTION("Affects test") {
        std::unordered_set<STMT_NUM> stmt1 = {4, 6, 11};
        std::unordered_set<STMT_NUM> stmt2 = {4, 6, 11, 14};
        std::unordered_set<STMT_NUM> stmt4 = {10, 14, 19};
        std::unordered_set<STMT_NUM> stmt6 = {14};
        std::unordered_set<STMT_NUM> stmt8 = {};
        std::unordered_set<STMT_NUM> stmt10 = {};
        std::unordered_set<STMT_NUM> stmt11 = {14, 19};
        std::unordered_set<STMT_NUM> stmt12 = {16};
        std::unordered_set<STMT_NUM> stmt14 = {};
        std::unordered_set<STMT_NUM> stmt16 = {};
        std::unordered_set<STMT_NUM> stmt18 = {19, 14};
        std::unordered_set<STMT_NUM> stmt19 = {14};

        rte.computeAffects(createdCFG, 1);
        rte.computeAffects(createdCFG, 2);
        rte.computeAffects(createdCFG, 4);
        rte.computeAffects(createdCFG, 6);
        rte.computeAffects(createdCFG, 8);
        rte.computeAffects(createdCFG, 10);
        rte.computeAffects(createdCFG, 11);
        rte.computeAffects(createdCFG, 12);
        rte.computeAffects(createdCFG, 14);
        rte.computeAffects(createdCFG, 18);
        rte.computeAffects(createdCFG, 19);
        REQUIRE(pkbInterface->affectsMap[1] == stmt1);
        REQUIRE(pkbInterface->affectsMap[2] == stmt2);
        REQUIRE(pkbInterface->affectsMap[4] == stmt4);
        REQUIRE(pkbInterface->affectsMap[6] == stmt6);
        REQUIRE(pkbInterface->affectsMap[8] == stmt8);
        REQUIRE(pkbInterface->affectsMap[10] == stmt10);
        REQUIRE(pkbInterface->affectsMap[11] == stmt11);
        REQUIRE(pkbInterface->affectsMap[12] == stmt12);
        REQUIRE(pkbInterface->affectsMap[14] == stmt14);
        REQUIRE(pkbInterface->affectsMap[18] == stmt18);
        REQUIRE(pkbInterface->affectsMap[19] == stmt19);
    }

    SECTION("Affects* Test") {
        std::unordered_set<STMT_NUM> stmt1 = {4, 6, 10, 11, 14, 19};
        std::unordered_set<STMT_NUM> stmt2 = {4, 6, 10, 11, 14, 19};
        std::unordered_set<STMT_NUM> stmt4 = {10, 14, 19};
        std::unordered_set<STMT_NUM> stmt6 = {14};
        std::unordered_set<STMT_NUM> stmt8 = {};
        std::unordered_set<STMT_NUM> stmt10 = {};
        std::unordered_set<STMT_NUM> stmt11 = {14, 19};
        std::unordered_set<STMT_NUM> stmt12 = {16};
        std::unordered_set<STMT_NUM> stmt14 = {};
        std::unordered_set<STMT_NUM> stmt16 = {};
        std::unordered_set<STMT_NUM> stmt18 = {19, 14};
        std::unordered_set<STMT_NUM> stmt19 = {14};

        rte.computeAffectsStar(createdCFG, 1);
        rte.computeAffectsStar(createdCFG, 2);
        rte.computeAffectsStar(createdCFG, 4);
        rte.computeAffectsStar(createdCFG, 6);
        rte.computeAffectsStar(createdCFG, 8);
        rte.computeAffectsStar(createdCFG, 10);
        rte.computeAffectsStar(createdCFG, 11);
        rte.computeAffectsStar(createdCFG, 12);
        rte.computeAffectsStar(createdCFG, 14);
        rte.computeAffectsStar(createdCFG, 18);
        rte.computeAffectsStar(createdCFG, 19);
        REQUIRE(pkbInterface->affectsStarMap[1] == stmt1);
        REQUIRE(pkbInterface->affectsStarMap[2] == stmt2);
        REQUIRE(pkbInterface->affectsStarMap[4] == stmt4);
        REQUIRE(pkbInterface->affectsStarMap[6] == stmt6);
        REQUIRE(pkbInterface->affectsStarMap[8] == stmt8);
        REQUIRE(pkbInterface->affectsStarMap[10] == stmt10);
        REQUIRE(pkbInterface->affectsStarMap[11] == stmt11);
        REQUIRE(pkbInterface->affectsStarMap[12] == stmt12);
        REQUIRE(pkbInterface->affectsStarMap[14] == stmt14);
        REQUIRE(pkbInterface->affectsStarMap[18] == stmt18);
        REQUIRE(pkbInterface->affectsStarMap[19] == stmt19);
    }
}