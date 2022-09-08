#include "DesignExtractorInterface.h"
#include "pkb/PKBInterface.h"
class DesignExtractor : public DesignExtractorInterface{
private:
    PKBInterface* pkbInterface;
    std::vector<std::shared_ptr<Extractor>> extractorList;
public:
    DesignExtractor(PKBInterface* pkb) {
        std::shared_ptr<FollowsExtractor> followsExtractor = make_shared<FollowsExtractor>(pkb);
        std::shared_ptr<ParentExtractor> parentExtractor = make_shared<ParentExtractor>(pkb);
        std::shared_ptr<ModifiesExtractor> modifiesExtractor = make_shared<ModifiesExtractor>(pkb);
        std::shared_ptr<UsesExtractor> usesExtractor = make_shared<UsesExtractor>(pkb);
        extractorList = {followsExtractor, parentExtractor, modifiesExtractor, usesExtractor};
        pkbInterface = pkb;
    }
    void traverse(std::shared_ptr<ProcedureNode> ptr, std::shared_ptr<Extractor> e);
    void traverse(std::shared_ptr<StatementNode> ptr, std::shared_ptr<Extractor> e);
    void extract(std::shared_ptr<ProcedureNode> p) override;
};