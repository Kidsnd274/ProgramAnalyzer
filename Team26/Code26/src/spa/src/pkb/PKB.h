#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "StatementTable.h"
#include "UsesTable.h"

using namespace std;
typedef short PROC;

class TNode;

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer
class ConstantTable;
class ProcedureTable;
class ModifiesTable;
class ParentTable;
class ParentStarTable;
class FollowsTable;
class FollowsStarTable;
class CallTable;
class CallStarTable;

class PKB {
public:
    static ProcedureTable* procedureTable;
	static VarTable* varTable;
    static ConstantTable* constantTable;
    StatementTable* statementTable = new StatementTable();
    static ModifiesTable* modifiesTable;
    UsesTable* usesTable = new UsesTable();
    static ParentTable* parentTable;
    static ParentStarTable* parentStarTable;
    static FollowsTable* followsTable;
    static FollowsStarTable* followsStarTable;
    static CallTable* callTable;
    static CallStarTable* callStarTable;
	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST (PROC p);
};