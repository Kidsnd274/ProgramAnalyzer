#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "PKB.h"
#include "util/ast/TNode.h"
#include "VarTable.h"
#include "ConstantTable.h"
#include "ProcedureTable.h"
#include "StatementTable.h"

using namespace std;
//using namespace StatementType;

ProcedureTable* PKB::procedureTable = new ProcedureTable();
VarTable* PKB::varTable = new VarTable();
ConstantTable* PKB::constantTable = new ConstantTable();
StatementTable* PKB::statementTable = new StatementTable();

int PKB::setProcToAST(PROC p, TNode* r) {
	return 0;
}

TNode* PKB::getRootAST (PROC p){
	return nullptr;
}

