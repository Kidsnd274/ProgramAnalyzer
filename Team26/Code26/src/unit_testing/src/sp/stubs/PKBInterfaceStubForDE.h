#include "pkb/PKBInterface.h"

enum class StmtType {
    IF,
    WHILE,
    PRINT,
    CALL,
    ASSIGN,
    READ
};

class PKBInterfaceStubForDE : public PKBInterface {
public:
    std::unordered_map<int, int> followsMap;
    std::unordered_map<int, int> parentMapIntInt;
    std::unordered_multimap<int, int> parentStarMapIntInt;
    std::unordered_multimap<int, std::string> modifiesMapIntString;
    std::unordered_multimap<std::string, std::string> modifiesMapStringString;
    std::unordered_multimap<int, std::string> usesMapIntString;
    std::unordered_multimap<std::string, std::string> usesMapStringString;
    std::unordered_multimap<std::string, std::string> callMapStringString;
    std::unordered_multimap<std::string, std::string> callStarMapStringString;
    std::unordered_map<int, int> statements;
    std::unordered_map<int, StmtType> statementTypeMap;
    std::unordered_map<STMT_NUM, std::unordered_set<STMT_NUM>> nextStarMap;
    std::unordered_map<STMT_NUM, std::unordered_set<STMT_NUM>> affectsMap;
    std::unordered_map<std::string, CFGHeadPtr> procedureToCFG;
    std::unordered_map<STMT_NUM, std::unordered_set<STMT_NUM>> affectsStarMap;
    std::unordered_map<std::string, std::pair<STMT_NUM, STMT_NUM>> procToStmtNums;

    void addFollows(int stmt1Number, int stmt2Number) override;
    void addParent(int parentStmtNumber, int stmtNumber) override;
    void addParentStar(int parentStmtNumber, int stmtNumber) override; // might let qps handle in the future
    void addModifies(int stmtNumber, std::string varModified) override;
    void addModifies(std::string procedureName, std::string varModified) override;
    void addUses(int stmtNumber, std::string variableUsed) override;
    void addUses(std::string procedureName, std::string variableUsed) override;
    //Temporary methods to test Follows*
//    void addReadStatement(int statementNumber, int stmtListNum) override;
    void addAssignStatement(int statementNumber, int stmtListNum, std::shared_ptr<TNode> ptr) override;
//    void addWhileStatement(int statementNumber, int stmtListNum) override;
//    void addIfStatement(int statementNumber, int stmtListNum) override;
//    void addPrintStatement(int statementNumber, int stmtListNum) override;
    void addCallStatement(int statementNumber, int statementListNumber, std::string calleeProcName) override;
    void addCall(std::string procedureName, std::string procedureCalled) override;
    void addCallStar(std::string procedureName, std::string procedureCalled) override;
    std::unordered_set<std::string> getAllVariablesModified(std::string procedureName) override;
    std::unordered_set<std::string> getAllVariablesUsed(std::string procedureName) override;
    std::unordered_set<int> getParentStar(int statementNumber) override;
    std::unordered_set<std::string> getCall(std::string procedure) override;
    std::unordered_set<std::string> getCallStar(std::string procedure) override;

    //for testing Next*
    bool hasNextStar(STMT_NUM stmt) override;
    void addNextStar(STMT_NUM stmt, std::unordered_set<STMT_NUM> nextStarSet) override;
    bool isStatementContainer(STMT_NUM stmt) override;
    bool doesStatementModify(STMT_NUM stmt, std::string varModified) override;
    bool hasAffects(STMT_NUM stmt) override;
    std::string getModifiedVariable(STMT_NUM stmt) override;
    bool isStatementAssign(STMT_NUM stmt) override;
    bool doesStatementUse(STMT_NUM stmt, std::string varUsed) override;
    void addAffects(STMT_NUM stmt, STMT_NUM affectedStmt) override;
    void addProcedure(std::string name, int startingStmtNo, int endingStmtNo, std::shared_ptr<CFGHead> cfg) override;
    std::string getProcedureNameOf(CFGHeadPtr cfg) override;
    bool hasAffectsStar(STMT_NUM stmt) override;
    void addAffectsStar(STMT_NUM stmt, std::unordered_set<STMT_NUM> affectsStarSet) override;
    std::unordered_set<STMT_NUM> getAllAssignFromProcedure(std::string procName) override;
    std::unordered_set<STMT_NUM> getAffects(STMT_NUM stmt) override;
};