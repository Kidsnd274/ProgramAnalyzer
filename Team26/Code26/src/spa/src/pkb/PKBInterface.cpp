#include "PKBInterface.h"

void PKBInterface::addProcedure(std::string name, int startingStmtNo, int endingStmtNo, std::shared_ptr<CFGHead> cfg) {
    Procedure proc;
    proc.name = std::move(name);
    proc.startingStmtNo = startingStmtNo;
    proc.endingStmtNo = endingStmtNo;
    proc.cfg = std::move(cfg);
    pkb->procedureTable->insertProc(proc);
}

// S1 (Major): DRY - Code structure of method is similar to addConst
void PKBInterface::addVariable(std::string name) {
    pkb->varTable->insertVar(name);
}

// S1 (Major): DRY - Code structure of method is similar to addVariable
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

// S1 (Major): DRY - Code structure of method is similar to other addStatement methods
void PKBInterface::addReadStatement(int statementNumber, int statementListNumber) {
    return addStatement(StatementType::READ, statementNumber, statementListNumber, nullptr, "");
}

void PKBInterface::addAssignStatement(int statementNumber, int statementListNumber, std::shared_ptr<TNode> rootNode) {
    return addStatement(StatementType::ASSIGN, statementNumber, statementListNumber, rootNode, "");
}

// S1 (Major): DRY - Code structure of method is similar to other addStatement methods
void PKBInterface::addWhileStatement(int statementNumber, int statementListNumber) {
    return addStatement(StatementType::WHILE, statementNumber, statementListNumber, nullptr, "");
}

// S1 (Major): DRY - Code structure of method is similar to other addStatement methods
void PKBInterface::addIfStatement(int statementNumber, int statementListNumber) {
    return addStatement(StatementType::IF, statementNumber, statementListNumber, nullptr, "");
}

// S1 (Major): DRY - Code structure of method is similar to other addStatement methods
void PKBInterface::addPrintStatement(int statementNumber, int statementListNumber) {
    return addStatement(StatementType::PRINT, statementNumber, statementListNumber, nullptr, "");
}

// S1 (Major): DRY - Code structure of method is similar to other addStatement methods
void PKBInterface::addCallStatement(int statementNumber, int statementListNumber, std::string calleeProcName) {
    return addStatement(StatementType::CALL, statementNumber, statementListNumber, nullptr, calleeProcName);
}

// S1 (Major): DRY - Code structure of method is similar to addUses(stmt, var)
void PKBInterface::addModifies(int statementNumber, std::string varName) {
    pkb->modifiesTable->insertModifies(statementNumber, std::move(varName));
}

// S1 (Major): DRY - Code structure of method is similar to addUses(proc, var)
void PKBInterface::addModifies(std::string procedureName, std::string varName) {
    pkb->modifiesTable->insertProcModifies(procedureName, varName);
}
// S1 (Major): DRY - Code structure of method is similar to addModifies(stmt, var)
void PKBInterface::addUses(int statementNumber, std::string varName) {
    pkb->usesTable->insertUses(statementNumber, std::move(varName));
}

// S1 (Major): DRY - Code structure of method is similar to addModifies(proc, var)
void PKBInterface::addUses(std::string procedureName, std::string varName) {
    pkb->usesTable->insertProcUses(procedureName, varName);
}

// S1 (Major): DRY - Code structure of method is similar to other addRelationship methods
void PKBInterface::addParent(int parentStatementNumber, int childStatementNumber) {
    pkb->parentTable->insertParent(parentStatementNumber, childStatementNumber);
}

// S1 (Major): DRY - Code structure of method is similar to other addRelationship methods
void PKBInterface::addParentStar(int parentStatementNumber, int childStatementNumber) {
    pkb->parentStarTable->insertParentStar(parentStatementNumber, childStatementNumber);
}

// S1 (Major): DRY - Code structure of method is similar to other addRelationship methods
void PKBInterface::addFollows(int frontStatementNumber, int backStatementNumber) {
    pkb->followsTable->insertFollows(frontStatementNumber, backStatementNumber);
}

// S1 (Major): DRY - Code structure of method is similar to other addRelationship methods
void PKBInterface::addFollowsStar(int frontStatementNumber, int backStatementNumber) {
    pkb->followsStarTable->insertFollowsStar(frontStatementNumber, backStatementNumber);
}

// S1 (Major): DRY - Code structure of method is similar to addCallStar
void PKBInterface::addCall(std::string procedureName, std::string procedureCalled) {
    pkb->callTable->insertCall(procedureName, procedureCalled);
}

// S1 (Major): DRY - Code structure of method is similar to addCall
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


// S1 (Major): DRY - Code structure of method is similar to getAllVariableUsed
std::unordered_set<std::string> PKBInterface::getAllVariablesModified(std::string procedureName) {
    std::vector<std::string> varsModified = pkb->modifiesTable->getAllModifiedVarByProc(procedureName);
    std::unordered_set<std::string> result;
    for (std::string var : varsModified) {
        result.insert(var);
    }
    return result;
}

// S1 (Major): DRY - Code structure of method is similar to getAllVariableModified
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


// S1 (Major): DRY - Code structure of method is similar to getCallStar
std::unordered_set<std::string> PKBInterface::getCall(std::string procedure) {
    std::vector<std::string> procsCalled = pkb->callTable->getProcsCalled(procedure);
    std::unordered_set<std::string> result;
    for (std::string proc : procsCalled) {
        result.insert(proc);
    }
    return result;
}

// S1 (Major): DRY - Code structure of method is similar to getCall
std::unordered_set<std::string> PKBInterface::getCallStar(std::string procedure) {
    std::vector<std::string> procsStarCalled = pkb->callStarTable->getProcsStarCalled(procedure);
    std::unordered_set<std::string> result;
    for (std::string proc : procsStarCalled) {
        result.insert(proc);
    }
    return result;
}


// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::unordered_map<std::string, std::vector<std::string>> PKBInterface::getAllCall() {
    return pkb->callTable->getAllCalls();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::unordered_map<std::string, std::vector<std::string>> PKBInterface::getAllCallStar() {
    return pkb->callStarTable->getAllCallStars();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::unordered_map<int, int> PKBInterface::getAllFollow() {
    return pkb->followsTable->getAllFollows();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::unordered_map<int, int> PKBInterface::getAllFollowStar() {
    return pkb->followsStarTable->getAllFollowStars();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::unordered_map<int, std::vector<int>> PKBInterface::getAllNext() {
    return pkb->nextTable->getAllNext();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::unordered_map<STMT_NUM, std::unordered_set<STMT_NUM>> PKBInterface::getAllNextStar() {
    return pkb->nextStarTable->getAllNextStar();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::unordered_map<int, std::unordered_set<int>> PKBInterface::getAllAffects() {
    return pkb->affectTable->getAllAffect();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::unordered_map<int, std::unordered_set<int>> PKBInterface::getAllAffectsStar() {
    return pkb->affectStarTable->getAllAffectStar();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::unordered_map<int, std::vector<std::string>> PKBInterface::getAllModifyByStmt() {
    return pkb->modifiesTable->getAllModifiesByStmt();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::unordered_map<std::string, std::vector<std::string>> PKBInterface::getAllModifyByProc() {
    return pkb->modifiesTable->getAllModifiesByProc();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::unordered_map<int, std::vector<int>> PKBInterface::getAllParent() {
    return pkb->parentTable->getAllParents();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::unordered_map<int, std::vector<int>> PKBInterface::getAllParentStar() {
    return pkb->parentStarTable->getAllParentStars();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::unordered_map<int, std::vector<std::string>> PKBInterface::getAllUseByStmt() {
    return pkb->usesTable->getAllUsesByStmt();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::unordered_map<std::string, std::vector<std::string>> PKBInterface::getAllUseByProc() {
    return pkb->usesTable->getAllUsesByProc();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
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

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::vector<std::string> PKBInterface::getAllStmts() {
    return pkb->statementTable->getAllStmts();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::vector<std::string> PKBInterface::getAllReads() {
    return pkb->statementTable->getAllReads();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::vector<std::string> PKBInterface::getAllPrints() {
    return pkb->statementTable->getAllPrints();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::vector<std::string> PKBInterface::getAllCalls() {
    return pkb->statementTable->getAllCalls();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::vector<std::string> PKBInterface::getAllWhiles() {
    return pkb->statementTable->getAllWhiles();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::vector<std::string> PKBInterface::getAllIfs() {
    return pkb->statementTable->getAllIfs();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::vector<std::string> PKBInterface::getAllAssigns() {
    return pkb->statementTable->getAllAssigns();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::vector<std::string> PKBInterface::getAllVariables() {
    return pkb->varTable->getAllVariables();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
std::vector<std::string> PKBInterface::getAllConstants() {
    return pkb->constantTable->getAllConstants();
}

// S1 (Major): DRY - Code structure of method is similar to getAll methods
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


// S1 (Major): DRY - Code structure of method is similar to get___Name methods
std::string PKBInterface::getCallProcName(std::string callLineNumber) {
    int callLine = std::stoi(callLineNumber);
    Statement callStmt = pkb->statementTable->getStmtByLineNumber(callLine);
    return callStmt.calleeProcName;
}

// S1 (Major): DRY - Code structure of method is similar to get___Name methods
std::string PKBInterface::getReadVarName(std::string readLineNumber) {
    int readLine = std::stoi(readLineNumber);
    std::unordered_map<int, std::vector<std::string>> modifiesList = pkb->modifiesTable->getAllModifiesByStmt();
    return modifiesList[readLine].front();
}
// S1 (Major): DRY - Code structure of method is similar to get___Name methods
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

// S1 (Major): DRY - Code structure of method is similar to hasAffects, hasAffectsStar
bool PKBInterface::hasNextStar(STMT_NUM stmt) {
    return pkb->nextStarTable->existNextStar(stmt);
}

// S1 (Major): DRY - Code structure of method is similar to addAffects, addAffectsStar
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

// S1 (Major): DRY - Code structure of method is similar to hasNextStar, hasAffectsStar
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

// S1 (Major): DRY - Code structure of method is similar to addNextStar, addAffectsStar
void PKBInterface::addAffects(STMT_NUM stmt, STMT_NUM affectedStmt) {
    pkb->affectTable->insertAffect(stmt, affectedStmt);
}

std::string PKBInterface::getProcedureNameOf(CFGHeadPtr cfg) {
    return pkb->procedureTable->getProcedureNameOf(cfg);
}

// S1 (Major): DRY - Code structure of method is similar to hasNextStar, hasAffects
bool PKBInterface::hasAffectsStar(STMT_NUM stmt) {
    return pkb->affectStarTable->existAffectStar(stmt);
}

// S1 (Major): DRY - Code structure of method is similar to addNextStar, addAffects
void PKBInterface::addAffectsStar(STMT_NUM stmt, std::unordered_set<STMT_NUM> affectsStarSet) {
    pkb->affectStarTable->insertAffectStar(stmt, affectsStarSet);
}

std::unordered_set<STMT_NUM> PKBInterface::getAllAssignFromProcedure(std::string procName) {
    Procedure proc = pkb->procedureTable->getProcedureByName(procName);
    int startStmt = proc.startingStmtNo;
    int endStmt = proc.endingStmtNo;
    return pkb->statementTable->getAllAssignFromProcedure(startStmt, endStmt);
}


// S1 (Major): DRY - Code structure of method is similar to getNextStar, getAffectsStar
std::unordered_set<STMT_NUM> PKBInterface::getAffects(STMT_NUM stmt) {
    return pkb->affectTable->getAffectedSet(stmt);
}

// S1 (Major): DRY - Code structure of method is similar to getNextStar, getAffects
std::unordered_set<STMT_NUM> PKBInterface::getAffectsStar(STMT_NUM stmt) {
    return pkb->affectStarTable->getAffectedStarSet(stmt);
}

// S1 (Major): DRY - Code structure of method is similar to getAffects, getAffectsStar
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




