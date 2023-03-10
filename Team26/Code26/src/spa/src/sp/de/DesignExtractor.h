#include <memory>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "DesignExtractorInterface.h"
#include "pkb/PKBInterface.h"
#include "CallStatementHandler.h"
#include "sp/SemanticErrorException.h"

class DesignExtractor : public DesignExtractorInterface {
private:
    PKBInterface* pkbInterface;
    std::vector<std::shared_ptr<Extractor>> extractorList;
    std::vector<std::vector<CallStruct>> callList;
    std::unordered_map<std::string, std::pair<int, int>> nameToIndex;
    std::unordered_map<int, std::string> indexToName;
public:
    explicit DesignExtractor(PKBInterface* pkb) {
        std::shared_ptr<FollowsExtractor> followsExtractor = std::make_shared<FollowsExtractor>(pkb);
        std::shared_ptr<ParentExtractor> parentExtractor = std::make_shared<ParentExtractor>(pkb);
        std::shared_ptr<ModifiesExtractor> modifiesExtractor = std::make_shared<ModifiesExtractor>(pkb);
        std::shared_ptr<UsesExtractor> usesExtractor = std::make_shared<UsesExtractor>(pkb);
        extractorList = {followsExtractor, parentExtractor, modifiesExtractor, usesExtractor};
        pkbInterface = pkb;
    }

    bool doesProcedureAlreadyExist(std::string name);
    void addProcedure(std::string name) override;
    void addCallStatement(CallStruct &cs) override;
    void traverse(std::shared_ptr<ProcedureNode> ptr, std::shared_ptr<Extractor> e);
    void traverse(std::shared_ptr<StatementNode> ptr, std::shared_ptr<Extractor> e);
    void extract(std::vector<std::shared_ptr<ProcedureNode>> procedures) override;
};
