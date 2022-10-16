#ifndef SPA_QPS_PKB_INTERFACE_H
#define SPA_QPS_PKB_INTERFACE_H

#include "pkb/PKBInterface.h"
#include "pkb/Statement.h"
#include "type/Argument.h"
#include "Query.h"

class QPS_PKB_Interface {
public:
    static PKBInterface* pkbInterface;

public:
    static void setPKBInterface(PKBInterface* myPKBInterface);

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
    static std::unordered_map<int, int> getAllFollowsRelations();

    /**
     * Call PKB interface to get all parent relations in ParentTable.
     * @return a vector containing all the parent relations.
     */
    static std::unordered_map<int, vector<int>> getAllParentRelations();

    /**
     * Call PKB interface to get all parent* relations in ParentTable.
     * @return a vector containing all the parent* relations.
     */
    static std::unordered_map<int, vector<int>> getAllParentTRelations();


    /**
     * Call PKB interface to get all call relations in CallsTable.
     * @return a vector containing all the calls relations.
     */
    static std::unordered_map<std::string, std::vector<std::string>> getAllCallRelations();

    /**
     * Call PKB interface to get all procedure calls relations in CallsTable.
     * @return a vector containing all the procedure calls relations.
     */
    static std::unordered_map<std::string, std::vector<std::string>> getAllCallTRelations();

    /**
     * Call PKB interface to get all modifies relations in ModifiesTable.
     * @return a vector containing all the modifies relations.
     */
    static std::unordered_map<int, std::vector<std::string>> getAllModifiesRelations();

    /**
     * Call PKB interface to get all procedure modifies relations in ModifiesTable.
     * @return a vector containing all the procedure modifies relations.
     */
    static std::unordered_map<std::string, std::vector<std::string>> getAllModifiesProcRelations();

    /**
     * Call PKB interface to get all uses relations in UsesTable.
     * @return a vector containing all the uses relations.
     */
    static std::unordered_map<int, std::vector<std::string>> getAllUsesRelations();

    /**
     * Call PKB interface to get all procedure uses relations in UsesTable.
     * @return a vector containing all the procedure uses relations.
     */
    static std::unordered_map<std::string, std::vector<std::string>> getAllUsesProcRelations();

    /**
     * Call PKB interface to get all affects relations in AffectsTable.
     * @return a vector containing all the affects relations.
     */
    static std::vector<pair<int, int>> getAllAffectsRelations();

    /**
     * Call PKB interface to get all procedure affects relations in AffectsTable.
     * @return a vector containing all the procedure affects relations.
     */
    static std::vector<pair<int, int>> getAllAffectsProcRelations();

    /**
     * Call PKB interface to get all next relations in NextTable.
     * @return a vector containing all the next relations.
     */
    static std::vector<pair<int, int>> getAllNextRelations();

    /**
     * Call PKB interface to get all procedure xt relations in NextTable.
     * @return a vector containing all the procedure next relations.
     */
    static std::vector<pair<int, int>> getAllNextProcRelations();

    /**
     * Call PKB interface to get all assignments in StatementTable.
     * @return a vector containing the line number of all the assignments.
     */
    static std::vector<std::string> getAllAssigns();


    /**
     * Call PKB interface to get all statement lists.
     * @return a vector of statement list.
     */
    static std::vector<std::vector<Statement>> getAllStmtLists();

    /**
     * Call PKB interface to get all entities of a certain type.
     * @param argument
     * @return
     */
    static std::vector<std::string> getAllEntity(Argument* argument);

    /**
     * Call PKB interface to get the line number of a certain procedure.
     * @param procName the name of procedure
     * @return a string, the line number of given procedure
     */
    static std::string getProcLineNumberByName(std::string procName);

    static std::string getCallProcName(std::string callLineNumber);

    static std::string getReadVarName(std::string readLineNumber);

    static std::string getPrintVarName(std::string printLineNumber);

    static std::string getAttrName(std::string value, WithClause::WithClauseArgument candidate);
};


#endif //SPA_QPS_PKB_INTERFACE_H
