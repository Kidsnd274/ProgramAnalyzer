#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "PKB.h"
#include "util/ast/TNode.h"
#include "VarTable.h"
#include "ConstantTable.h"
#include "ParentTable.h"
#include "ParentStarTable.h"
#include "FollowsTable.h"
#include "FollowsStarTable.h"
#include "CallTable.h"
#include "CallStarTable.h"
#include "ContainerTable.h"

using namespace std;
//using namespace StatementType;

VarTable* PKB::varTable = new VarTable();
ConstantTable* PKB::constantTable = new ConstantTable();
ParentTable* PKB::parentTable = new ParentTable();
ParentStarTable* PKB::parentStarTable = new ParentStarTable();
FollowsTable* PKB::followsTable = new FollowsTable();
FollowsStarTable* PKB::followsStarTable = new FollowsStarTable();
CallTable* PKB::callTable = new CallTable();
CallStarTable* PKB::callStarTable = new CallStarTable();
ContainerTable* PKB::containerTable = new ContainerTable();

int PKB::setProcToAST(PROC p, TNode* r) {
	return 0;
}

TNode* PKB::getRootAST (PROC p){
	return nullptr;
}

