#ifndef SPA_QPS_INTERFACE_H
#define SPA_QPS_INTERFACE_H

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include "pkb/PKBInterface.h"
#include "pkb/Statement.h"
#include "sp/rte/RuntimeExtractor.h"
#include "type/Argument.h"
#include "type/RelationClause.h"
#include "Query.h"

class QPS_Interface {
public:
    static PKBInterface* pkbInterface;
    static RuntimeExtractor* runtimeExtractor;

public:
    static void setPKBInterface(PKBInterface* myPKBInterface);

    static void createRuntimeExtractor();

    static void clearRuntimeExtractor();

    /**
     * Call PKB interface to get the AST TNode of a certain assign statement.
     *
     * @param assignRef The statement reference.
     * @return A pointer of AST TNode.
     */
    static std::shared_ptr<AssignNode> getAssignTNode(std::string assignRef);

    /**
     * Call PKB interface to get all parent relations in ParentTable.
     * @return a vector containing all the parent relations.
     */
    static std::unordered_map<int, std::vector<int>> getAllParentRelations(RelationType relationType);


    /**
     * Call PKB interface to get all follows relations in FollowsTable.
     * @return a vector containing all the follows relations.
     */
    static std::unordered_map<int, int> getAllFollowsRelations();

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
    static std::unordered_set<std::string> getAllEntity(Argument* argument);

    /**
     * Call PKB interface to return the variable used in if/while condition statement.
     * @param containerLineNumber the statement line number of if/while.
     * @return the variable name.
     */
    static std::vector<std::string> getConditionVarNameByStmtNum(std::string containerLineNumber);

    static std::string getAttrName(std::string value, ArgAttrStruct candidate);

    /**
     * Call PKB interface to get the CFGHead of the procedure by passing in
     * one statement in this procedure.
     * @param stmt the given statement.
     * @return a shared_ptr of CFGHead.
     */
    static CFGHeadPtr getCFGHeadPtrByProc(STMT_NUM stmt);

    /**
     * Call PKB interface to get the Procedure by passing in one statement
     * in this procedure.
     * @param stmt the given statement.
     * @return a Procedure.
     */
    static Procedure* getProcByStmt(STMT_NUM stmt);

    /**
     * Call PKB interface to get the list of all procedures.
     * @return a vector of all the procedures.
     */
    static std::vector<Procedure> getProcList();

    /**
     * Check whether PKB nextStarList has the entry stmt.
     * If not, evaluator will call runtimeExtractor to calculate the
     * nextStar of stmt, and PKB will cache the result.
     * @param stmt the given statement to check.
     * @return a bool indicating whether PKB nextStarList has the entry.
     */
    static bool hasNextStar(STMT_NUM stmt);

    /**
     * Call PKB interface to get all the nextStar of a given stmt.
     * @param stmt the given stmt.
     * @return a vector of stmt2 that satisfies next*(stmt, stmt2).
     */
    static std::unordered_set<STMT_NUM> getNextStar(STMT_NUM stmt);
    static std::unordered_set<STMT_NUM> getAffects(STMT_NUM stmt);
    static std::unordered_set<STMT_NUM> getAffectsStar(STMT_NUM stmt);
};

#endif  // SPA_QPS_INTERFACE_H
