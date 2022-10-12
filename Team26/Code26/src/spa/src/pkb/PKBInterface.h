#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_set>

#include "qps/QueryProcessorTypes.h"
#include "PKB.h"
#include "util/ast/AssignNode.h"
#include "util/ast/TNode.h"

using namespace std;
using namespace QPS;
typedef short PROC;

class PKBInterface {
public:
    PKB* pkb = new PKB();

    void addProcedure(string name, int startingStmtNo, int endingStmtNo);
    void addVariable(string name);
    void addConst(int value);

    virtual void addReadStatement(int statementNumber, int statementListNumber);
    virtual void addAssignStatement(int statementNumber, int statementListNumber, shared_ptr<TNode> rootNode);
    virtual void addWhileStatement(int statementNumber, int statementListNumber);
    virtual void addIfStatement(int statementNumber, int statementListNumber);
    virtual void addPrintStatement(int statementNumber, int statementListNumber);
    virtual void addCallStatement(int statementNumber, int statementListNumber);

    virtual void addModifies(int statementNumber, string varName);
    virtual void addModifies(std::string procedureName, std::string varName);
    virtual void addUses(int statementNumber, string varName);
    virtual void addUses(std::string procedureName, std::string varName);
    virtual void addParent(int parentStatementNumber, int childStatementNumber);
    virtual void addParentStar(int parentStatementNumber, int childStatementNumber);
    virtual void addFollows(int frontStatementNumber, int backStatementNumber);
    virtual void addFollowsStar(int frontStatementNumber, int backStatementNumber);
    virtual void addCall(std::string procedureName, std::string procedureCalled);
    virtual void addCallStar(std::string procedureName, std::string procedureCalled);


    virtual std::unordered_set<std::string> getAllVariablesModified(std::string procedureName);
    virtual std::unordered_set<std::string> getAllVariablesUsed(std::string procedureName);
    virtual std::unordered_set<int> getParentStar(int statementNumber);
    virtual std::unordered_set<string> getCall(std::string procedure);
    virtual std::unordered_set<string> getCallStar(std::string procedure);


    vector<string> getAllEntity(EntityType type);
    bool existRelation(const RelationStruct& relation);
    shared_ptr<AssignNode> getAssignTNode(const string& assignRef);

    virtual unordered_map<std::string, std::vector<std::string>> getAllCall();
    virtual unordered_map<std::string, std::vector<std::string>> getAllCallStar();
//    virtual unordered_map<std::string, std::vector<std::string>> getAllFollow();
//    virtual unordered_map<std::string, std::vector<std::string>> getAllFollowStar();
//    virtual unordered_map<std::string, std::vector<std::string>> getAllModify();
//    virtual unordered_map<std::string, std::vector<std::string>> getAllParent();
//    virtual unordered_map<std::string, std::vector<std::string>> getAllParentStar();
//    virtual unordered_map<std::string, std::vector<std::string>> getAllUse();
};
