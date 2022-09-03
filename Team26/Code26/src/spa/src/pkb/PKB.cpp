#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"
#include "VarTable.h"
#include "Variable.h"
#include "ConstantTable.h"
#include "PKBParserInterface.h"

VarTable* PKB::varTable = new VarTable();
ConstantTable* PKB::constantTable = new ConstantTable();

int PKB::setProcToAST(PROC p, TNode* r) {
	return 0;
}

TNode* PKB::getRootAST (PROC p){
	return nullptr;
}

void PKBParserInterface::addVariable(string name) {
    Variable var;
    var.name = name;
    PKB::varTable->insertVar(var);
}

void PKBParserInterface::addConst(int value){
    PKB::constantTable->insertConst(value);
}
