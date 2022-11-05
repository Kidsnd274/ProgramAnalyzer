#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_set>
#include <cassert>
#include <memory>
#include <unordered_set>
#include <utility>

#include "qps/QueryProcessorTypes.h"
#include "PKB.h"
#include "Statement.h"
#include "util/ast/AssignNode.h"
#include "util/ast/TNode.h"
#include "util/cfg/CFGHead.h"
#include "ProcedureTable.h"
#include "StatementTable.h"
#include "ModifiesTable.h"
#include "ParentStarTable.h"
#include "ContainerTable.h"
#include "ProcedureNotFoundException.h"
#include "NextStarTable.h"

using namespace std;
using namespace QPS;
typedef short PROC;

class PKBInterface {
public:
    PKB* pkb = new PKB();

    virtual void addProcedure(std::string name, int startingStmtNo, int endingStmtNo, std::shared_ptr<CFGHead> cfg);
    void addVariable(std::string name);
    void addConst(int value);

    virtual void addStatement(StatementType::StmtType type, int statementNumber, int statementListNumber,
                              std::shared_ptr<TNode> rootNode, std::string calleeProcName);
    virtual void addReadStatement(int statementNumber, int statementListNumber);
    virtual void addAssignStatement(int statementNumber, int statementListNumber, std::shared_ptr<TNode> rootNode);
    virtual void addWhileStatement(int statementNumber, int statementListNumber);
    virtual void addIfStatement(int statementNumber, int statementListNumber);
    virtual void addPrintStatement(int statementNumber, int statementListNumber);
    virtual void addCallStatement(int statementNumber, int statementListNumber, std::string calleeProcName);
    virtual void addCondVar(int statementNumber, string varName);

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
    unordered_set<string> getConditionVar(const string& containerRef);

    virtual unordered_map<std::string, std::unordered_set<std::string>> getAllCall();
    virtual unordered_map<std::string, std::unordered_set<std::string>> getAllCallStar();
    virtual unordered_map<int,int> getAllFollow();
    virtual unordered_map<int,int> getAllFollowStar();
    virtual unordered_map<int, unordered_set<int>> getAllNext();
    virtual std::unordered_map<STMT_NUM, std::unordered_set<STMT_NUM>> getAllNextStar();
    virtual unordered_map<int, std::unordered_set<int>> getAllAffects();
    virtual unordered_map<int, std::unordered_set<int>> getAllAffectsStar();
    virtual unordered_map<int, std::unordered_set<std::string>> getAllModifyByStmt();
    virtual unordered_map<std::string, std::unordered_set<std::string>> getAllModifyByProc();
    virtual unordered_map<int, std::unordered_set<int>> getAllParent();
    virtual unordered_map<int, std::unordered_set<int>> getAllParentStar();
    virtual unordered_map<int, std::unordered_set<std::string>> getAllUseByStmt();
    virtual unordered_map<std::string, std::unordered_set<std::string>> getAllUseByProc();
    virtual std::unordered_set<unordered_set<Statement*>*> getAllStmtLists();

    unordered_set<string> getAllStmts();
    unordered_set<string> getAllReads();
    unordered_set<string> getAllPrints();
    unordered_set<string> getAllCalls();
    unordered_set<string> getAllWhiles();
    unordered_set<string> getAllIfs();
    unordered_set<string> getAllAssigns();
    unordered_set<string> getAllVariables();
    unordered_set<string> getAllConstants();
    unordered_set<string> getAllProcedures();


    virtual std::string getProcLineNumberByName(std::string procName);
    virtual std::string getCallProcName(std::string callLineNumber);
    virtual std::string getReadVarName(std::string readLineNumber);
    virtual std::string getPrintVarName(std::string printLineNumber);


    CFGHeadPtr getCfgOfProcedure(std::string procedureName);
    virtual bool hasNextStar(STMT_NUM stmt);
    virtual void addNextStar(STMT_NUM stmt, std::unordered_set<STMT_NUM> nextStarSet);
    virtual bool isStatementContainer(STMT_NUM stmt);
    virtual bool doesStatementModify(STMT_NUM stmt, std::string varModified);
    virtual bool hasAffects(STMT_NUM stmt);
    virtual std::string getModifiedVariable(STMT_NUM stmt);
    virtual bool isStatementAssign(STMT_NUM stmt);
    virtual bool doesStatementUse(STMT_NUM stmt, std::string varUsed);
    virtual void addAffects(STMT_NUM stmt, STMT_NUM affectedStmt);
    virtual std::unordered_set<STMT_NUM> getAffects(STMT_NUM stmt);
    virtual std::unordered_set<STMT_NUM> getAffectsStar(STMT_NUM stmt);
    virtual std::string getProcedureNameOf(CFGHeadPtr cfg);
    virtual bool hasAffectsStar(STMT_NUM stmt);
    virtual void addAffectsStar(STMT_NUM stmt, std::unordered_set<STMT_NUM> affectsStarSet);
    virtual std::unordered_set<STMT_NUM> getAllAssignFromProcedure(std::string procName);

    virtual std::unordered_set<STMT_NUM> getNextStar(STMT_NUM stmt);
    virtual CFGHeadPtr getCFGHeadPtrByProc(STMT_NUM stmt);
    virtual Procedure* getProcByStmt(STMT_NUM stmt);
    virtual std::unordered_set<Procedure*> getProcList();

    /**
     * Clear NextStar, Affect and AffectStar Tables.
     */
    virtual void clear();
};
