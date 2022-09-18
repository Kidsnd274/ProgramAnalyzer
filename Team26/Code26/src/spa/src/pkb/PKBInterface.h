#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "qps/QueryProcessorTypes.h"
#include "PKB.h"
#include "util/ast/AssignNode.h"
#include "util/ast/TNode.h"

using namespace std;
using namespace QPS;
typedef short PROC;

class PKBInterface {
public:
    static PKB* pkb;

    static void addProcedure(string name, int startingStmtNo, int endingStmtNo);
    static void addVariable(string name);
    static void addConst(int value);

    virtual void addReadStatement(int statementNumber, int statementListNumber);
    virtual void addAssignStatement(int statementNumber, int statementListNumber, shared_ptr<TNode> rootNode);
    virtual void addWhileStatement(int statementNumber, int statementListNumber);
    virtual void addIfStatement(int statementNumber, int statementListNumber);
    virtual void addPrintStatement(int statementNumber, int statementListNumber);

    virtual void addModifies(int statementNumber, string varName);
    virtual void addModifies(std::string procedureName, std::string varName);
    virtual void addUses(int statementNumber, string varName);
    virtual void addUses(std::string procedureName, std::string varName);
    virtual void addParent(int parentStatementNumber, int childStatementNumber);
    virtual void addParentStar(int parentStatementNumber, int childStatementNumber);
    virtual void addFollows(int frontStatementNumber, int backStatementNumber);
    virtual void addFollowsStar(int frontStatementNumber, int backStatementNumber);

    static vector<string> getAllEntity(EntityType type);
    static bool existRelation(const RelationStruct& relation);
    static shared_ptr<AssignNode> getAssignTNode(const string& assignRef);
};
