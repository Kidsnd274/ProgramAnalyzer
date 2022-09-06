#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef short PROC;

class TNode;

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer
class ConstantTable;
class ProcedureTable;
class StatementTable;

class PKB {
public:
    static ProcedureTable*  procedureTable;
	static VarTable* varTable;
    static ConstantTable* constantTable;
    static StatementTable* statementTable;
	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST (PROC p);

};