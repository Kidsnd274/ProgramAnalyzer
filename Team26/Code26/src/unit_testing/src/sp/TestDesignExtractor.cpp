#include "sp/Parser.h"
#include "./stubs/PKBInterfaceStubForDE.h"
#include "util/ast/TNode.h"
#include "catch.hpp"
#include <unordered_set>

std::string testcalls = "procedure testCalls {read x; call next; call next2;} procedure next {print x; z = y * 3;call last;}procedure last {y = var123;} procedure next2{read x;}";

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

std::shared_ptr<ProcedureNode> generateSimpleProcedureNode(std::string procedureName) {
    std::shared_ptr<TNode> expr = std::move(generateSimpleTNode(1));
    std::shared_ptr<AssignNode> statement1 = std::move(AssignNode::createAssignNode(1, "x", expr));
    std::shared_ptr<PrintNode> statement2 = std::move(PrintNode::createPrintNode(2, "y"));
    std::shared_ptr<ReadNode> statement3 = std::move(ReadNode::createReadNode(3, "z"));
    std::vector<std::shared_ptr<StatementNode>> stmtList = {statement1, statement2, statement3};
    return ProcedureNode::createProcedureNode(procedureName, stmtList);
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

std::shared_ptr<IfNode> generateThreeNestedIfNode(int startingNo) {
    std::shared_ptr<TNode> condExpr = std::move(generateSimpleCondStmt(startingNo));
    std::shared_ptr<TNode> expr = std::move(generateTwoVariableTNode(startingNo + 1));
    std::shared_ptr<AssignNode> ifStmt1 = std::move(AssignNode::createAssignNode(startingNo + 1, "x", expr));
    std::shared_ptr<WhileNode> ifStmt2 = std::move(generateTwoNestedWhileLoop(startingNo + 2));

    // Creating 2 nested while loops
    std::shared_ptr<AssignNode> assignStmt = AssignNode::createAssignNode(startingNo + 12, "x",
                                                                          generateSimpleTNode(startingNo + 12));
    std::shared_ptr<WhileNode> innerWhileLoop = generateSimpleWhileNode(startingNo + 13);

    std::vector<std::shared_ptr<StatementNode>> outerWhileLoopStmtList = {assignStmt, innerWhileLoop};

    std::shared_ptr<WhileNode> elseStmt = std::move(
            WhileNode::createWhileNode(startingNo + 11, generateSimpleCondStmt(startingNo + 11), outerWhileLoopStmtList));

    std::vector<std::shared_ptr<StatementNode>> ifStmtList = {ifStmt1, ifStmt2};
    std::vector<std::shared_ptr<StatementNode>> elseStmtList = {elseStmt};

    return IfNode::createIfNode(startingNo, condExpr, ifStmtList, elseStmtList);
}

std::shared_ptr<WhileNode> generateThreeNestedWhileLoop(int startingNo) {
    std::shared_ptr<TNode> condExpr = std::move(generateSimpleCondStmt(startingNo));

    std::shared_ptr<TNode> expr = std::move(generateTwoVariableTNode(startingNo + 1));
    std::shared_ptr<AssignNode> stmt1 = std::move(AssignNode::createAssignNode(startingNo + 1, "x", expr));
    std::shared_ptr<IfNode> stmt2 = std::move(generateTwoNestedIfNode(startingNo + 2));
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

std::shared_ptr<ProcedureNode> generateMilestone1TestNestlevel3() {
    std::shared_ptr<WhileNode> stmt1 = std::move(generateThreeNestedWhileLoop(1));
    std::shared_ptr<IfNode> stmt2 = std::move(generateThreeNestedIfNode(12));
    return ProcedureNode::createProcedureNode("milestone1NestLevel3", {stmt1, stmt2});
}

// Individual extractor tests
TEST_CASE("FollowsExtractor Tests") {
    SECTION("Extract from Procedure Test") {
        auto *pkbInterface = new PKBInterfaceStubForDE();
        FollowsExtractor followsExtractor = FollowsExtractor(pkbInterface);
        followsExtractor.extractFromProcedure(generateSimpleProcedureNode("simpleTest"));

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
        std::vector<shared_ptr<ProcedureNode>> procedures = {mainNode};
        designExtractor.extract(procedures);

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
        std::vector<shared_ptr<ProcedureNode>> procedures = {mainNode};
        designExtractor.extract(procedures);

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

        delete pkbInterface;
    }

    SECTION("Nesting Level 3") {
        auto *pkbInterface = new PKBInterfaceStubForDE();
        DesignExtractor designExtractor = DesignExtractor(pkbInterface);
        std::shared_ptr<ProcedureNode> mainNode = std::move(generateMilestone1TestNestlevel3());
        std::vector<shared_ptr<ProcedureNode>> procedures = {mainNode};
        designExtractor.extract(procedures);

        std::unordered_map<int, int> correctFollowsMap = {
                {2, 3},
                {4, 5},
                {6, 7},
                {7, 8},
                {9, 10},
                {10, 11},
                {13, 14},
                {15, 16},
                {17, 18},
                {18, 19},
                {20, 21},
                {21, 22},
                {24, 25},
                {26, 27},
                {27, 28},
                {1, 12}
        };

        REQUIRE(pkbInterface->followsMap == correctFollowsMap);

        std::unordered_map<int, int> correctParentMap = {
                {2,1},
                {3,1},
                {4,3}, // 2nd nested If Statement
                {5,3},
                {9,3},
                {10,3},
                {11,3},
                {6,5},
                {7,5},
                {8,5},
                {13,12},
                {14,12},
                {15,14}, // 2nd nested While Statement
                {16,14},
                {17,16},
                {18,16},
                {19,16},
                {20,16},
                {21,16},
                {22,16},
                {23,12},
                {24,23},
                {25,23},
                {26,25},
                {27,25},
                {28,25}
        };

        std::unordered_multimap<int, int> correctParentStarMap = {
                {1,2},
                {1,3},
                {3,4}, // 2nd nested If Statement
                {1,4},
                {3,5},
                {1,5},
                {3,9},
                {1,9},
                {3,10},
                {1,10},
                {3,11},
                {1,11},
                {5,6},
                {3,6},
                {1,6},
                {5,7},
                {3,7},
                {1,7},
                {5,8},
                {3,8},
                {1,8},
                {12,13},
                {12,14},
                {14,15}, // 2nd nested While Statement
                {12,15},
                {14,16},
                {12,16},
                {16,17},
                {14,17},
                {12,17},
                {16,18},
                {14,18},
                {12,18},
                {16,19},
                {14,19},
                {12,19},
                {16,20},
                {14,20},
                {12,20},
                {16,21},
                {14,21},
                {12,21},
                {16,22},
                {14,22},
                {12,22},
                {12,23},
                {23,24},
                {12,24},
                {23,25},
                {12,25},
                {25,26},
                {23,26},
                {12,26},
                {25,27},
                {23,27},
                {12,27},
                {25,28},
                {23,28},
                {12,28}
        };

        REQUIRE(pkbInterface->parentMapIntInt == correctParentMap);
        REQUIRE(pkbInterface->parentStarMapIntInt == correctParentStarMap);

        std::unordered_multimap<int, std::string> modifiesMapIntString = {
                {2, "x"}, // Assign
                {1, "x"},
                {4, "x"},
                {3, "x"},
                {1, "x"},
                {6, "x"},
                {5, "x"},
                {3, "x"},
                {1, "x"},
                {8, "y"},
                {5, "y"},
                {3, "y"},
                {1, "y"},
                {9, "x"},
                {3, "x"},
                {1, "x"},
                {11, "y"},
                {3, "y"},
                {1, "y"},
                {13, "x"},
                {12, "x"},
                {15, "x"},
                {14, "x"},
                {12, "x"},
                {17, "x"},
                {16, "x"},
                {14, "x"},
                {12, "x"},
                {19, "y"},
                {16, "y"},
                {14, "y"},
                {12, "y"},
                {21, "x"},
                {16, "x"},
                {14, "x"},
                {12, "x"},
                {22, "y"},
                {16, "y"},
                {14, "y"},
                {12, "y"},
                {24, "x"},
                {23, "x"},
                {12, "x"},
                {26, "x"},
                {25, "x"},
                {23, "x"},
                {12, "x"},
                {28, "y"},
                {25, "y"},
                {23, "y"},
                {12, "y"}
        };

        REQUIRE(pkbInterface->modifiesMapIntString == modifiesMapIntString);

        std::unordered_multimap<std::string, std::string> modifiesMapStringString = {
                {"milestone1NestLevel3", "x"}, // Procedure
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "y"},
                {"milestone1NestLevel3", "y"},
                {"milestone1NestLevel3", "y"},
                {"milestone1NestLevel3", "y"},
                {"milestone1NestLevel3", "y"}
        };
        REQUIRE(pkbInterface->modifiesMapStringString == modifiesMapStringString);

        std::unordered_multimap<int, std::string> usesMapIntString = {
                {1, "x"},
                {2, "x"},
                {1, "x"},
                {2, "z"},
                {1, "z"},
                {3, "x"}, // If cond
                {1, "x"},
                {4, "x"},
                {3, "x"},
                {1, "x"},
                {5, "x"}, // While cond
                {3, "x"},
                {1, "x"},
                {6, "x"},
                {5, "x"},
                {3, "x"},
                {1, "x"},
                {7, "y"},
                {5, "y"},
                {3, "y"},
                {1, "y"},
                {9, "x"},
                {3, "x"},
                {1, "x"},
                {9, "z"},
                {3, "z"},
                {1, "z"},
                {10, "y"},
                {3, "y"},
                {1, "y"},
                {12, "x"},
                {13, "x"},
                {12, "x"},
                {13, "z"},
                {12, "z"},
                {14, "x"},
                {12, "x"},
                {15, "x"},
                {14, "x"},
                {12, "x"},
                {16, "x"},
                {14, "x"},
                {12, "x"},
                {17, "x"},
                {16, "x"},
                {14, "x"},
                {12, "x"},
                {18, "y"},
                {16, "y"},
                {14, "y"},
                {12, "y"},
                {20, "y"},
                {16, "y"},
                {14, "y"},
                {12, "y"},
                {21, "x"},
                {16, "x"},
                {14, "x"},
                {12, "x"},
                {23, "x"},
                {12, "x"},
                {24, "x"},
                {23, "x"},
                {12, "x"},
                {25, "x"},
                {23, "x"},
                {12, "x"},
                {26, "x"},
                {25, "x"},
                {23, "x"},
                {12, "x"},
                {27, "y"},
                {25, "y"},
                {23, "y"},
                {12, "y"},
        };

        REQUIRE(pkbInterface->usesMapIntString == usesMapIntString);

        std::unordered_multimap<std::string, std::string> usesMapStringString = {
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "x"},
                {"milestone1NestLevel3", "y"},
                {"milestone1NestLevel3", "y"},
                {"milestone1NestLevel3", "y"},
                {"milestone1NestLevel3", "y"},
                {"milestone1NestLevel3", "y"},
                {"milestone1NestLevel3", "z"},
                {"milestone1NestLevel3", "z"},
                {"milestone1NestLevel3", "z"}
        };
        REQUIRE(pkbInterface->usesMapStringString == usesMapStringString);

        delete pkbInterface;
    }
}

TEST_CASE("Test multiple procedures") {
    SECTION("2 basic procedures") {
        auto *pkbInterface = new PKBInterfaceStubForDE();
        DesignExtractor designExtractor = DesignExtractor(pkbInterface);
        std::shared_ptr<ProcedureNode> proc1 = std::move(generateSimpleProcedureNode("main1"));
        std::shared_ptr<ProcedureNode> proc2 = std::move(generateSimpleProcedureNode("second2131"));
        std::vector<shared_ptr<ProcedureNode>> procedures = {proc1, proc2};
        designExtractor.extract(procedures);

        std::unordered_multimap<std::string, std::string> usesMapStringString = {
                {"main1", "y"},
                {"second2131", "y"},
                {"main1", "x"},
                {"second2131", "x"},
        };

        REQUIRE(pkbInterface->usesMapStringString == usesMapStringString);

        std::unordered_multimap<std::string, std::string> modifiesMapStringString = {
                {"main1", "x"},
                {"second2131", "x"},
                {"main1", "z"},
                {"second2131", "z"},
        };

        REQUIRE(pkbInterface->modifiesMapStringString == modifiesMapStringString);

        delete pkbInterface;
    }
}

TEST_CASE("Test call procedures with call statements") {
    SECTION("Basic 3 procedure test") {
        auto *pkbInterface = new PKBInterfaceStubForDE();
        DesignExtractor designExtractor = DesignExtractor(pkbInterface);

//        //procedure 1
//        std::shared_ptr<ReadNode> statement1 = std::move(ReadNode::createReadNode(1, "x"));
//        std::shared_ptr<CallNode> statement2 = std::move(CallNode::createCallNode(2, "next"));
//        std::vector<std::shared_ptr<StatementNode>> stmtList1 = {statement1, statement2};
//        std::shared_ptr<ProcedureNode> proc1 = std::move(ProcedureNode::createProcedureNode("testCalls", stmtList1));
//
//        //procedure 2
//        std::shared_ptr<PrintNode> stmt1 = PrintNode::createPrintNode(3, "x");
//        std::shared_ptr<TNode> stmt2expr = TNode::createTerm(4, "*", TNode::createVariableName(4, "y"), TNode::createConstantValue(4, "3"));
//        std::shared_ptr<AssignNode> stmt2 = AssignNode::createAssignNode(4, "y", stmt2expr);
//        std::shared_ptr<CallNode> stmt3 = CallNode::createCallNode(5, "last");
//        std::shared_ptr<ProcedureNode> proc2 = ProcedureNode::createProcedureNode("next", {stmt1, stmt2, stmt3});
//
//        //procedure 3
//        std::shared_ptr<TNode> expr = std::move(TNode::createVariableName(6, "var123"));
//        std::shared_ptr<AssignNode> stmt = std::move(AssignNode::createAssignNode(6, "y", expr));
//        std::vector<std::shared_ptr<StatementNode>> stmtList3 = {stmt};
//        std::shared_ptr<ProcedureNode> proc3 = std::move(ProcedureNode::createProcedureNode("last", stmtList3));
//
//        std::vector<shared_ptr<ProcedureNode>> procedures = {proc1, proc2, proc3};
        //designExtractor.extract(procedures);
        Lexer l(testcalls);
        Parser p(l.tokenize(), pkbInterface);
        p.parseSimple();

        std::unordered_set<std::string> proc1Modified = {"x", "z", "y"};
        std::unordered_set<std::string> proc1Used = {"x", "y", "var123"};
        std::unordered_set<std::string> proc2Modified = {"z", "y"};
        std::unordered_set<std::string> proc2Used = {"x", "y", "var123"};
        std::unordered_set<std::string> proc3Modified = {"y"};
        std::unordered_set<std::string> proc3Used = {"var123"};

        std::unordered_set<std::string> proc1Called = { "next", "next2" };
        std::unordered_set<std::string> proc2Called = { "last" };
        std::unordered_set<std::string> proc3Called = { };
        std::unordered_set<std::string> proc1CalledStar = { "next", "last", "next2" };
        std::unordered_set<std::string> proc2CalledStar = { "last" };
        std::unordered_set<std::string> proc3CalledStar = { };

        REQUIRE(proc1Modified == pkbInterface->getAllVariablesModified("testCalls"));
        REQUIRE(proc2Modified == pkbInterface->getAllVariablesModified("next"));
        REQUIRE(proc3Modified == pkbInterface->getAllVariablesModified("last"));

        REQUIRE(proc1Used == pkbInterface->getAllVariablesUsed("testCalls"));
        REQUIRE(proc2Used == pkbInterface->getAllVariablesUsed("next"));
        REQUIRE(proc3Used == pkbInterface->getAllVariablesUsed("last"));

        REQUIRE(proc1Called == pkbInterface->getCall("testCalls"));
        REQUIRE(proc2Called == pkbInterface->getCall("next"));
        REQUIRE(proc3Called == pkbInterface->getCall("last"));

        REQUIRE(proc1CalledStar == pkbInterface->getCallStar("testCalls"));
        REQUIRE(proc2CalledStar == pkbInterface->getCallStar("next"));
        REQUIRE(proc3CalledStar == pkbInterface->getCallStar("last"));
    }
}