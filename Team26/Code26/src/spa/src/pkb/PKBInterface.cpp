#include "PKBInterface.h"

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

void PKBInterface::addVariable(std::string name) {
    pkb->varTable->insertVar(name);
}

void PKBInterface::addConst(int value) {
    pkb->constantTable->insertConst(value);
}

void PKBInterface::addStatement(StatementType::StmtType type, int statementNumber, int statementListNumber,
                                std::shared_ptr<TNode> rootNode, std::string calleeProcName) {
    Statement stmt;
    stmt.type = type;
    stmt.lineNumber = statementNumber;
    stmt.statementListNumber = statementListNumber;
    stmt.rootNode = std::move(rootNode);
    stmt.calleeProcName = calleeProcName;
    pkb->statementTable->insertStmt(stmt);
}

void PKBInterface::addReadStatement(int statementNumber, int statementListNumber) {
    return addStatement(StatementType::READ, statementNumber, statementListNumber, nullptr, "");
}

void PKBInterface::addAssignStatement(int statementNumber, int statementListNumber, std::shared_ptr<TNode> rootNode) {
    return addStatement(StatementType::ASSIGN, statementNumber, statementListNumber, rootNode, "");
}

void PKBInterface::addWhileStatement(int statementNumber, int statementListNumber) {
    return addStatement(StatementType::WHILE, statementNumber, statementListNumber, nullptr, "");
}

void PKBInterface::addIfStatement(int statementNumber, int statementListNumber) {
    return addStatement(StatementType::IF, statementNumber, statementListNumber, nullptr, "");
}

void PKBInterface::addPrintStatement(int statementNumber, int statementListNumber) {
    return addStatement(StatementType::PRINT, statementNumber, statementListNumber, nullptr, "");
}

void PKBInterface::addCallStatement(int statementNumber, int statementListNumber, std::string calleeProcName) {
    return addStatement(StatementType::CALL, statementNumber, statementListNumber, nullptr, calleeProcName);
}

void PKBInterface::addModifies(int statementNumber, std::string varName) {
    pkb->modifiesTable->insertModifies(statementNumber, std::move(varName));
}

void PKBInterface::addModifies(std::string procedureName, std::string varName) {
    pkb->modifiesTable->insertProcModifies(procedureName, varName);
}

void PKBInterface::addUses(int statementNumber, std::string varName) {
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

std::shared_ptr<AssignNode> PKBInterface::getAssignTNode(const std::string& assignRef) {
    int assignStmtNo = stoi(assignRef);
    assert(pkb->modifiesTable->existStatement(assignStmtNo) == true);
    std::string varName = (pkb->modifiesTable->getModifiesVar(assignStmtNo)).at(0);
    Statement assignStmt = pkb->statementTable->getStmtByLineNumber(assignStmtNo);
//    assert(assignStmt.type == StatementType::ASSIGN);
    std::shared_ptr<TNode> tNode = assignStmt.rootNode;

    return AssignNode::createAssignNode(assignStmtNo, varName, tNode);
}

std::vector<std::string> PKBInterface::getConditionVar(const std::string &containerRef) {
    int containerStmtNo = stoi(containerRef);
    return pkb->containerTable->getVarNames(containerStmtNo);
}

void PKBInterface::addCondVar(int statementNumber, std::string varName) {
    this->pkb->containerTable->addCondVar(statementNumber, varName);
}

std::unordered_set<std::string> PKBInterface::getAllVariablesModified(std::string procedureName) {
    std::vector<std::string> varsModified = pkb->modifiesTable->getAllModifiedVarByProc(procedureName);
    std::unordered_set<std::string> result;
    for (std::string var : varsModified) {
        result.insert(var);
    }
    return result;
}

std::unordered_set<std::string> PKBInterface::getAllVariablesUsed(std::string procedureName) {
    std::vector<std::string> varsUsed = pkb->usesTable->getAllVarUsedByProc(procedureName);
    std::unordered_set<std::string> result;
    for (std::string var : varsUsed) {
        result.insert(var);
    }
    return result;
}

std::unordered_set<int> PKBInterface::getParentStar(int statementNumber) {
    return pkb->parentStarTable->getAllParentStar(statementNumber);
}

std::unordered_set<std::string> PKBInterface::getCall(std::string procedure) {
    std::vector<std::string> procsCalled = pkb->callTable->getProcsCalled(procedure);
    std::unordered_set<std::string> result;
    for (std::string proc : procsCalled) {
        result.insert(proc);
    }
    return result;
}

std::unordered_set<std::string> PKBInterface::getCallStar(std::string procedure) {
    std::vector<std::string> procsStarCalled = pkb->callStarTable->getProcsStarCalled(procedure);
    std::unordered_set<std::string> result;
    for (std::string proc : procsStarCalled) {
        result.insert(proc);
    }
    return result;
}

std::unordered_map<std::string, std::vector<std::string>> PKBInterface::getAllCall() {
    return pkb->callTable->getAllCalls();
}

std::unordered_map<std::string, std::vector<std::string>> PKBInterface::getAllCallStar() {
    return pkb->callStarTable->getAllCallStars();
}

std::unordered_map<int, int> PKBInterface::getAllFollow() {
    return pkb->followsTable->getAllFollows();
}

std::unordered_map<int, int> PKBInterface::getAllFollowStar() {
    return pkb->followsStarTable->getAllFollowStars();
}

std::unordered_map<int, std::vector<int>> PKBInterface::getAllNext() {
    return pkb->nextTable->getAllNext();
}

std::unordered_map<STMT_NUM, std::unordered_set<STMT_NUM>> PKBInterface::getAllNextStar() {
    return pkb->nextStarTable->getAllNextStar();
}

std::unordered_map<int, std::unordered_set<int>> PKBInterface::getAllAffects() {
    return pkb->affectTable->getAllAffect();
}

std::unordered_map<int, std::unordered_set<int>> PKBInterface::getAllAffectsStar() {
    return pkb->affectStarTable->getAllAffectStar();
}

std::unordered_map<int, std::vector<std::string>> PKBInterface::getAllModifyByStmt() {
    return pkb->modifiesTable->getAllModifiesByStmt();
}

std::unordered_map<std::string, std::vector<std::string>> PKBInterface::getAllModifyByProc() {
    return pkb->modifiesTable->getAllModifiesByProc();
}

std::unordered_map<int, std::vector<int>> PKBInterface::getAllParent() {
    return pkb->parentTable->getAllParents();
}

std::unordered_map<int, std::vector<int>> PKBInterface::getAllParentStar() {
    return pkb->parentStarTable->getAllParentStars();
}

std::unordered_map<int, std::vector<std::string>> PKBInterface::getAllUseByStmt() {
    return pkb->usesTable->getAllUsesByStmt();
}

std::unordered_map<std::string, std::vector<std::string>> PKBInterface::getAllUseByProc() {
    return pkb->usesTable->getAllUsesByProc();
}

std::vector<std::vector<Statement>> PKBInterface::getAllStmtLists() {
    std::unordered_map<int, std::vector<Statement>> map;
    for (Statement stmt : pkb->statementTable->getStatementList()) {
        int listNumber = stmt.statementListNumber;
        if (map.find(listNumber) != map.end()) {
            map[listNumber].push_back(stmt);
        } else {
            std::pair<int, std::vector<Statement>> stmtList(listNumber, {stmt});
            map.insert(stmtList);
        }
    }
    std::vector<std::vector<Statement>> result;
    for (auto it = map.begin(); it != map.end(); it++) {
        result.push_back(it->second);
    }
    return result;
}


std::vector<std::string> PKBInterface::getAllEntity(Argument::ArgumentType type) {
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

std::vector<std::string> PKBInterface::getAllAssigns() {
    return pkb->statementTable->getAllStmtsByType(StatementType::ASSIGN);
}

std::vector<std::string> PKBInterface::getAllVariables() {
    return pkb->varTable->getAllVariables();
}

std::vector<std::string> PKBInterface::getAllConstants() {
    return pkb->constantTable->getAllConstants();
}

std::vector<std::string> PKBInterface::getAllProcedures() {
    return pkb->procedureTable->getAllProcedures();
}

std::string PKBInterface::getProcLineNumberByName(std::string procName) {
    for (Procedure p : pkb->procedureTable->getProcList()) {
        if (p.name == procName) {
            return std::to_string(p.startingStmtNo);
        }
    }
    return "";
}

std::string PKBInterface::getCallProcName(std::string callLineNumber) {
    int callLine = std::stoi(callLineNumber);
    Statement callStmt = pkb->statementTable->getStmtByLineNumber(callLine);
    return callStmt.calleeProcName;
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


CFGHeadPtr PKBInterface::getCfgOfProcedure(std::string procedureName) {
    for (Procedure currentProcedure : pkb->procedureTable->getProcList()) {
        if (currentProcedure.name == procedureName) {
            return currentProcedure.cfg;
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
    Statement statement = pkb->statementTable->getStmtByLineNumber(stmt);
    StatementType::StmtType type = statement.type;
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
    Statement statement = pkb->statementTable->getStmtByLineNumber(stmt);
    StatementType::StmtType type = statement.type;
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
    Procedure proc = pkb->procedureTable->getProcedureByName(procName);
    int startStmt = proc.startingStmtNo;
    int endStmt = proc.endingStmtNo;
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

std::vector<Procedure> PKBInterface::getProcList() {
    return pkb->procedureTable->getProcList();
}

void PKBInterface::clear() {
    pkb->nextStarTable->clear();
    pkb->affectTable->clear();
    pkb->affectStarTable->clear();
}




