#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "util/ast/TNode.h"
#include "ProcedureTable.h"
#include "VarTable.h"
#include "ConstantTable.h"
#include "StatementTable.h"
#include "ModifiesTable.h"
#include "UsesTable.h"
#include "ParentTable.h"
#include "ParentStarTable.h"
#include "FollowsTable.h"
#include "FollowsStarTable.h"
#include "CallTable.h"
#include "CallStarTable.h"
#include "ContainerTable.h"
#include "NextTable.h"
#include "NextStarTable.h"
#include "AffectTable.h"
#include "AffectStarTable.h"

typedef int PROC;

class PKB {
public:
    ProcedureTable* procedureTable;
    VarTable* varTable;
    ConstantTable* constantTable;
    StatementTable* statementTable;
    ModifiesTable* modifiesTable;
    UsesTable* usesTable;
    ParentTable* parentTable;
    ParentStarTable* parentStarTable;
    FollowsTable* followsTable;
    FollowsStarTable* followsStarTable;
    CallTable* callTable;
    CallStarTable* callStarTable;
    ContainerTable* containerTable;
    NextTable* nextTable;
    NextStarTable* nextStarTable;
    AffectTable* affectTable;
    AffectStarTable* affectStarTable;
    PKB() {
        procedureTable = new ProcedureTable();
        varTable = new VarTable();
        constantTable = new ConstantTable();
        statementTable = new StatementTable();
        modifiesTable = new ModifiesTable();
        usesTable = new UsesTable();
        parentTable = new ParentTable();
        parentStarTable = new ParentStarTable();
        followsTable = new FollowsTable;
        followsStarTable = new FollowsStarTable();
        callTable = new CallTable();
        callStarTable = new CallStarTable();
        containerTable = new ContainerTable();
        nextTable = new NextTable();
        nextStarTable = new NextStarTable();
        affectTable = new AffectTable();
        affectStarTable = new AffectStarTable();
    }
    int setProcToAST(PROC p, TNode* r);
    TNode* getRootAST(PROC p);
};
