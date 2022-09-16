//
// Created by QMS on 4/9/2022.
//

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <memory>

#include "PKB.h"
#include "util/ast/TNode.h"
#include "VarTable.h"
#include "ConstantTable.h"
#include "ProcedureTable.h"
#include "StatementTable.h"
#include "PKBInterface.h"
#include "ModifiesTable.h"
#include "UsesTable.h"
#include "ParentTable.h"
#include "ParentStarTable.h"
#include "FollowsTable.h"
#include "FollowsStarTable.h"

using namespace std;
//using namespace StatementType;

PKB* PKBInterface::pkb = new PKB();

void PKBInterface::addProcedure(std::string name, int startingStmtNo, int endingStmtNo) {
    Procedure proc;
    proc.name = name;
    proc.startingStmtNo = startingStmtNo;
    proc.endingStmtNo = endingStmtNo;
    pkb->procedureTable->insertProc(proc);
}

void PKBInterface::addVariable(string name) {
    pkb->varTable->insertVar(name);
}

void PKBInterface::addConst(int value) {
    pkb->constantTable->insertConst(value);
}

void PKBInterface::addReadStatement(int statementNumber, int statementListNumber) {
    Statement stmt;
    stmt.type = StatementType::READ;
    stmt.lineNumber = statementNumber;
    stmt.statementListNumber = statementListNumber;
    pkb->statementTable->insertStmt(stmt);
}

void PKBInterface::addAssignStatement(int statementNumber, int statementListNumber, shared_ptr<TNode> rootNode) {
    Statement stmt;
    stmt.type = StatementType::ASSIGN;
    stmt.lineNumber = statementNumber;
    stmt.statementListNumber = statementListNumber;
    stmt.rootNode = rootNode;
    pkb->statementTable->insertStmt(stmt);
}

void PKBInterface::addWhileStatement(int statementNumber, int statementListNumber) {
    Statement stmt;
    stmt.type = StatementType::WHILE;
    stmt.lineNumber = statementNumber;
    stmt.statementListNumber = statementListNumber;
    pkb->statementTable->insertStmt(stmt);
}

void PKBInterface::addIfStatement(int statementNumber, int statementListNumber) {
    Statement stmt;
    stmt.type = StatementType::IF;
    stmt.lineNumber = statementNumber;
    stmt.statementListNumber = statementListNumber;
    pkb->statementTable->insertStmt(stmt);
}

void PKBInterface::addPrintStatement(int statementNumber, int statementListNumber) {
    Statement stmt;
    stmt.type = StatementType::PRINT;
    stmt.lineNumber = statementNumber;
    stmt.statementListNumber = statementListNumber;
    pkb->statementTable->insertStmt(stmt);
}

void PKBInterface::addModifies(int statementNumber, string varName) {
    pkb->modifiesTable->insertModifies(statementNumber, varName);
}

void PKBInterface::addUses(int statementNumber, string varName) {
    pkb->usesTable->insertUses(statementNumber, varName);
}

void PKBInterface::addParent(int parentStatementNumber, int childStatementNumber) {
    pkb->parentTable->insertParent(parentStatementNumber, childStatementNumber);
}

void PKBInterface::addParentStar(int parentStatementNumber, int childStatementNumber) {
    pkb->parentStarTable->insertParentStar(parentStatementNumber, childStatementNumber);
}

void PKBInterface::addFollows(int frontStatementNumber, int backStatementNumber) {
    pkb->followsTable->insertFollows(frontStatementNumber, backStatementNumber);
}

void PKBInterface::addFollowsStar(int frontStatementNumber, int backStatementNumber) {
    pkb->followsStarTable->insertFollowsStar(frontStatementNumber, backStatementNumber);
}

vector<string> PKBInterface::getAllEntity(EntityType type) {
    vector<string> result;
    switch (type) {
        case QPS::STATEMENT:
            result = pkb->statementTable->getAllStmts();
            break;
        case QPS::READ:
            result = pkb->statementTable->getAllReads();
            break;
        case QPS::PRINT:
            result = pkb->statementTable->getAllPrints();
            break;
        case QPS::CALL:
            result = pkb->statementTable->getAllCalls();
            break;
        case QPS::WHILE:
            result = pkb->statementTable->getAllWhiles();
            break;
        case QPS::IF:
            result = pkb->statementTable->getAllIfs();
            break;
        case QPS::ASSIGN:
            result = pkb->statementTable->getAllAssigns();
            break;
        case QPS::VARIABLE:
            result = pkb->varTable->getAllVariables();
            break;
        case QPS::CONSTANT:
            result = pkb->constantTable->getAllConstants();
            break;
        case QPS::PROCEDURE:
            result = pkb->procedureTable->getAllProcedures();
            break;
//        case QPS::INVALID_ENTITY_TYPE:
//            break;
        default:
            break;
    }
    return result;
}

bool PKBInterface::existRelation(RelationStruct relation) {
    RelationType typeOfRelation = relation.typeOfRelation;
    ArgumentStruct arg1 = relation.arg1;
    ArgumentStruct arg2 = relation.arg2;
    bool result;
    switch (typeOfRelation) {
        case QPS::FOLLOWS:
//            assert(arg1.typeOfArgument == QPS::STMT_SYNONYM);
//            assert(arg2.typeOfArgument == QPS::STMT_SYNONYM);
            result = pkb->followsTable->existFollows(stoi(arg1.nameOfArgument), stoi(arg2.nameOfArgument));
            break;
        case QPS::FOLLOWS_T:
//            assert(arg1.typeOfArgument == QPS::STMT_SYNONYM);
//            assert(arg2.typeOfArgument == QPS::STMT_SYNONYM);
            result = pkb->followsStarTable->existFollowsStar(stoi(arg1.nameOfArgument), stoi(arg2.nameOfArgument));
            break;
        case QPS::PARENT:
//            assert(arg1.typeOfArgument == QPS::STMT_SYNONYM);
//            assert(arg2.typeOfArgument == QPS::STMT_SYNONYM);
            result = pkb->parentTable->existParent(stoi(arg1.nameOfArgument), stoi(arg2.nameOfArgument));
            break;
        case QPS::PARENT_T:
//            assert(arg1.typeOfArgument == QPS::STMT_SYNONYM);
//            assert(arg2.typeOfArgument == QPS::STMT_SYNONYM);
            result = pkb->parentStarTable->existParentStar(stoi(arg1.nameOfArgument), stoi(arg2.nameOfArgument));
            break;
        case QPS::MODIFIES_S:
//            assert(arg1.typeOfArgument == QPS::STMT_SYNONYM);
//            assert(arg2.typeOfArgument == QPS::VAR_SYNONYM);
            result = pkb->modifiesTable->existModifies(stoi(arg1.nameOfArgument), arg2.nameOfArgument);
            break;
        case QPS::USES_S:
//            assert(arg1.typeOfArgument == QPS::STMT_SYNONYM);
//            assert(arg2.typeOfArgument == QPS::VAR_SYNONYM);
            result = pkb->usesTable->existUses(stoi(arg1.nameOfArgument), arg2.nameOfArgument);
            break;
        default:
            result = false;
            break;
    }
    return result;
}

shared_ptr<AssignNode> PKBInterface::getAssignTNode(string assignRef) {
    int assignStmtNo = stoi(assignRef);
    assert(pkb->modifiesTable->existStatement(assignStmtNo) == true);
    string varName = pkb->modifiesTable->getModifiesVar(assignStmtNo);
    Statement assignStmt = pkb->statementTable->getStmtByLineNumber(assignStmtNo);
    assert(assignStmt.type == StatementType::ASSIGN);
    shared_ptr<TNode> tNode = assignStmt.rootNode;

    return AssignNode::createAssignNode(assignStmtNo, varName, tNode);
}

void PKBInterface::addModifies(std::string procedureName, std::string varName) {

}

void PKBInterface::addUses(std::string procedureName, std::string varName) {

}
