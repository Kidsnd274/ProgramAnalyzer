#include "DesignExtractorInterface.h"
#include "pkb/PKBInterface.h"
class DesignExtractor : public DesignExtractorInterface{
private:
    PKBInterface pkbInterface;
    std::vector<std::shared_ptr<Extractor>> extractorList;
public:
    DesignExtractor(PKBInterface &pkb) {
        pkbInterface = pkb;
    }
    void traverse(std::shared_ptr<ProcedureNode> ptr, std::shared_ptr<Extractor> e);
    void traverse(std::shared_ptr<StatementNode> ptr, std::shared_ptr<Extractor> e);
    void extract(std::shared_ptr<ProcedureNode> p) override;
};