#include "QPS_PKB_Interface.h"

PKBInterface* QPS_PKB_Interface::pkbInterface = nullptr;

void QPS_PKB_Interface::setPKBInterface(PKBInterface *myPKBInterface) {
    QPS_PKB_Interface::pkbInterface = myPKBInterface;
}

std::shared_ptr<AssignNode> getAssignTNode(std::string assignRef) {
    return QPS_PKB_Interface::pkbInterface->getAssignTNode(assignRef);
}

std::unordered_map<int, int> QPS_PKB_Interface::getAllFollowsRelations() {
    return QPS_PKB_Interface::pkbInterface->getAllFollow();
}

std::unordered_map<int, vector<int>> QPS_PKB_Interface::getAllParentRelations() {
    return QPS_PKB_Interface::pkbInterface->getAllParent();
}

std::unordered_map<int, vector<int>> QPS_PKB_Interface::getAllParentTRelations() {
    return QPS_PKB_Interface::pkbInterface->getAllParentStar();
}

std::unordered_map<std::string, std::vector<std::string>> QPS_PKB_Interface::getAllCallRelations() {
    return QPS_PKB_Interface::pkbInterface->getAllCall();
}

std::unordered_map<std::string, std::vector<std::string>> QPS_PKB_Interface::getAllCallTRelations() {
        return QPS_PKB_Interface::pkbInterface->getAllCallStar();
}

std::unordered_map<int, std::vector<std::string>> QPS_PKB_Interface::getAllUsesRelations() {
    return QPS_PKB_Interface::pkbInterface->getAllUseByStmt();
}

std::unordered_map<std::string, std::vector<std::string>> QPS_PKB_Interface::getAllUsesProcRelations() {
    return QPS_PKB_Interface::pkbInterface->getAllUseByProc();
}

std::unordered_map<int, std::vector<std::string>> QPS_PKB_Interface::getAllModifiesRelations() {
    return QPS_PKB_Interface::pkbInterface->getAllModifyByStmt();
}

std::unordered_map<std::string, std::vector<std::string>> QPS_PKB_Interface::getAllModifiesProcRelations() {
    return QPS_PKB_Interface::pkbInterface->getAllModifyByProc();
}

std::vector<pair<int, int>> QPS_PKB_Interface::getAllAffectsRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllAffects();
    return {};
}

std::vector<pair<int, int>> QPS_PKB_Interface::getAllAffectsProcRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllAffectsProc();
    return {};
}

std::vector<pair<int, int>> QPS_PKB_Interface::getAllNextRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllNext();
    return {};
}

std::vector<pair<int, int>> QPS_PKB_Interface::getAllNextProcRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllNextProc();
    return {};
}
std::vector<std::string> QPS_PKB_Interface::getAllAssigns() {
    return QPS_PKB_Interface::pkbInterface->getAllAssigns();
}

std::vector<std::vector<Statement>> QPS_PKB_Interface::getAllStmtLists() {
    return QPS_PKB_Interface::pkbInterface->getAllStmtLists();
}

std::shared_ptr<AssignNode> QPS_PKB_Interface::getAssignTNode(std::string assignRef) {
    return pkbInterface->getAssignTNode(assignRef);
}

std::vector<std::string> QPS_PKB_Interface::getAllEntity(Argument *argument) {
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

std::string QPS_PKB_Interface::getProcLineNumberByName(std::string procName) {
    return pkbInterface->getProcLineNumberByName(procName);
}