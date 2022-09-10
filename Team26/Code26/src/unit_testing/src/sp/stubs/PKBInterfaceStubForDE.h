#include "pkb/PKBInterface.h"

template <class T, class Y> class PKBInterfaceStubForDE : public PKBInterface {
public:
    std::unordered_map<T, Y> unorderedMap;

    void addFollows(int stmt1Number, int stmt2Number) override;
    // TODO: Is there a way to override without making the base method virtual
    // TODO: Having issues overriding the base method with the methods at the btm
//    void addModifies(int stmtNumber, std::string varModified) override;
//    void addModifies(std::string procedureName, std::string varModified) override;
//    void addParent(int parentStmtNumber, int stmtNumber) override;
//    void addParentStar(int parentStmtNumber, int stmtNumber) override; // might let qps handle in the future
//    void addUses(int stmtNumber, std::string variableUsed) override;
//    void addUses(std::string procedureName, std::string variableUsed) override;
};