#pragma once

#include <iostream>
#include <string>
#include <unordered_set>
#include <cassert>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "qps/QueryProcessorTypes.h"
#include "qps/type/Argument.h"
#include "qps/type/RelationClause.h"
#include "qps/type/Entity.h"
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

using namespace QPS;

class PKBInterface {
public:
    PKB* pkb = new PKB();

    virtual void addProcedure(std::string name, int startingStmtNo, int endingStmtNo, std::shared_ptr<CFGHead> cfg);
    void addItem(Entity::EntityType type, std::string name, int value);

    /**
     * Add IF, WHILE, PRINT, READ statement to statement table.
     * @param type type of the statement
     * @param statementNumber line number of the statement
     * @param statementListNumber number of list which the statement belongs to
     */
    virtual void addStatement(StatementType::StmtType type, int statementNumber, int statementListNumber);
    virtual void addAssignStatement(int statementNumber, int statementListNumber, std::shared_ptr<TNode> rootNode);
    virtual void addCallStatement(int statementNumber, int statementListNumber, std::string calleeProcName);
    virtual void addCondVar(int statementNumber, std::string varName);

    virtual void addRelation(RelationType type, int statementNumber, std::string varName);
    virtual void addRelation(RelationType type, std::string procedureName, std::string name);
    virtual void addRelation(RelationType type, int firstStatementNumber, int SecondStatementNumber);


    virtual std::unordered_set<std::string> getAllUsedOrCalled(RelationType type, std::string procedureName);
    virtual std::unordered_set<int> getParentStar(int statementNumber);


    std::shared_ptr<AssignNode> getAssignTNode(const std::string& assignRef);
    std::unordered_set<std::string> getConditionVar(const std::string& containerRef);


    virtual std::unordered_map<std::string, std::unordered_set<std::string>> getAllProcVarRelation(RelationType type);
    virtual std::unordered_map<int, std::unordered_set<int>> getAllStmtRelation(RelationType type);
    virtual std::unordered_map<int, std::unordered_set<std::string>> getAllStmtVarRelation(RelationType type);


    virtual std::unordered_map<int, int> getAllFollow();
    virtual std::unordered_set<std::unordered_set<Statement*>*> getAllStmtLists();

    /**
     * Get all entities of given type.
     * @param type type of entity
     * @teturn an unordered_set of statement line number, if/while/assign/call/read/print statement line number,
     * variable name, procedure name or constant (as string).
     */
    std::unordered_set<std::string> getAllEntity(Argument::ArgumentType type);


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
