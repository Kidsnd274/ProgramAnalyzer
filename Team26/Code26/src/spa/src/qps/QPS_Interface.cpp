#include "QPS_Interface.h"

PKBInterface* QPS_Interface::pkbInterface = nullptr;
RuntimeExtractor* QPS_Interface::runtimeExtractor = nullptr;

void QPS_Interface::setPKBInterface(PKBInterface *myPKBInterface) {
    QPS_Interface::pkbInterface = myPKBInterface;
}


void QPS_Interface::createRuntimeExtractor() {
    QPS_Interface::runtimeExtractor = new RuntimeExtractor(QPS_Interface::pkbInterface);
}

std::shared_ptr<AssignNode> getAssignTNode(std::string assignRef) {
    return QPS_Interface::pkbInterface->getAssignTNode(assignRef);
}

std::unordered_map<int, int> QPS_Interface::getAllFollowsRelations() {
    return QPS_Interface::pkbInterface->getAllFollow();
}

std::unordered_map<int, vector<int>> QPS_Interface::getAllParentRelations() {
    return QPS_Interface::pkbInterface->getAllParent();
}

std::unordered_map<int, vector<int>> QPS_Interface::getAllParentTRelations() {
    return QPS_Interface::pkbInterface->getAllParentStar();
}

std::unordered_map<std::string, std::vector<std::string>> QPS_Interface::getAllCallRelations() {
    return QPS_Interface::pkbInterface->getAllCall();
}

std::unordered_map<std::string, std::vector<std::string>> QPS_Interface::getAllCallTRelations() {
        return QPS_Interface::pkbInterface->getAllCallStar();
}

std::unordered_map<int, std::vector<std::string>> QPS_Interface::getAllUsesRelations() {
    return QPS_Interface::pkbInterface->getAllUseByStmt();
}

std::unordered_map<std::string, std::vector<std::string>> QPS_Interface::getAllUsesProcRelations() {
    return QPS_Interface::pkbInterface->getAllUseByProc();
}

std::unordered_map<int, std::vector<std::string>> QPS_Interface::getAllModifiesRelations() {
    return QPS_Interface::pkbInterface->getAllModifyByStmt();
}

std::unordered_map<std::string, std::vector<std::string>> QPS_Interface::getAllModifiesProcRelations() {
    return QPS_Interface::pkbInterface->getAllModifyByProc();
}

std::vector<pair<int, int>> QPS_Interface::getAllAffectsRelations() {
//    return QPS_Interface::pkbInterface->getAllAffects();
    return {};
}

std::vector<pair<int, int>> QPS_Interface::getAllAffectsTRelations() {
//    return QPS_Interface::pkbInterface->getAllAffectsProc();
    return {};
}

std::unordered_map<int, std::vector<int>> QPS_Interface::getAllNextRelations() {
    return QPS_Interface::pkbInterface->getAllNext();
}

std::vector<pair<int, int>> QPS_Interface::getAllNextTRelations() {
//    return QPS_Interface::pkbInterface->getAllNextProc();
    return {};
}
std::vector<std::string> QPS_Interface::getAllAssigns() {
    return QPS_Interface::pkbInterface->getAllAssigns();
}

std::vector<std::vector<Statement>> QPS_Interface::getAllStmtLists() {
    return QPS_Interface::pkbInterface->getAllStmtLists();
}

std::shared_ptr<AssignNode> QPS_Interface::getAssignTNode(std::string assignRef) {
    return pkbInterface->getAssignTNode(assignRef);
}

std::vector<std::string> QPS_Interface::getAllEntity(Argument *argument) {
    switch (argument->argumentType) {
        case Argument::STMT_SYNONYM:
            return pkbInterface->getAllStmts();
        case Argument::READ_SYNONYM:
            return pkbInterface->getAllReads();
        case Argument::PRINT_SYNONYM:
            return pkbInterface->getAllPrints();
        case Argument::CALL_SYNONYM:
            return pkbInterface->getAllCalls();
        case Argument::WHILE_SYNONYM:
            return pkbInterface->getAllWhiles();
        case Argument::IF_SYNONYM:
            return pkbInterface->getAllIfs();
        case Argument::ASSIGN_SYNONYM:
            return pkbInterface->getAllAssigns();
        case Argument::VAR_SYNONYM:
            return pkbInterface->getAllVariables();
        case Argument::CONST_SYNONYM:
            return pkbInterface->getAllConstants();
        case Argument::PROCEDURE_SYNONYM:
            return pkbInterface->getAllProcedures();
        default:
            return {};
    }
}

std::string QPS_Interface::getProcLineNumberByName(std::string procName) {
    return pkbInterface->getProcLineNumberByName(procName);
}

std::string QPS_Interface::getCallProcName(std::string callLineNumber) {
    return pkbInterface->getCallProcName(callLineNumber);
}

std::string QPS_Interface::getReadVarName(std::string readLineNumber) {
    return pkbInterface->getReadVarName(readLineNumber);
}

std::string QPS_Interface::getPrintVarName(std::string printLineNumber) {
    return pkbInterface->getPrintVarName(printLineNumber);
}

std::vector<std::string> QPS_Interface::getConditionVarNameByStmtNum(std::string containerLineNumber) {
    return pkbInterface->getConditionVar(containerLineNumber);
}

std::string QPS_Interface::getAttrName(std::string value, WithClause::WithClauseArgument candidate) {
    if (candidate.attributeType == AttributeType::STMT_LINE_NUMBER
        && candidate.argument.argumentType == Argument::PROCEDURE_SYNONYM) {
        string temp = QPS_Interface::getProcLineNumberByName(value);
        return QPS_Interface::getProcLineNumberByName(value);
    }
    if (candidate.attributeType == AttributeType::PROC_NAME
        && candidate.argument.argumentType == Argument::CALL_SYNONYM) {
        return QPS_Interface::getCallProcName(value);
    }
    if (candidate.attributeType == AttributeType::WITH_VAR_NAME
        && candidate.argument.argumentType == Argument::READ_SYNONYM) {
        return QPS_Interface::getReadVarName(value);
    }
    if (candidate.attributeType == AttributeType::WITH_VAR_NAME
        && candidate.argument.argumentType == Argument::PRINT_SYNONYM) {
        return QPS_Interface::getPrintVarName(value);
    }
    return value;
}

std::string QPS_Interface::getAttrName(std::string value, Query::CandidateStruct candidate) {
    if (candidate.attributeType == AttributeType::STMT_LINE_NUMBER
        && candidate.argument.argumentType == Argument::PROCEDURE_SYNONYM) {
        string temp = QPS_Interface::getProcLineNumberByName(value);
        return QPS_Interface::getProcLineNumberByName(value);
    }
    if (candidate.attributeType == AttributeType::PROC_NAME
        && candidate.argument.argumentType == Argument::CALL_SYNONYM) {
        return QPS_Interface::getCallProcName(value);
    }
    if (candidate.attributeType == AttributeType::WITH_VAR_NAME
        && candidate.argument.argumentType == Argument::READ_SYNONYM) {
        return QPS_Interface::getReadVarName(value);
    }
    if (candidate.attributeType == AttributeType::WITH_VAR_NAME
        && candidate.argument.argumentType == Argument::PRINT_SYNONYM) {
        return QPS_Interface::getPrintVarName(value);
    }
    return value;
}

CFGHeadPtr QPS_Interface::getCFGHeadPtrByProc(STMT_NUM stmt) {
    return QPS_Interface::pkbInterface->getCFGHeadPtrByProc(stmt);
    return nullptr;
}

Procedure* QPS_Interface::getProcByStmt(STMT_NUM stmt) {
    return QPS_Interface::pkbInterface->getProcByStmt(stmt);
}

std::vector<Procedure> QPS_Interface::getProcList() {
    return QPS_Interface::pkbInterface->getProcList();
}

bool QPS_Interface::hasNextStar(STMT_NUM stmt) {
    return QPS_Interface::pkbInterface->hasNextStar(stmt);
}

std::unordered_set<STMT_NUM> QPS_Interface::getNextStar(STMT_NUM stmt) {
    if (!QPS_Interface::hasNextStar(stmt)) {
        CFGHeadPtr cfgHeadPtr = QPS_Interface::getCFGHeadPtrByProc(stmt);
        QPS_Interface::runtimeExtractor->computeNextStar(cfgHeadPtr, stmt);
    }
    return QPS_Interface::pkbInterface->getNextStar(stmt);
}

std::unordered_set<STMT_NUM> QPS_Interface::getAffects(STMT_NUM stmt) {
    bool hasAffects = QPS_Interface::pkbInterface->hasAffects(stmt);
    if (!hasAffects) {
        CFGHeadPtr cfgHeadPtr = QPS_Interface::getCFGHeadPtrByProc(stmt);
        runtimeExtractor->computeAffects(cfgHeadPtr, stmt);
    }
    return QPS_Interface::pkbInterface->getAffects(stmt);
}

std::unordered_set<STMT_NUM> QPS_Interface::getAffectsStar(STMT_NUM stmt) {
    bool hasAffectsStar = QPS_Interface::pkbInterface->hasAffectsStar(stmt);
    if (!hasAffectsStar) {
        CFGHeadPtr cfgHeadPtr = QPS_Interface::getCFGHeadPtrByProc(stmt);
        runtimeExtractor->computeAffectsStar(cfgHeadPtr, stmt);
    }
    return QPS_Interface::pkbInterface->getAffectsStar(stmt);
}