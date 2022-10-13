#include "QPS_PKB_Interface.h"

void QPS_PKB_Interface::setPKBInterface(PKBInterface *pkbInterface) {
    QPS_PKB_Interface::pkbInterface = pkbInterface;
}

std::shared_ptr<AssignNode> getAssignTNode(std::string assignRef) {
    return QPS_PKB_Interface::pkbInterface->getAssignTNode(assignRef);
}

std::unordered_map<int, vector<int>> QPS_PKB_Interface::getAllParentRelations() {}

std::unordered_map<std::string, std::vector<std::string>> QPS_PKB_Interface::getAllCallRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllCall();
}

std::unordered_map<std::string, std::vector<std::string>> QPS_PKB_Interface::getAllCallTRelations() {
    //    return QPS_PKB_Interface::pkbInterface->getAllCallStar();
}

std::unordered_map<std::string, std::vector<std::string>> QPS_PKB_Interface::getAllUsesProcRelations() {

}

std::unordered_map<std::string, std::vector<std::string>> QPS_PKB_Interface::getAllModifiesProcRelations() {

}

std::unordered_map<int, std::vector<std::string>> QPS_PKB_Interface::getAllUsesRelations() {}

std::unordered_map<int, std::vector<std::string>> QPS_PKB_Interface::getAllModifiesRelations() {}

std::unordered_map<int, vector<int>> QPS_PKB_Interface::getAllParentTRelations() {}

std::unordered_map<int, int> QPS_PKB_Interface::getAllFollowsRelations() {}