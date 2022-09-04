#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
//using namespace StatementType;

#include "PKB.h"
#include "TNode.h"
#include "VarTable.h"
#include "ConstantTable.h"
#include "ProcedureTable.h"
#include "StatementTable.h"
#include "PKBParserInterface.h"
#include "PKBQueryInterface.h"

ProcedureTable* PKB::procedureTable = new ProcedureTable();
VarTable* PKB::varTable = new VarTable();
ConstantTable* PKB::constantTable = new ConstantTable();
StatementTable* PKB::statementTable = new StatementTable();

int PKB::setProcToAST(PROC p, TNode* r) {
	return 0;
}

TNode* PKB::getRootAST (PROC p){
	return nullptr;
}

void PKBParserInterface::addProcedure(std::string name, int startingStmtNo, int endingStmtNo) {
    Procedure proc;
    proc.name = name;
    proc.startingStmtNo = startingStmtNo;
    proc.endingStmtNo = endingStmtNo;
    PKB::procedureTable->insertProc(proc);
}

void PKBParserInterface::addVariable(string name) {
    Variable var;
    var.name = name;
    PKB::varTable->insertVar(var);
}

void PKBParserInterface::addConst(int value){
    PKB::constantTable->insertConst(value);
}

void PKBParserInterface::addReadStatement(int statementNumber) {
    Statement stmt;
    stmt.type = StmtType->READ;
    stmt.lineNumber = statementNumber;
    PKB::statementTable->insertStmt(stmt);
}

void PKBParserInterface::addAssignStatement(int statementNumber) {
    Statement stmt;
    stmt.type = StmtType->ASSIGN;
    stmt.lineNumber = statementNumber;
    PKB::statementTable->insertStmt(stmt);
}

void PKBParserInterface::addWhileStatement(int statementNumber) {
    Statement stmt;
    stmt.type = StmtType->WHILE;
    stmt.lineNumber = statementNumber;
    PKB::statementTable->insertStmt(stmt);
}

void PKBParserInterface::addIfStatement(int statementNumber) {
    Statement stmt;
    stmt.type = StmtType->IF;
    stmt.lineNumber = statementNumber;
    PKB::statementTable->insertStmt(stmt);
}

void PKBParserInterface::addPrintStatement(int statementNumber) {
    Statement stmt;
    stmt.type = StmtType->PRINT;
    stmt.lineNumber = statementNumber;
    PKB::statementTable->insertStmt(stmt);
}

vector<string> getAllEntity(EntityType) {
    vector<string> result;
    switch(EntityType) {
        case STATEMENT:
            result = PKB::statementTable->getAllStmts();
            break;
        case READ:
            result = PKB::statementTable->getAllReads();
            break;
        case PRINT:
            result = PKB::statementTable->getAllPrints();
            break;
        case CALL:
            result = PKB::statementTable->getAllCalls();
            break;
        case WHILE:
            result = PKB::statementTable->getAllWhiles();
            break;
        case IF:
            result = PKB::statementTable->getAllIfs();
            break;
        case ASSIGN:
            result = PKB::statementTable->getAllAssigns();
            break;
        case VARIABLE:
            result = PKB::varTable->getAllVariables();
            break;
        case CONSTANT:
            result = PKB::constantTable->getAllConstants();
            break;
        case PROCEDURE:
            result = PKB::procedureTable->getAllProcedures();
            break;
//        case INVALID_ENTITY_TYPE:
//            break;
        default:
            break;
    }
    return result;
}
