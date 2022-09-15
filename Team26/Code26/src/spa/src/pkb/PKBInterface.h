#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "qps/QueryProcessorTypes.h"
#include "PKB.h"

using namespace std;
using namespace QPS;
typedef short PROC;

class PKBInterface {
public:
    static PKB* pkb;

    void addProcedure(string name, int startingStmtNo, int endingStmtNo);
    void addVariable(string name);
    void addConst(int value);
    void addReadStatement(int statementNumber, int statementListNumber);
    void addAssignStatement(int statementNumber, int statementListNumber, shared_ptr<TNode> rootNode);
    void addWhileStatement(int statementNumber, int statementListNumber);
    void addIfStatement(int statementNumber, int statementListNumber);
    void addPrintStatement(int statementNumber, int statementListNumber);

    void addModifies(int statementNumber, string varName);
    void addUses(int statementNumber, string varName);
    void addParent(int parentStatementNumber, int childStatementNumber);
    void addParentStar(int parentStatementNumber, int childStatementNumber);
    void addFollows(int frontStatementNumber, int backStatementNumber);
    void addFollowsStar(int frontStatementNumber, int backStatementNumber);

    vector<string> getAllEntity(EntityType type);
    bool existRelation(RelationStruct relation);
    shared_ptr<AssignNode> getAssignTNode(string assignRef);
};
