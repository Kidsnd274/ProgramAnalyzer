#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_set>

#include "qps/QueryProcessorTypes.h"
#include "PKB.h"
#include "Statement.h"
#include "util/ast/AssignNode.h"
#include "util/ast/TNode.h"
#include "util/cfg/CFGHead.h"

using namespace std;
using namespace QPS;
typedef short PROC;

class PKBInterface {
public:
    PKB* pkb = new PKB();

    void addProcedure(string name, int startingStmtNo, int endingStmtNo, std::shared_ptr<CFGHead> cfg);
    void addVariable(string name);
    void addConst(int value);

    virtual void addReadStatement(int statementNumber, int statementListNumber);
    virtual void addAssignStatement(int statementNumber, int statementListNumber, std::shared_ptr<TNode> rootNode);
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


    shared_ptr<AssignNode> getAssignTNode(const string& assignRef);

    virtual unordered_map<std::string, std::vector<std::string>> getAllCall();
    virtual unordered_map<std::string, std::vector<std::string>> getAllCallStar();
    virtual unordered_map<int,int> getAllFollow();
    virtual unordered_map<int,int> getAllFollowStar();
    virtual unordered_map<int, std::vector<std::string>> getAllModifyByStmt();
    virtual unordered_map<std::string, std::vector<std::string>> getAllModifyByProc();
    virtual unordered_map<int, std::vector<int>> getAllParent();
    virtual unordered_map<int, std::vector<int>> getAllParentStar();
    virtual unordered_map<int, std::vector<std::string>> getAllUseByStmt();
    virtual unordered_map<std::string, std::vector<std::string>> getAllUseByProc();
    virtual std::vector<vector<Statement>> getAllStmtLists();

    vector<string> getAllStmts();
    vector<string> getAllReads();
    vector<string> getAllPrints();
    vector<string> getAllCalls();
    vector<string> getAllWhiles();
    vector<string> getAllIfs();
    vector<string> getAllAssigns();
    vector<string> getAllVariables();
    vector<string> getAllConstants();
    vector<string> getAllProcedures();


    virtual std::string getProcLineNumberByName(std::string procName);
    virtual std::string getCallProcName(std::string callLineNumber);
    virtual std::string getReadVarName(std::string readLineNumber);
    virtual std::string getPrintVarName(std::string printLineNumber);
};
