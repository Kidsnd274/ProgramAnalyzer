#include "pkb/PKBInterface.h"

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
    std::unordered_map<STMT_NUM, std::unordered_set<STMT_NUM>> nextStarCache;

    void addFollows(int stmt1Number, int stmt2Number) override;
    void addParent(int parentStmtNumber, int stmtNumber) override;
    void addParentStar(int parentStmtNumber, int stmtNumber) override; // might let qps handle in the future
    void addModifies(int stmtNumber, std::string varModified) override;
    void addModifies(std::string procedureName, std::string varModified) override;
    void addUses(int stmtNumber, std::string variableUsed) override;
    void addUses(std::string procedureName, std::string variableUsed) override;
    //Temporary methods to test Follows*
    void addReadStatement(int statementNumber, int stmtListNum) override;
    void addAssignStatement(int statementNumber, int stmtListNum, std::shared_ptr<TNode> ptr) override;
    void addWhileStatement(int statementNumber, int stmtListNum) override;
    void addIfStatement(int statementNumber, int stmtListNum) override;
    void addPrintStatement(int statementNumber, int stmtListNum) override;
    void addCall(std::string procedureName, std::string procedureCalled) override;
    void addCallStar(std::string procedureName, std::string procedureCalled) override;
    std::unordered_set<std::string> getAllVariablesModified(std::string procedureName) override;
    std::unordered_set<std::string> getAllVariablesUsed(std::string procedureName) override;
    std::unordered_set<int> getParentStar(int statementNumber) override;
    std::unordered_set<string> getCall(std::string procedure) override;
    std::unordered_set<string> getCallStar(std::string procedure) override;

    //Methods to test Next*
    bool isNextStarComputed(STMT_NUM stmt) override;
    void addAllNextStarFrom(STMT_NUM toAddTo, STMT_NUM toAddFrom) override;
    void addNextStar(STMT_NUM toAddTo, std::unordered_set<STMT_NUM>& toBeAdded) override;
};