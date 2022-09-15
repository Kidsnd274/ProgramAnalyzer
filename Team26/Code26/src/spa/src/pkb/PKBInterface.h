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

    void addModifies(int statementNumber, string varName);
    void addUses(int statementNumber, string varName);
    void addParent(int parentStatementNumber, int childStatementNumber);
    void addParentStar(int parentStatementNumber, int childStatementNumber);
    void addFollows(int frontStatementNumber, int backStatementNumber);
    void addFollowsStar(int frontStatementNumber, int backStatementNumber);

    vector<string> getAllEntity(EntityType type);
    bool existRelation(RelationStruct relation);

};