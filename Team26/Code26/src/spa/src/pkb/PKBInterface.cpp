#include "PKBInterface.h"
#include <utility>

void PKBInterface::addProcedure(std::string name, int startingStmtNo, int endingStmtNo, std::shared_ptr<CFGHead> cfg) {
    Procedure proc;
    proc.name = std::move(name);
    proc.startingStmtNo = startingStmtNo;
    proc.endingStmtNo = endingStmtNo;
    proc.cfg = std::move(cfg);
    pkb->procedureTable->insertProc(proc);
}

void PKBInterface::addItem(Entity::EntityType type, std::string name, int value) {
    switch (type) {
        case Entity::VARIABLE:
            pkb->varTable->insertVar(name);
        case Entity::CONSTANT:
            pkb->constantTable->insertConst(value);
        default:;
    }
}

void PKBInterface::addStatement(StatementType::StmtType type, int statementNumber, int statementListNumber) {
    Statement stmt;
    stmt.type = type;
    stmt.lineNumber = statementNumber;
    stmt.statementListNumber = statementListNumber;
    pkb->statementTable->insertStmt(stmt);
}

void PKBInterface::addAssignStatement(int statementNumber, int statementListNumber, std::shared_ptr<TNode> rootNode) {
    Statement stmt;
    stmt.type = StatementType::ASSIGN;
    stmt.lineNumber = statementNumber;
    stmt.statementListNumber = statementListNumber;
    stmt.rootNode = std::move(rootNode);
    pkb->statementTable->insertStmt(stmt);
}

void PKBInterface::addCallStatement(int statementNumber, int statementListNumber, std::string calleeProcName) {
    Statement stmt;
    stmt.type = StatementType::CALL;
    stmt.lineNumber = statementNumber;
    stmt.statementListNumber = statementListNumber;
    stmt.calleeProcName = calleeProcName;
    pkb->statementTable->insertStmt(stmt);
}

void PKBInterface::addRelation(RelationType type, int statementNumber, std::string varName) {
    switch (type) {
        case RelationType::MODIFIES_S:
            pkb->modifiesTable->insertModifies(statementNumber, varName);
        case RelationType::USES_S:
            pkb->usesTable->insertUses(statementNumber, varName);
        default:;
    }
}

void PKBInterface::addRelation(RelationType type, std::string procedureName, std::string name) {
    switch (type) {
        case RelationType::MODIFIES_S:
            pkb->modifiesTable->insertProcModifies(procedureName, name);
        case RelationType::USES_S:
            pkb->usesTable->insertProcUses(procedureName, name);
        case RelationType::CALLS:
            pkb->callTable->insertCall(procedureName, name);
        case RelationType::CALLS_T:
            pkb->callStarTable->insertCallStar(procedureName, name);
        default:;
    }
}
void PKBInterface::addRelation(RelationType type, int firstStatementNumber, int secondStatementNumber) {
    switch (type) {
        case RelationType::PARENT:
            pkb->parentTable->insertParent(firstStatementNumber, secondStatementNumber);
        case RelationType::PARENT_T:
            pkb->parentStarTable->insertParentStar(firstStatementNumber, secondStatementNumber);
        case RelationType::FOLLOWS:
            pkb->followsTable->insertFollows(firstStatementNumber, secondStatementNumber);
        default:;
    }
}

std::shared_ptr<AssignNode> PKBInterface::getAssignTNode(const std::string& assignRef) {
    int assignStmtNo = stoi(assignRef);
    assert(pkb->modifiesTable->existStatement(assignStmtNo) == true);
    std::string varName = pkb->modifiesTable->getFirstModifiedVar(assignStmtNo);
    Statement* assignStmt = pkb->statementTable->getStmtByLineNumber(assignStmtNo);
//    assert(assignStmt.type == StatementType::ASSIGN);
    std::shared_ptr<TNode> tNode = assignStmt->rootNode;
    return AssignNode::createAssignNode(assignStmtNo, varName, tNode);
}

std::unordered_set<string> PKBInterface::getConditionVar(const std::string &containerRef) {
    int containerStmtNo = stoi(containerRef);
    return pkb->containerTable->getVarNames(containerStmtNo);
}

void PKBInterface::addCondVar(int statementNumber, std::string varName) {
    this->pkb->containerTable->addCondVar(statementNumber, varName);
}

std::unordered_set<std::string> PKBInterface::getAllUsedOrCalled(RelationType type, std::string procedureName) {
    switch (type) {
        case RelationType::MODIFIES_S:
            return pkb->modifiesTable->getAllModifiedVarByProc(procedureName);
        case RelationType::USES_S:
            return pkb->usesTable->getAllVarUsedByProc(procedureName);
        case RelationType::CALLS:
            return pkb->callTable->getProcsCalled(procedureName);
        case RelationType::CALLS_T:
            return pkb->callStarTable->getProcsStarCalled(procedureName);
        default:
            return {};
    }
}

std::unordered_set<int> PKBInterface::getParentStar(int statementNumber) {
    return pkb->parentStarTable->getAllParentStar(statementNumber);
}

std::unordered_map<std::string, std::unordered_set<std::string>> PKBInterface::getAllProcVarRelation(RelationType type) {
    switch (type) {
        case RelationType::CALLS:
            return pkb->callTable->getAllCalls();
        case RelationType::CALLS_T:
            return pkb->callStarTable->getAllCallStars();
        case RelationType::USES_S:
            return pkb->usesTable->getAllUsesByProc();
        case RelationType::MODIFIES_S:
            return pkb->modifiesTable->getAllModifiesByProc();
        default:
            return {};
    }
}

std::unordered_map<int, std::unordered_set<int>> PKBInterface::getAllStmtRelation(RelationType type) {
    switch (type) {
        case RelationType::AFFECTS:
            return pkb->affectTable->getAllAffect();
        case RelationType::AFFECTS_T:
            return pkb->affectStarTable->getAllAffectStar();
        case RelationType::PARENT:
            return pkb->parentTable->getAllParents();
        case RelationType::PARENT_T:
            return pkb->parentStarTable->getAllParentStars();
        case RelationType::NEXT_T:
            return pkb->nextStarTable->getAllNextStar();
        default:
            return {};
    }
}

std::unordered_map<int, std::unordered_set<std::string>> PKBInterface::getAllStmtVarRelation(RelationType type) {
    switch (type) {
        case RelationType::USES_S:
            return pkb->usesTable->getAllUsesByStmt();
        case RelationType::MODIFIES_S:
            return pkb->modifiesTable->getAllModifiesByStmt();
        default:
            return {};
    }
}

std::unordered_map<int, int> PKBInterface::getAllFollow() {
    return pkb->followsTable->getAllFollows();
}

std::unordered_set<std::unordered_set<Statement*>*> PKBInterface::getAllStmtLists() {
    std::unordered_map<int, std::unordered_set<Statement*>> map;
    for (auto stmt: pkb->statementTable->getStatementList()) {
        int listNumber = stmt->statementListNumber;
        if (map.find(listNumber) != map.end()) {
            map[listNumber].insert(stmt);
        } else {
            std::pair<int, unordered_set<Statement*>> stmtList (listNumber, {stmt});
            map.insert(stmtList);
        }
    }
    std::unordered_set<unordered_set<Statement*>*> result;
    for (auto it = map.begin(); it != map.end(); it++) {
        result.insert(&(it->second));
    }
    return result;
}

std::unordered_set<std::string> PKBInterface::getAllEntity(Argument::ArgumentType type) {
    switch (type) {
        case Argument::STMT_SYNONYM:
            return pkb->statementTable->getAllStmts();
        case Argument::READ_SYNONYM:
            return pkb->statementTable->getAllStmtsByType(StatementType::READ);
        case Argument::PRINT_SYNONYM:
            return pkb->statementTable->getAllStmtsByType(StatementType::PRINT);
        case Argument::CALL_SYNONYM:
            return pkb->statementTable->getAllStmtsByType(StatementType::CALL);
        case Argument::WHILE_SYNONYM:
            return pkb->statementTable->getAllStmtsByType(StatementType::WHILE);
        case Argument::IF_SYNONYM:
            return pkb->statementTable->getAllStmtsByType(StatementType::IF);
        case Argument::ASSIGN_SYNONYM:
            return pkb->statementTable->getAllStmtsByType(StatementType::ASSIGN);
        case Argument::VAR_SYNONYM:
            return pkb->varTable->getAllVariables();
        case Argument::CONST_SYNONYM:
            return pkb->constantTable->getAllConstants();
        case Argument::PROCEDURE_SYNONYM:
            return pkb->procedureTable->getAllProcedures();
        default:
            return {};
    }
}

std::string PKBInterface::getProcLineNumberByName(std::string procName) {
    for (Procedure* p: pkb->procedureTable->getProcList()) {
        if (p->name == procName) {
            return std::to_string(p->startingStmtNo);
        }
    }
    return "";
}

std::string PKBInterface::getCallProcName(std::string callLineNumber) {
    int callLine = std::stoi(callLineNumber);
    Statement* callStmt = pkb->statementTable->getStmtByLineNumber(callLine);
    return callStmt->calleeProcName;
}

std::string PKBInterface::getReadVarName(std::string readLineNumber) {
    int readLine = std::stoi(readLineNumber);
    std::unordered_map<int, std::unordered_set<std::string>> modifiesList = pkb->modifiesTable->getAllModifiesByStmt();
    return *begin(modifiesList[readLine]);
}

std::string PKBInterface::getPrintVarName(std::string printLineNumber) {
    int printLine = std::stoi(printLineNumber);
    std::unordered_map<int, std::unordered_set<std::string>> usesList = pkb->usesTable->getAllUsesByStmt();
    return *begin(usesList[printLine]);
}


CFGHeadPtr PKBInterface::getCfgOfProcedure(std::string procedureName) {
    for (Procedure* currentProcedure : pkb->procedureTable->getProcList()) {
        if (currentProcedure->name == procedureName) {
            return currentProcedure->cfg;
        }
    }
    throw ProcedureNotFoundException();
    return nullptr;
}

bool PKBInterface::hasNextStar(STMT_NUM stmt) {
    return pkb->nextStarTable->existNextStar(stmt);
}

void PKBInterface::addNextStar(STMT_NUM stmt, std::unordered_set<STMT_NUM> nextStarSet) {
    pkb->nextStarTable->insertNextStar(stmt, nextStarSet);
}

bool PKBInterface::isStatementContainer(STMT_NUM stmt) {
    Statement* statement = pkb->statementTable->getStmtByLineNumber(stmt);
    StatementType::StmtType type = statement->type;
    return (type == StatementType::IF) || (type == StatementType::WHILE);
}

bool PKBInterface::doesStatementModify(STMT_NUM stmt, std::string varModified) {
    return pkb->modifiesTable->doesStatementModify(stmt, varModified);
}

bool PKBInterface::hasAffects(STMT_NUM stmt) {
    return pkb->affectTable->existAffect(stmt);
}

std::string PKBInterface::getModifiedVariable(STMT_NUM stmt) {
    return pkb->modifiesTable->getFirstModifiedVar(stmt);
}

bool PKBInterface::isStatementAssign(STMT_NUM stmt) {
    Statement* statement = pkb->statementTable->getStmtByLineNumber(stmt);
    StatementType::StmtType type = statement->type;
    return type == StatementType::ASSIGN;
}

bool PKBInterface::doesStatementUse(STMT_NUM stmt, std::string varUsed) {
    return pkb->usesTable->doesStatementUse(stmt, varUsed);
}

void PKBInterface::addAffects(STMT_NUM stmt, STMT_NUM affectedStmt) {
    pkb->affectTable->insertAffect(stmt, affectedStmt);
}

std::string PKBInterface::getProcedureNameOf(CFGHeadPtr cfg) {
    return pkb->procedureTable->getProcedureNameOf(cfg);
}

bool PKBInterface::hasAffectsStar(STMT_NUM stmt) {
    return pkb->affectStarTable->existAffectStar(stmt);
}

void PKBInterface::addAffectsStar(STMT_NUM stmt, std::unordered_set<STMT_NUM> affectsStarSet) {
    pkb->affectStarTable->insertAffectStar(stmt, affectsStarSet);
}

std::unordered_set<STMT_NUM> PKBInterface::getAllAssignFromProcedure(std::string procName) {
    Procedure* proc = pkb->procedureTable->getProcedureByName(procName);
    int startStmt = proc->startingStmtNo;
    int endStmt = proc->endingStmtNo;
    return pkb->statementTable->getAllAssignFromProcedure(startStmt, endStmt);
}

std::unordered_set<STMT_NUM> PKBInterface::getAffects(STMT_NUM stmt) {
    return pkb->affectTable->getAffectedSet(stmt);
}

std::unordered_set<STMT_NUM> PKBInterface::getAffectsStar(STMT_NUM stmt) {
    return pkb->affectStarTable->getAffectedStarSet(stmt);
}

std::unordered_set<STMT_NUM> PKBInterface::getNextStar(STMT_NUM stmt) {
    return pkb->nextStarTable->getNextStar(stmt);
}

CFGHeadPtr PKBInterface::getCFGHeadPtrByProc(STMT_NUM stmt) {
    Procedure* proc = pkb->procedureTable->getProcByStmt(stmt);
    return (*proc).cfg;
}

Procedure* PKBInterface::getProcByStmt(STMT_NUM stmt) {
    return pkb->procedureTable->getProcByStmt(stmt);
}

std::unordered_set<Procedure*> PKBInterface::getProcList() {
    return pkb->procedureTable->getProcList();
}

void PKBInterface::clear() {
    pkb->nextStarTable->clear();
    pkb->affectTable->clear();
    pkb->affectStarTable->clear();
}




