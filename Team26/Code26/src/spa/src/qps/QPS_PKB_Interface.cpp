#include "QPS_PKB_Interface.h"

PKBInterface* QPS_PKB_Interface::pkbInterface = nullptr;

void QPS_PKB_Interface::setPKBInterface(PKBInterface *myPKBInterface) {
    QPS_PKB_Interface::pkbInterface = myPKBInterface;
}

std::shared_ptr<AssignNode> getAssignTNode(std::string assignRef) {
    return QPS_PKB_Interface::pkbInterface->getAssignTNode(assignRef);
}

std::unordered_map<int, int> QPS_PKB_Interface::getAllFollowsRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllFollows();
}

std::unordered_map<int, vector<int>> QPS_PKB_Interface::getAllParentRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllParent();
}

std::unordered_map<int, vector<int>> QPS_PKB_Interface::getAllParentTRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllParentT();
}

std::unordered_map<std::string, std::vector<std::string>> QPS_PKB_Interface::getAllCallRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllCall();
}

std::unordered_map<std::string, std::vector<std::string>> QPS_PKB_Interface::getAllCallTRelations() {
    //    return QPS_PKB_Interface::pkbInterface->getAllCallStar();
}

std::unordered_map<int, std::vector<std::string>> QPS_PKB_Interface::getAllUsesRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllUses();
}

std::unordered_map<std::string, std::vector<std::string>> QPS_PKB_Interface::getAllUsesProcRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllUsesProc();
}

std::unordered_map<int, std::vector<std::string>> QPS_PKB_Interface::getAllModifiesRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllModifies();
}

std::unordered_map<std::string, std::vector<std::string>> QPS_PKB_Interface::getAllModifiesProcRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllModifiesProc();
}

std::vector<pair<int, int>> QPS_PKB_Interface::getAllAffectsRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllAffects();
}

std::vector<pair<int, int>> QPS_PKB_Interface::getAllAffectsProcRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllAffectsProc();
}

std::vector<pair<int, int>> QPS_PKB_Interface::getAllNextRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllNext();
}

std::vector<pair<int, int>> QPS_PKB_Interface::getAllNextProcRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllNextProc();
}
std::vector<std::string> QPS_PKB_Interface::getAllAssigns() {
//    return QPS_PKB_Interface::pkbInterface->getAllAssigns();
}

std::vector<std::vector<Statement>> QPS_PKB_Interface::getAllStmtLists() {
//    return QPS_PKB_Interface::pkbInterface->getAllStmtLists();
}

std::shared_ptr<AssignNode> QPS_PKB_Interface::getAssignTNode(std::string assignRef) {
    return std::shared_ptr<AssignNode>();
}