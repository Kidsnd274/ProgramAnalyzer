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

bool PKBInterface::existRelation(const RelationStruct& relation) {
    RelationType typeOfRelation = relation.typeOfRelation;
    ArgumentStruct arg1 = relation.arg1;
    ArgumentStruct arg2 = relation.arg2;
    bool isArg1Wildcard = arg1.typeOfArgument == QPS::WILDCARD;
    bool isArg2Wildcard = arg2.typeOfArgument == QPS::WILDCARD;
    bool result = false;
    switch (typeOfRelation) {
        case QPS::FOLLOWS:
//            assert(arg1.typeOfArgument == QPS::STMT_SYNONYM);
//            assert(arg2.typeOfArgument == QPS::STMT_SYNONYM);
            if (arg1.typeOfArgument == WILDCARD && arg2.typeOfArgument == WILDCARD) {
                result = true;
                break;
            }
            if (arg1.typeOfArgument == WILDCARD) {
                Statement stmt2 = pkb->statementTable->getStmtByLineNumber(stoi(arg2.nameOfArgument));
                result = false;
                for (Statement statement : pkb->statementTable->getStatementList()) {
                    if (statement.statementListNumber == stmt2.statementListNumber &&
                        pkb->followsTable->existFollows(statement.lineNumber, stmt2.lineNumber)) {
                        result = true;
                        break;
                    }
                }
                break;
            }
            if (arg2.typeOfArgument == WILDCARD) {
                Statement stmt1 = pkb->statementTable->getStmtByLineNumber(stoi(arg1.nameOfArgument));
                result = false;
                for (Statement statement : pkb->statementTable->getStatementList()) {
                    if (statement.statementListNumber == stmt1.statementListNumber &&
                        pkb->followsTable->existFollows(stmt1.lineNumber, statement.lineNumber)) {
                        result = true;
                        break;
                    }
                }
                break;
            }
            result = pkb->followsTable->existFollows(stoi(arg1.nameOfArgument), stoi(arg2.nameOfArgument));
            break;
        case QPS::FOLLOWS_T: {
//            assert(arg1.typeOfArgument == QPS::STMT_SYNONYM);
//            assert(arg2.typeOfArgument == QPS::STMT_SYNONYM);
//            result = pkb->followsStarTable->existFollowsStar(stoi(arg1.nameOfArgument), stoi(arg2.nameOfArgument));
            if (arg1.typeOfArgument == WILDCARD && arg2.typeOfArgument == WILDCARD) {
                result = true;
                break;
            }
            if (arg1.typeOfArgument == WILDCARD) {
                Statement stmt2 = pkb->statementTable->getStmtByLineNumber(stoi(arg2.nameOfArgument));
                result = false;
                for (Statement statement : pkb->statementTable->getStatementList()) {
                    if (statement.statementListNumber == stmt2.statementListNumber && statement.lineNumber < stmt2.lineNumber) {
                        result = true;
                        break;
                    }
                }
                break;
            }
            if (arg2.typeOfArgument == WILDCARD) {
                Statement stmt1 = pkb->statementTable->getStmtByLineNumber(stoi(arg1.nameOfArgument));
                result = false;
                for (Statement statement : pkb->statementTable->getStatementList()) {
                    if (statement.statementListNumber == stmt1.statementListNumber && stmt1.lineNumber < statement.lineNumber) {
                        result = true;
                        break;
                    }
                }
                break;
            }
            Statement stmt1 = pkb->statementTable->getStmtByLineNumber(stoi(arg1.nameOfArgument));
            Statement stmt2 = pkb->statementTable->getStmtByLineNumber(stoi(arg2.nameOfArgument));
            if (stmt1.statementListNumber == stmt2.statementListNumber && stmt1.lineNumber < stmt2.lineNumber) {
                result = true;
            } else {
                result = false;
            }
            break;
        }
        case QPS::PARENT:
//            assert(arg1.typeOfArgument == QPS::STMT_SYNONYM);
//            assert(arg2.typeOfArgument == QPS::STMT_SYNONYM);
            if (isArg1Wildcard && isArg2Wildcard) {
                result = pkb->parentTable->existParent(0, 0);
                break;
            }
            if (isArg1Wildcard) {
                result = pkb->parentTable->existParent(0, stoi(arg2.nameOfArgument));
                break;
            }
            if (isArg2Wildcard) {
                result = pkb->parentTable->existParent(stoi(arg1.nameOfArgument), 0);
                break;
            }
            result = pkb->parentTable->existParent(stoi(arg1.nameOfArgument), stoi(arg2.nameOfArgument));
            break;
        case QPS::PARENT_T:
//            assert(arg1.typeOfArgument == QPS::STMT_SYNONYM);
//            assert(arg2.typeOfArgument == QPS::STMT_SYNONYM);
//            result = pkb->parentStarTable->existParentStar(stoi(arg1.nameOfArgument), stoi(arg2.nameOfArgument));
            if (isArg1Wildcard && isArg2Wildcard) {
                result = pkb->parentStarTable->existParentStar(0, 0);
                break;
            }
            if (isArg1Wildcard) {
                result = pkb->parentStarTable->existParentStar(0, stoi(arg2.nameOfArgument));
                break;
            }
            if (isArg2Wildcard) {
                result = pkb->parentStarTable->existParentStar(stoi(arg1.nameOfArgument), 0);
                break;
            }
            result = pkb->parentStarTable->existParentStar(stoi(arg1.nameOfArgument), stoi(arg2.nameOfArgument));
            break;
        case QPS::MODIFIES_S:
//            assert(arg1.typeOfArgument == QPS::STMT_SYNONYM);
//            assert(arg2.typeOfArgument == QPS::VAR_SYNONYM);
            if (isArg1Wildcard) {
                if (isArg2Wildcard) {
                    result = pkb->modifiesTable->existModifies(0, std::string());
                } else {
                    result = pkb->modifiesTable->existModifies(0, arg2.nameOfArgument);
                }
            } else {
                if (isArg2Wildcard) {
                    result = pkb->modifiesTable->existModifies(stoi(arg1.nameOfArgument), std::string());
                } else {
                    result = pkb->modifiesTable->existModifies(stoi(arg1.nameOfArgument), arg2.nameOfArgument);
                }
            }
            break;
        case QPS::USES_S:
//            assert(arg1.typeOfArgument == QPS::STMT_SYNONYM);
//            assert(arg2.typeOfArgument == QPS::VAR_SYNONYM);
            if (isArg1Wildcard) {
                if (isArg2Wildcard) {
                    result = pkb->usesTable->existUses(0, std::string());
                } else {
                    result = pkb->usesTable->existUses(0, arg2.nameOfArgument);
                }
            } else {
                if (isArg2Wildcard) {
                    result = pkb->usesTable->existUses(stoi(arg1.nameOfArgument), std::string());
                } else {
                    result = pkb->usesTable->existUses(stoi(arg1.nameOfArgument), arg2.nameOfArgument);
                }
            }
            break;
        case QPS::CALLS:
            result = pkb->callTable->existCall(arg1.nameOfArgument, arg2.nameOfArgument);
            break;
        case QPS::CALLS_P:
            result = pkb->callStarTable->existCallStar(arg1.nameOfArgument, arg2.nameOfArgument);
            break;
        default:
            result = false;
            break;
        case USES_P:
        case MODIFIES_P:
        case INVALID_RELATION_TYPE:
            break;
    }
    return result;
}

shared_ptr<AssignNode> PKBInterface::getAssignTNode(const string& assignRef) {
    int assignStmtNo = stoi(assignRef);
    assert(pkb->modifiesTable->existStatement(assignStmtNo) == true);
    string varName = (pkb->modifiesTable->getModifiesVar(assignStmtNo)).at(0);
    Statement assignStmt = pkb->statementTable->getStmtByLineNumber(assignStmtNo);
    assert(assignStmt.type == StatementType::ASSIGN);
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
    return pkb->callTable->getAllCalls();
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

std::string PKBInterface::getProcLineNumberByName(std::string procName) {
    for (Procedure p: pkb->procedureTable->getProcList()) {
        if (p.name == procName) {
            return std::to_string(p.startingStmtNo);
        }
    }
    return "";
}

std::string PKBInterface::getCallProcName(std::string callLineNumber) {

}

std::string PKBInterface::getReadVarName(std::string readLineNumber) {
    int readLine = std::stoi(readLineNumber);
    std::unordered_map<int, std::vector<std::string>> modifiesList = pkb->modifiesTable->getAllModifiesByStmt();
    return modifiesList[readLine].front();
}

std::string PKBInterface::getPrintVarName(std::string printLineNumber) {
    int printLine = std::stoi(printLineNumber);
    std::unordered_map<int, std::vector<std::string>> usesList = pkb->usesTable->getAllUsesByStmt();
    return usesList[printLine].front();
}
