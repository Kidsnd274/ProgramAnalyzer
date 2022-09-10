//
// Created by QMS on 4/9/2022.
//

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "PKB.h"
#include "util/ast/TNode.h"
#include "VarTable.h"
#include "ConstantTable.h"
#include "ProcedureTable.h"
#include "StatementTable.h"
#include "PKBInterface.h"

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
    Variable var;
    var.name = name;
    pkb->varTable->insertVar(var);
}

void PKBInterface::addConst(int value){
    pkb->constantTable->insertConst(value);
}

void PKBInterface::addReadStatement(int statementNumber) {
    Statement stmt;
    stmt.type = StatementType::READ;
    stmt.lineNumber = statementNumber;
    pkb->statementTable->insertStmt(stmt);
}

void PKBInterface::addAssignStatement(int statementNumber) {
    Statement stmt;
    stmt.type = StatementType::ASSIGN;
    stmt.lineNumber = statementNumber;
    pkb->statementTable->insertStmt(stmt);
}

void PKBInterface::addWhileStatement(int statementNumber) {
    Statement stmt;
    stmt.type = StatementType::WHILE;
    stmt.lineNumber = statementNumber;
    pkb->statementTable->insertStmt(stmt);
}

void PKBInterface::addIfStatement(int statementNumber) {
    Statement stmt;
    stmt.type = StatementType::IF;
    stmt.lineNumber = statementNumber;
    pkb->statementTable->insertStmt(stmt);
}

void PKBInterface::addPrintStatement(int statementNumber) {
    Statement stmt;
    stmt.type = StatementType::PRINT;
    stmt.lineNumber = statementNumber;
    pkb->statementTable->insertStmt(stmt);
}

vector<string> PKBInterface::getAllEntity(EntityType type) {
    vector<string> result;
    switch(type) {
        case STATEMENT:
            result = pkb->statementTable->getAllStmts();
            break;
        case READ:
            result = pkb->statementTable->getAllReads();
            break;
        case PRINT:
            result = pkb->statementTable->getAllPrints();
            break;
        case CALL:
            result = pkb->statementTable->getAllCalls();
            break;
        case WHILE:
            result = pkb->statementTable->getAllWhiles();
            break;
        case IF:
            result = pkb->statementTable->getAllIfs();
            break;
        case ASSIGN:
            result = pkb->statementTable->getAllAssigns();
            break;
        case VARIABLE:
            result = pkb->varTable->getAllVariables();
            break;
        case CONSTANT:
            result = pkb->constantTable->getAllConstants();
            break;
        case PROCEDURE:
            result = pkb->procedureTable->getAllProcedures();
            break;
//        case INVALID_ENTITY_TYPE:
//            break;
        default:
            break;
    }
    return result;
}

void PKBInterface::addFollows(int stmt1Number, int stmt2Number) {

}

void PKBInterface::addModifies(int stmtNumber, std::string varModified) {

}

void PKBInterface::addModifies(std::string procedureName, std::string varModified) {

}

void PKBInterface::addParent(int parentStmtNumber, int stmtNumber) {

}

void PKBInterface::addParentStar(int parentStmtNumber, int stmtNumber) {

}

void PKBInterface::addUses(int stmtNumber, std::string variableUsed) {

}

void PKBInterface::addUses(std::string procedureName, std::string variableUsed) {

}


