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

    // Methods for Design Extractor
    void addFollows(int stmt1Number, int stmt2Number);
    void addModifies(int stmtNumber, std::string varModified);
    void addModifies(std::string procedureName, std::string varModified);
    void addParent(int parentStmtNumber, int stmtNumber);
    void addParentStar(int parentStmtNumber, int stmtNumber); // TODO: might let qps handle in the future
    void addUses(int stmtNumber, std::string variableUsed);
    void addUses(std::string procedureName, std::string variableUsed);
};