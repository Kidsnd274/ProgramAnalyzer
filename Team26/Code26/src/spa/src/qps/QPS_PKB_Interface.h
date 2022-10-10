#ifndef SPA_QPS_PKB_INTERFACE_H
#define SPA_QPS_PKB_INTERFACE_H

#include "pkb/PKBInterface.h"

class QPS_PKB_Interface {
public:
    static PKBInterface* pkbInterface;

public:
    static void setPKBInterface(PKBInterface* pkbInterface);

    /**
     * Call PKB interface to get the AST TNode of a certain assign statement.
     *
     * @param assignRef The statement reference.
     * @return A pointer of AST TNode.
     */
    static std::shared_ptr<AssignNode> getAssignTNode(std::string assignRef);

    /**
     * Call PKB interface to get all follows relations in FollowsTable.
     * @return a vector containing all the follows relations.
     */
    static std::vector<pair<int, int>> getAllFollowsRelations();

    /**
     * Call PKB interface to get all parent relations in ParentTable.
     * @return a vector containing all the parent relations.
     */
    static std::vector<pair<int, int>> getAllParentRelations();
};


#endif //SPA_QPS_PKB_INTERFACE_H
