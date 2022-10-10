#include "QPS_PKB_Interface.h"

std::shared_ptr<AssignNode> getAssignTNode(std::string assignRef) {
    return QPS_PKB_Interface::pkbInterface->getAssignTNode(assignRef);
}

std::vector<pair<int, int>> QPS_PKB_Interface::getAllFollowsRelations() {
//    return QPS_PKB_Interface::pkbInterface->getALLFollows();
}

std::vector<pair<int, int>> QPS_PKB_Interface::getAllParentRelations() {
//    return QPS_PKB_Interface::pkbInterface->getAllParent();
}