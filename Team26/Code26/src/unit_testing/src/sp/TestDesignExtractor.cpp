#include "sp/de/DesignExtractor.h"
#include "./stubs/PKBInterfaceStubForDE.h"
#include "util/ast/TNode.h"
#include "catch.hpp"

std::shared_ptr<TNode> generateSimpleTNode(int statementNo) {
    return TNode::createTerm(statementNo, "+", std::move(TNode::createVariableName(statementNo, "x")),
                                       std::move(TNode::createConstantValue(statementNo, "1")));
}

std::shared_ptr<TNode> generateTwoVariableTNode(int statementNo) {
    return TNode::createTerm(statementNo, "+", std::move(TNode::createVariableName(statementNo, "x")),
                             std::move(TNode::createVariableName(statementNo, "z")));
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

std::shared_ptr<IfNode> generateTwoNestedIfNode(int startingNo) {
    std::shared_ptr<TNode> condExpr = std::move(generateSimpleCondStmt(startingNo));
    std::shared_ptr<TNode> expr = std::move(generateSimpleTNode(startingNo + 1));
    std::shared_ptr<AssignNode> ifStmt1 = std::move(AssignNode::createAssignNode(startingNo + 1, "x", expr));
    std::shared_ptr<WhileNode> ifStmt2 = std::move(generateSimpleWhileNode(startingNo + 2));

    std::shared_ptr<TNode> expr2 = std::move(generateTwoVariableTNode(startingNo + 6));
    std::shared_ptr<AssignNode> elseStmt1 = std::move(AssignNode::createAssignNode(startingNo + 6, "x", expr2));
    std::shared_ptr<PrintNode> elseStmt2 = std::move(PrintNode::createPrintNode(startingNo + 7, "y"));
    std::shared_ptr<ReadNode> elseStmt3 = std::move(ReadNode::createReadNode(startingNo + 8, "y"));

    std::vector<std::shared_ptr<StatementNode>> ifStmtList = {ifStmt1, ifStmt2};
    std::vector<std::shared_ptr<StatementNode>> elseStmtList = {elseStmt1, elseStmt2, elseStmt3};

    return IfNode::createIfNode(startingNo, condExpr, ifStmtList, elseStmtList);
}

std::shared_ptr<WhileNode> generateTwoNestedWhileLoop(int startingNo) {
    std::shared_ptr<TNode> condExpr = std::move(generateSimpleCondStmt(startingNo));

    std::shared_ptr<TNode> expr = std::move(generateSimpleTNode(startingNo + 1));
    std::shared_ptr<AssignNode> stmt1 = std::move(AssignNode::createAssignNode(startingNo + 1, "x", expr));
    std::shared_ptr<IfNode> stmt2 = std::move(generateSimpleIfNode(startingNo + 2));
    std::vector<std::shared_ptr<StatementNode>> stmtList = {stmt1, stmt2};

    return WhileNode::createWhileNode(startingNo, condExpr, stmtList);
}

std::shared_ptr<ProcedureNode> generateMilestone1TestNestlevel1() {
    std::shared_ptr<TNode> expr = std::move(generateSimpleTNode(1));
    std::shared_ptr<AssignNode> statement1 = std::move(AssignNode::createAssignNode(1, "x", expr));
    std::shared_ptr<PrintNode> statement2 = std::move(PrintNode::createPrintNode(2, "y"));
    std::shared_ptr<ReadNode> statement3 = std::move(ReadNode::createReadNode(3, "y"));
    std::shared_ptr<IfNode> statement4 = std::move(generateSimpleIfNode(4));
    std::shared_ptr<WhileNode> statement5 = std::move(generateSimpleWhileNode(11));
    std::vector<std::shared_ptr<StatementNode>> stmtList = {statement1, statement2, statement3, statement4, statement5};
    return ProcedureNode::createProcedureNode("milestone1NestLevel1", stmtList);
}

std::shared_ptr<ProcedureNode> generateMilestone1TestNestlevel2() {
    std::shared_ptr<TNode> expr = std::move(generateTwoVariableTNode(1));
    std::shared_ptr<AssignNode> statement1 = std::move(AssignNode::createAssignNode(1, "x", expr));
    std::shared_ptr<PrintNode> statement2 = std::move(PrintNode::createPrintNode(2, "y"));
    std::shared_ptr<ReadNode> statement3 = std::move(ReadNode::createReadNode(3, "y"));
    std::shared_ptr<IfNode> statement4 = std::move(generateTwoNestedIfNode(4));
    std::shared_ptr<WhileNode> statement5 = std::move(generateTwoNestedWhileLoop(13));
    std::vector<std::shared_ptr<StatementNode>> stmtList = {statement1, statement2, statement3, statement4, statement5};
    return ProcedureNode::createProcedureNode("milestone1NestLevel2", stmtList);
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
        std::shared_ptr<ProcedureNode> mainNode = std::move(generateMilestone1TestNestlevel1());
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
        //REQUIRE(pkbInterface->parentStarMapIntInt == correctParentMap); // only one nesting level

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
                {"milestone1NestLevel1", "x"}, // Procedure
                {"milestone1NestLevel1", "x"},
                {"milestone1NestLevel1", "x"},
                {"milestone1NestLevel1", "x"},
                {"milestone1NestLevel1", "y"},
                {"milestone1NestLevel1", "y"},
                {"milestone1NestLevel1", "y"},
                {"milestone1NestLevel1", "y"},
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
        REQUIRE(pkbInterface->usesMapIntString == usesMapIntString);

        std::unordered_multimap<std::string, std::string> usesMapStringString = {
                {"milestone1NestLevel1", "x"}, // Procedure
                {"milestone1NestLevel1", "x"},
                {"milestone1NestLevel1", "x"},
                {"milestone1NestLevel1", "x"},
                {"milestone1NestLevel1", "x"},
                {"milestone1NestLevel1", "x"},
                {"milestone1NestLevel1", "y"},
                {"milestone1NestLevel1", "y"},
                {"milestone1NestLevel1", "y"},
                {"milestone1NestLevel1", "y"},
        };
        REQUIRE(pkbInterface->usesMapStringString == usesMapStringString);

        delete pkbInterface;
    }

    SECTION("Nesting Level 2") {
        auto *pkbInterface = new PKBInterfaceStubForDE();
        DesignExtractor designExtractor = DesignExtractor(pkbInterface);
        std::shared_ptr<ProcedureNode> mainNode = std::move(generateMilestone1TestNestlevel2());
        designExtractor.extract(mainNode);

        std::unordered_map<int, int> correctFollowsMap = {
                {1, 2},
                {2, 3},
                {3, 4},
                {5, 6},
                {7, 8},
                {8, 9},
                {10, 11},
                {11, 12},
                {4, 13},
                {14, 15},
                {16, 17},
                {17, 18},
                {19, 20},
                {20, 21}
        };
        REQUIRE(pkbInterface->followsMap == correctFollowsMap);

        std::unordered_map<int, int> correctParentMap = {
                {5,4},
                {6,4},
                {10,4},
                {11,4},
                {12,4},
                {7,6},
                {8,6},
                {9,6},
                {14,13},
                {15,13},
                {16,15},
                {17,15},
                {18,15},
                {19,15},
                {21,15},
                {20,15},
        };

        std::unordered_multimap<int, int> correctParentStarMap = {
                {4,5},
                {4,6},
                {4,10},
                {4,11},
                {4,12},
                {6,7},
                {6,8},
                {6,9},
                {13,14},
                {13,15},
                {15,16},
                {15,17},
                {15,18},
                {15,19},
                {15,20},
                {15,21},
                {4,7},
                {4,8},
                {4,9},
                {13,16},
                {13,17},
                {13,18},
                {13,19},
                {13,20},
                {13,21},
        };

        REQUIRE(pkbInterface->parentMapIntInt == correctParentMap);
        REQUIRE(pkbInterface->parentStarMapIntInt == correctParentStarMap);

        std::unordered_multimap<int, std::string> modifiesMapIntString = {
                {1, "x"}, // Assign
                {3, "y"},
                {5, "x"},
                {7, "x"},
                {9, "y"},
                {10, "x"},
                {12, "y"},
                {6, "x"},
                {6, "y"},
                {4, "x"},
                {4, "x"},
                {4, "y"},
                {4, "x"},
                {4, "y"},
                {14, "x"},
                {13, "x"},
                {13, "x"},
                {15, "x"},
                {16, "x"},
                {13, "y"},
                {15, "y"},
                {18, "y"},
                {13, "x"},
                {15, "x"},
                {20, "x"},
                {13, "y"},
                {15, "y"},
                {21, "y"}
        };

        REQUIRE(pkbInterface->modifiesMapIntString == modifiesMapIntString);

        std::unordered_multimap<std::string, std::string> modifiesMapStringString = {
                {"milestone1NestLevel2", "x"}, // Procedure
                {"milestone1NestLevel2", "x"},
                {"milestone1NestLevel2", "x"},
                {"milestone1NestLevel2", "x"},
                {"milestone1NestLevel2", "x"},
                {"milestone1NestLevel2", "x"},
                {"milestone1NestLevel2", "x"},
                {"milestone1NestLevel2", "y"},
                {"milestone1NestLevel2", "y"},
                {"milestone1NestLevel2", "y"},
                {"milestone1NestLevel2", "y"},
                {"milestone1NestLevel2", "y"}
        };
        REQUIRE(pkbInterface->modifiesMapStringString == modifiesMapStringString);

        std::unordered_multimap<int, std::string> usesMapIntString = {
                {1, "x"},
                {1, "z"},
                {2, "y"},
                {4, "x"}, // If cond
                {5, "x"},
                {4, "x"},
                {6, "x"},
                {4, "x"},
                {7, "x"},
                {6, "x"},
                {4, "x"},
                {8, "y"},
                {6, "y"},
                {4, "y"},
                {10, "x"},
                {10, "z"},
                {4, "x"},
                {4, "z"},
                {11, "y"},
                {4, "y"},
                {13, "x"},
                {14, "x"},
                {13, "x"},
                {15, "x"},
                {13, "x"},
                {16, "x"},
                {15, "x"},
                {13, "x"},
                {17, "y"},
                {15, "y"},
                {13, "y"},
                {20, "x"},
                {15, "x"},
                {13, "x"},
                {19, "y"},
                {15, "y"},
                {13, "y"},
        };
        REQUIRE(pkbInterface->usesMapIntString == usesMapIntString);

        std::unordered_multimap<std::string, std::string> usesMapStringString = {
                {"milestone1NestLevel2", "x"}, // Procedure
                {"milestone1NestLevel2", "x"},
                {"milestone1NestLevel2", "x"},
                {"milestone1NestLevel2", "x"},
                {"milestone1NestLevel2", "x"},
                {"milestone1NestLevel2", "x"},
                {"milestone1NestLevel2", "x"},
                {"milestone1NestLevel2", "x"},
                {"milestone1NestLevel2", "x"},
                {"milestone1NestLevel2", "x"},
                {"milestone1NestLevel2", "x"},
                {"milestone1NestLevel2", "y"},
                {"milestone1NestLevel2", "y"},
                {"milestone1NestLevel2", "y"},
                {"milestone1NestLevel2", "y"},
                {"milestone1NestLevel2", "y"},
                {"milestone1NestLevel2", "z"},
                {"milestone1NestLevel2", "z"}
        };
        REQUIRE(pkbInterface->usesMapStringString == usesMapStringString);
    }

    SECTION("Nesting Level 3") {
        REQUIRE(true);
    }
}