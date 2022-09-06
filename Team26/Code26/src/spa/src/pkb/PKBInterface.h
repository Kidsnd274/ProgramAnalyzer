#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "qps/QueryProcessorTypes.h"
#include "PKB.h"

using namespace std;
using namespace QPS;
typedef short PROC;

class PKBInterface {
public:
    static PKB* pkb;
	//static void addAST (/* Tnode AST */);
    void addProcedure(string name, int startingStmtNo, int endingStmtNo);
    void addVariable(string name);
    void addConst(int value);
    void addReadStatement(int statementNumber);
    void addAssignStatement(int statementNumber);
    void addWhileStatement(int statementNumber);
    void addIfStatement(int statementNumber);
    void addPrintStatement(int statementNumber);
    vector<string> getAllEntity(EntityType type);

};