#include "sp/de/DesignExtractor.h"
#include "./stubs/PKBInterfaceStubForDE.h"
#include "util/ast/TNode.h"
#include "catch.hpp"

std::shared_ptr<TNode> generateSimpleTNode(int statementNo) {
    return TNode::createTerm(statementNo, "+", std::move(TNode::createVariableName(statementNo, "x")),
                                       std::move(TNode::createConstantValue(statementNo, "1")));
}

std::shared_ptr<TNode> generateSimpleCondStmt(int statementNo) {
    return TNode::createConditionalExpression(statementNo, "<", std::move(TNode::createVariableName(statementNo, "x")),
                             std::move(TNode::createConstantValue(statementNo, "1")));
}

std::shared_ptr<ProcedureNode> generateSimpleProcedureNode() {
    std::shared_ptr<TNode> expr = std::move(generateSimpleTNode(1));
    std::shared_ptr<AssignNode> statement1 = std::move(AssignNode::createAssignNode(1, "x", expr));
    std::shared_ptr<PrintNode> statement2 = std::move(PrintNode::createPrintNode(2, "y"));
    std::shared_ptr<ReadNode> statement3 = std::move(ReadNode::createReadNode(3, "x"));
    std::vector<std::shared_ptr<StatementNode>> stmtList = {statement1, statement2, statement3};
    return ProcedureNode::createProcedureNode("simpleTest", stmtList);
}

std::shared_ptr<IfNode> generateSimpleIfNode(int startingNo) {
    std::shared_ptr<TNode> condExpr = std::move(generateSimpleCondStmt(startingNo));

    std::shared_ptr<TNode> expr = std::move(generateSimpleTNode(startingNo + 1));
    std::shared_ptr<AssignNode> ifStmt1 = std::move(AssignNode::createAssignNode(startingNo + 1, "x", expr));
    std::shared_ptr<PrintNode> ifStmt2 = std::move(PrintNode::createPrintNode(startingNo + 2, "y"));
    std::shared_ptr<ReadNode> ifStmt3 = std::move(ReadNode::createReadNode(startingNo + 3, "x"));
    std::shared_ptr<TNode> expr2 = std::move(generateSimpleTNode(startingNo + 5));
    std::shared_ptr<PrintNode> elseStmt1 = std::move(PrintNode::createPrintNode(startingNo + 4, "y"));
    std::shared_ptr<AssignNode> elseStmt2 = std::move(AssignNode::createAssignNode(startingNo + 5, "x", expr2));
    std::shared_ptr<ReadNode> elseStmt3 = std::move(ReadNode::createReadNode(startingNo + 6, "x"));

    std::vector<std::shared_ptr<StatementNode>> ifStmtList = {ifStmt1, ifStmt2, ifStmt3};
    std::vector<std::shared_ptr<StatementNode>> elseStmtList = {elseStmt1, elseStmt2, elseStmt3};

    return IfNode::createIfNode(startingNo, condExpr, ifStmtList, elseStmtList);
}

std::shared_ptr<WhileNode> generateSimpleWhileNode(int startingNo) {
    std::shared_ptr<TNode> condExpr = std::move(generateSimpleCondStmt(startingNo));

    std::shared_ptr<TNode> expr = std::move(generateSimpleTNode(startingNo + 1));
    std::shared_ptr<AssignNode> stmt1 = std::move(AssignNode::createAssignNode(startingNo + 1, "x", expr));
    std::shared_ptr<PrintNode> stmt2 = std::move(PrintNode::createPrintNode(startingNo + 2, "y"));
    std::shared_ptr<ReadNode> stmt3 = std::move(ReadNode::createReadNode(startingNo + 3, "x"));

    std::vector<std::shared_ptr<StatementNode>> stmtList = {stmt1, stmt2, stmt3};

    return WhileNode::createWhileNode(startingNo, condExpr, stmtList);
}

TEST_CASE("FollowsExtractor Tests") {
    SECTION("Extract from Procedure Test") {
        auto *pkbInterface = new PKBInterfaceStubForDE<int, int>();
        FollowsExtractor followsExtractor = FollowsExtractor(pkbInterface);
        followsExtractor.extractFromProcedure(generateSimpleProcedureNode());

        auto correctUnorderedMap = std::unordered_map<int, int>();
        correctUnorderedMap[1] = 2;
        correctUnorderedMap[2] = 3;

        REQUIRE(pkbInterface->unorderedMap[1] == 2);
        REQUIRE(pkbInterface->unorderedMap[2] == 3);
        REQUIRE(pkbInterface->unorderedMap == correctUnorderedMap);
        delete pkbInterface;
    }

    SECTION("Extract from If Node") {
        auto *pkbInterface = new PKBInterfaceStubForDE<int, int>();
        FollowsExtractor followsExtractor = FollowsExtractor(pkbInterface);
        followsExtractor.extractFromIf(generateSimpleIfNode(1));

        auto correctUnorderedMap = std::unordered_map<int, int>();
        correctUnorderedMap[2] = 3;
        correctUnorderedMap[3] = 4;
        correctUnorderedMap[5] = 6;
        correctUnorderedMap[6] = 7;

        REQUIRE(pkbInterface->unorderedMap == correctUnorderedMap);
        delete pkbInterface;
    }

    SECTION("Extract from While Node") {
        auto *pkbInterface = new PKBInterfaceStubForDE<int, int>();
        FollowsExtractor followsExtractor = FollowsExtractor(pkbInterface);
        followsExtractor.extractFromWhile(generateSimpleWhileNode(1));

        auto correctUnorderedMap = std::unordered_map<int, int>();
        correctUnorderedMap[2] = 3;
        correctUnorderedMap[3] = 4;

        REQUIRE(pkbInterface->unorderedMap == correctUnorderedMap);
        delete pkbInterface;
    }
}