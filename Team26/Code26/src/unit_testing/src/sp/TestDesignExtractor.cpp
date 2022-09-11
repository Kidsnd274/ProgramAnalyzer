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
    std::shared_ptr<ReadNode> statement3 = std::move(ReadNode::createReadNode(3, "y"));
    std::vector<std::shared_ptr<StatementNode>> stmtList = {statement1, statement2, statement3};
    return ProcedureNode::createProcedureNode("simpleTest", stmtList);
}

std::shared_ptr<IfNode> generateSimpleIfNode(int startingNo) {
    std::shared_ptr<TNode> condExpr = std::move(generateSimpleCondStmt(startingNo));

    std::shared_ptr<TNode> expr = std::move(generateSimpleTNode(startingNo + 1));
    std::shared_ptr<AssignNode> ifStmt1 = std::move(AssignNode::createAssignNode(startingNo + 1, "x", expr));
    std::shared_ptr<PrintNode> ifStmt2 = std::move(PrintNode::createPrintNode(startingNo + 2, "y"));
    std::shared_ptr<ReadNode> ifStmt3 = std::move(ReadNode::createReadNode(startingNo + 3, "y"));
    std::shared_ptr<TNode> expr2 = std::move(generateSimpleTNode(startingNo + 5));
    std::shared_ptr<PrintNode> elseStmt1 = std::move(PrintNode::createPrintNode(startingNo + 4, "y"));
    std::shared_ptr<AssignNode> elseStmt2 = std::move(AssignNode::createAssignNode(startingNo + 5, "x", expr2));
    std::shared_ptr<ReadNode> elseStmt3 = std::move(ReadNode::createReadNode(startingNo + 6, "y"));

    std::vector<std::shared_ptr<StatementNode>> ifStmtList = {ifStmt1, ifStmt2, ifStmt3};
    std::vector<std::shared_ptr<StatementNode>> elseStmtList = {elseStmt1, elseStmt2, elseStmt3};

    return IfNode::createIfNode(startingNo, condExpr, ifStmtList, elseStmtList);
}

std::shared_ptr<WhileNode> generateSimpleWhileNode(int startingNo) {
    std::shared_ptr<TNode> condExpr = std::move(generateSimpleCondStmt(startingNo));

    std::shared_ptr<TNode> expr = std::move(generateSimpleTNode(startingNo + 1));
    std::shared_ptr<AssignNode> stmt1 = std::move(AssignNode::createAssignNode(startingNo + 1, "x", expr));
    std::shared_ptr<PrintNode> stmt2 = std::move(PrintNode::createPrintNode(startingNo + 2, "y"));
    std::shared_ptr<ReadNode> stmt3 = std::move(ReadNode::createReadNode(startingNo + 3, "y"));

    std::vector<std::shared_ptr<StatementNode>> stmtList = {stmt1, stmt2, stmt3};

    return WhileNode::createWhileNode(startingNo, condExpr, stmtList);
}

std::shared_ptr<ProcedureNode> generateMilestone1Test_nestlevel1() {
    std::shared_ptr<TNode> expr = std::move(generateSimpleTNode(1));
    std::shared_ptr<AssignNode> statement1 = std::move(AssignNode::createAssignNode(1, "x", expr));
    std::shared_ptr<PrintNode> statement2 = std::move(PrintNode::createPrintNode(2, "y"));
    std::shared_ptr<ReadNode> statement3 = std::move(ReadNode::createReadNode(3, "y"));
    std::shared_ptr<IfNode> statement4 = std::move(generateSimpleIfNode(4));
    std::shared_ptr<WhileNode> statement5 = std::move(generateSimpleWhileNode(11));
    std::vector<std::shared_ptr<StatementNode>> stmtList = {statement1, statement2, statement3, statement4, statement5};
    return ProcedureNode::createProcedureNode("milestone1_nestlevel1", stmtList);
}

// Individual extractor tests
TEST_CASE("FollowsExtractor Tests") {
    SECTION("Extract from Procedure Test") {
        auto *pkbInterface = new PKBInterfaceStubForDE();
        FollowsExtractor followsExtractor = FollowsExtractor(pkbInterface);
        followsExtractor.extractFromProcedure(generateSimpleProcedureNode());

        auto correctUnorderedMap = std::unordered_map<int, int>();
        correctUnorderedMap[1] = 2;
        correctUnorderedMap[2] = 3;

        REQUIRE(pkbInterface->followsMap[1] == 2);
        REQUIRE(pkbInterface->followsMap[2] == 3);
        REQUIRE(pkbInterface->followsMap == correctUnorderedMap);
        delete pkbInterface;
    }

    SECTION("Extract from If Node") {
        auto *pkbInterface = new PKBInterfaceStubForDE();
        FollowsExtractor followsExtractor = FollowsExtractor(pkbInterface);
        followsExtractor.extractFromIf(generateSimpleIfNode(1));

        auto correctUnorderedMap = std::unordered_map<int, int>();
        correctUnorderedMap[2] = 3;
        correctUnorderedMap[3] = 4;
        correctUnorderedMap[5] = 6;
        correctUnorderedMap[6] = 7;

        REQUIRE(pkbInterface->followsMap == correctUnorderedMap);
        delete pkbInterface;
    }

    SECTION("Extract from While Node") {
        auto *pkbInterface = new PKBInterfaceStubForDE();
        FollowsExtractor followsExtractor = FollowsExtractor(pkbInterface);
        followsExtractor.extractFromWhile(generateSimpleWhileNode(1));

        auto correctUnorderedMap = std::unordered_map<int, int>();
        correctUnorderedMap[2] = 3;
        correctUnorderedMap[3] = 4;

        REQUIRE(pkbInterface->followsMap == correctUnorderedMap);
        delete pkbInterface;
    }
}

TEST_CASE("Main Extract Interface") {
    SECTION("Nesting Level 1") {
        auto *pkbInterface = new PKBInterfaceStubForDE();
        DesignExtractor designExtractor = DesignExtractor(pkbInterface);
        std::shared_ptr<ProcedureNode> mainNode = std::move(generateMilestone1Test_nestlevel1());
        designExtractor.extract(mainNode);

        auto correctFollowsMap = std::unordered_map<int, int>();
        correctFollowsMap[1] = 2;
        correctFollowsMap[2] = 3;
        correctFollowsMap[3] = 4;
        correctFollowsMap[4] = 11;
        correctFollowsMap[5] = 6; // If Stmt List
        correctFollowsMap[6] = 7;
        correctFollowsMap[8] = 9; // Else Stmt List
        correctFollowsMap[9] = 10;
        correctFollowsMap[12] = 13; // While Stmt List
        correctFollowsMap[13] = 14;
        REQUIRE(pkbInterface->followsMap == correctFollowsMap);

        auto correctParentMap = std::unordered_map<int, int>();
        correctParentMap[5] = 4;
        correctParentMap[6] = 4;
        correctParentMap[7] = 4;
        correctParentMap[8] = 4;
        correctParentMap[9] = 4;
        correctParentMap[10] = 4;
        correctParentMap[12] = 11;
        correctParentMap[13] = 11;
        correctParentMap[14] = 11;
        REQUIRE(pkbInterface->parentMapIntInt == correctParentMap);
        REQUIRE(pkbInterface->parentStarMapIntInt == correctParentMap); // only one nesting level

        std::unordered_multimap<int, std::string> modifiesMapIntString = {
                {1, "x"}, // Assign
                {5, "x"},
                {9, "x"},
                {12, "x"},
                {3, "y"}, // Read
                {7, "y"},
                {10,"y"},
                {14, "y"},
                {4, "x"}, // If
                {4, "x"},
                {4, "y"},
                {4, "y"},
                {11, "x"}, // While
                {11, "y"},
        };
        REQUIRE(pkbInterface->modifiesMapIntString == modifiesMapIntString);

        std::unordered_multimap<std::string, std::string> modifiesMapStringString = {
                {"milestone1_nestlevel1", "x"}, // Procedure
                {"milestone1_nestlevel1", "x"},
                {"milestone1_nestlevel1", "x"},
                {"milestone1_nestlevel1", "x"},
                {"milestone1_nestlevel1", "x"},
                {"milestone1_nestlevel1", "x"},
                {"milestone1_nestlevel1", "x"},
                {"milestone1_nestlevel1", "x"},
        };
        REQUIRE(pkbInterface->modifiesMapStringString == modifiesMapStringString);

        std::unordered_multimap<int, std::string> usesMapIntString = {
                {1, "x"},
                {2, "y"},
                {4, "x"}, // If cond
                {5, "x"},
                {4, "x"},
                {6, "y"},
                {4, "y"}, // Copy for If Statement
                {8, "y"},
                {4, "y"},
                {9, "x"},
                {4, "x"},
                {11, "x"},
                {12, "x"},
                {11, "x"},
                {13, "y"},
                {11, "y"},
        };
//        REQUIRE(pkbInterface->usesMapIntString == usesMapIntString);

        std::unordered_multimap<std::string, std::string> usesMapStringString = {
                {"milestone1_nestlevel1", "x"}, // Procedure
                {"milestone1_nestlevel1", "x"},
                {"milestone1_nestlevel1", "x"},
                {"milestone1_nestlevel1", "x"},
                {"milestone1_nestlevel1", "y"},
                {"milestone1_nestlevel1", "y"},
                {"milestone1_nestlevel1", "y"},
                {"milestone1_nestlevel1", "y"},
        };
//        REQUIRE(pkbInterface->usesMapStringString == usesMapStringString);

        delete pkbInterface;
    }

    SECTION("Nesting Level 2") {
        REQUIRE(true);
    }

    SECTION("Nesting Level 3") {
        REQUIRE(true);
    }
}