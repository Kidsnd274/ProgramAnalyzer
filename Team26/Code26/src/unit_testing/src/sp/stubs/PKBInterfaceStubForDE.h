#include "pkb/PKBInterface.h"

class PKBInterfaceStubForDE : public PKBInterface {
public:
    std::unordered_map<int, int> followsMap;
    std::unordered_map<int, int> parentMapIntInt;
    std::unordered_map<int, int> parentStarMapIntInt;
    std::unordered_multimap<int, std::string> modifiesMapIntString;
    std::unordered_multimap<std::string, std::string> modifiesMapStringString;
    std::unordered_multimap<int, std::string> usesMapIntString;
    std::unordered_multimap<std::string, std::string> usesMapStringString;

    void addFollows(int stmt1Number, int stmt2Number) override;
    // TODO: Is there a way to override without making the base method virtual
    void addParent(int parentStmtNumber, int stmtNumber) override;
    void addParentStar(int parentStmtNumber, int stmtNumber) override; // might let qps handle in the future
    void addModifies(int stmtNumber, std::string varModified) override;
    void addModifies(std::string procedureName, std::string varModified) override;
    void addUses(int stmtNumber, std::string variableUsed) override;
    void addUses(std::string procedureName, std::string variableUsed) override;
};