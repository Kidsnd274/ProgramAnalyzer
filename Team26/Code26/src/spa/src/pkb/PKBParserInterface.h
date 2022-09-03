#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef short PROC;

class PKBParserInterface {
public:
	//static void addAST (/* Tnode AST */);
    void addProcedure(string name, int startingStmtNo, int endingStmtNo);
    void addVariable(string name);
    void addConst(int value);
    void addReadStatement(int statementNumber);
    void addAssignStatement(int statementNumber);
    void addWhileStatement(int statementNumber);
    void addIfStatement(int statementNumber);
    void addPrintStatement(int statementNumber);

};