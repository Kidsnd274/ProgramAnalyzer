//
// Created by QMS on 4/9/2022.
//

#include<stdio.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <cassert>
#include <memory>

#include "PKB.h"
#include "util/ast/TNode.h"
#include "util/cfg/CFGHead.h"
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
#include "CallTable.h"
#include "CallStarTable.h"

using namespace std;
//using namespace StatementType;

void PKBInterface::addProcedure(std::string name, int startingStmtNo, int endingStmtNo, std::shared_ptr<CFGHead> cfg) {
    Procedure proc;
    proc.name = std::move(name);
    proc.startingStmtNo = startingStmtNo;
    proc.endingStmtNo = endingStmtNo;
    proc.cfg = std::move(cfg);
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
    stmt.rootNode = std::move(rootNode);
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

void PKBInterface::addCallStatement(int statementNumber, int statementListNumber) {
    Statement stmt;
    stmt.type = StatementType::CALL;
    stmt.lineNumber = statementNumber;
    stmt.statementListNumber = statementListNumber;
    pkb->statementTable->insertStmt(stmt);
}

void PKBInterface::addModifies(int statementNumber, string varName) {
    pkb->modifiesTable->insertModifies(statementNumber, std::move(varName));
}

void PKBInterface::addModifies(std::string procedureName, std::string varName) {
    pkb->modifiesTable->insertProcModifies(procedureName, varName);
}

void PKBInterface::addUses(int statementNumber, string varName) {
    pkb->usesTable->insertUses(statementNumber, std::move(varName));
}

void PKBInterface::addUses(std::string procedureName, std::string varName) {
    pkb->usesTable->insertProcUses(procedureName, varName);
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

void PKBInterface::addCall(std::string procedureName, std::string procedureCalled) {
    pkb->callTable->insertCall(procedureName, procedureCalled);
}

void PKBInterface::addCallStar(std::string procedureName, std::string procedureCalled) {
    pkb->callStarTable->insertCallStar(procedureName, procedureCalled);
}


shared_ptr<AssignNode> PKBInterface::getAssignTNode(const string& assignRef) {
    int assignStmtNo = stoi(assignRef);
    assert(pkb->modifiesTable->existStatement(assignStmtNo) == true);
    string varName = (pkb->modifiesTable->getModifiesVar(assignStmtNo)).at(0);
    Statement assignStmt = pkb->statementTable->getStmtByLineNumber(assignStmtNo);
//    assert(assignStmt.type == StatementType::ASSIGN);
    shared_ptr<TNode> tNode = assignStmt.rootNode;

    return AssignNode::createAssignNode(assignStmtNo, varName, tNode);
}

std::unordered_set<std::string> PKBInterface::getAllVariablesModified(std::string procedureName) {
    std::vector<std::string> varsModified = pkb->modifiesTable->getAllModifiedVarByProc(procedureName);
    std::unordered_set<string> result;
    for (std::string var: varsModified) {
        result.insert(var);
    }
    return result;
}

std::unordered_set<std::string> PKBInterface::getAllVariablesUsed(std::string procedureName) {
    std::vector<std::string> varsUsed = pkb->usesTable->getAllVarUsedByProc(procedureName);
    std::unordered_set<string> result;
    for (std::string var: varsUsed) {
        result.insert(var);
    }
    return result;
}

std::unordered_set<int> PKBInterface::getParentStar(int statementNumber) {
    return pkb->parentStarTable->getAllParentStar(statementNumber);
}

std::unordered_set<string> PKBInterface::getCall(std::string procedure) {
    std::vector<std::string> procsCalled = pkb->callTable->getProcsCalled(procedure);
    std::unordered_set<string> result;
    for (std::string proc: procsCalled) {
        result.insert(proc);
    }
    return result;
}

std::unordered_set<string> PKBInterface::getCallStar(std::string procedure) {
    std::vector<std::string> procsStarCalled = pkb->callStarTable->getProcsStarCalled(procedure);
    std::unordered_set<string> result;
    for (std::string proc: procsStarCalled) {
        result.insert(proc);
    }
    return result;
}

unordered_map<std::string, std::vector<std::string>> PKBInterface::getAllCall() {
    return pkb->callTable->getAllCalls();
}

unordered_map<std::string, std::vector<std::string>> PKBInterface::getAllCallStar() {
    return pkb->callStarTable->getAllCallStars();
}

unordered_map<int,int> PKBInterface::getAllFollow() {
    return pkb->followsTable->getAllFollows();
}

unordered_map<int,int> PKBInterface::getAllFollowStar() {
    return pkb->followsStarTable->getAllFollowStars();
}

unordered_map<int, std::vector<std::string>> PKBInterface::getAllModifyByStmt() {
    return pkb->modifiesTable->getAllModifiesByStmt();
}

unordered_map<std::string, std::vector<std::string>> PKBInterface::getAllModifyByProc() {
    return pkb->modifiesTable->getAllModifiesByProc();
}

unordered_map<int, std::vector<int>> PKBInterface::getAllParent() {
    return pkb->parentTable->getAllParents();
}

unordered_map<int, std::vector<int>> PKBInterface::getAllParentStar() {
    return pkb->parentStarTable->getAllParentStars();
}

unordered_map<int, std::vector<std::string>> PKBInterface::getAllUseByStmt() {
    return pkb->usesTable->getAllUsesByStmt();
}

unordered_map<std::string, std::vector<std::string>> PKBInterface::getAllUseByProc() {
    return pkb->usesTable->getAllUsesByProc();
}

std::vector<vector<Statement>> PKBInterface::getAllStmtLists() {
    std::unordered_map<int, vector<Statement>> map;
    for (Statement stmt: pkb->statementTable->getStatementList()) {
        int listNumber = stmt.statementListNumber;
        if (map.find(listNumber) != map.end()) {
            map[listNumber].push_back(stmt);
        } else {
            std::pair<int, vector<Statement>> stmtList (listNumber, {stmt});
            map.insert(stmtList);
        }
    }
    std::vector<vector<Statement>> result;
    for (auto it = map.begin(); it != map.end(); it++) {
        result.push_back(it->second);
    }
    return result;
}

vector<string> PKBInterface::getAllStmts() {
    return pkb->statementTable->getAllStmts();
}

vector<string> PKBInterface::getAllReads() {
    return pkb->statementTable->getAllReads();
}

vector<string> PKBInterface::getAllPrints() {
    return pkb->statementTable->getAllPrints();
}

vector<string> PKBInterface::getAllCalls() {
    return pkb->statementTable->getAllCalls();
}

vector<string> PKBInterface::getAllWhiles() {
    return pkb->statementTable->getAllWhiles();
}

vector<string> PKBInterface::getAllIfs() {
    return pkb->statementTable->getAllIfs();
}

vector<string> PKBInterface::getAllAssigns() {
    return pkb->statementTable->getAllAssigns();
}

vector<string> PKBInterface::getAllVariables() {
    return pkb->varTable->getAllVariables();
}

vector<string> PKBInterface::getAllConstants() {
    return pkb->constantTable->getAllConstants();
}

vector<string> PKBInterface::getAllProcedures() {
    return pkb->procedureTable->getAllProcedures();
}
