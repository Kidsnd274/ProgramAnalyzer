#include "pkb/PKBInterface.h"

template <class T, class Y> class PKBInterfaceStubForDE : public PKBInterface {
public:
    std::unordered_map<T, Y> unorderedMap;

    void addFollows(int stmt1Number, int stmt2Number);
    void addModifies(int stmtNumber, std::string varModified);
    void addModifies(std::string procedureName, std::string varModified);
    void addParent(int parentStmtNumber, int stmtNumber);
    void addParentStar(int parentStmtNumber, int stmtNumber); // might let qps handle in the future
    void addUses(int stmtNumber, std::string variableUsed);
    void addUses(std::string procedureName, std::string variableUsed);
};