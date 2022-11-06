#include <memory>
#include <vector>
#include "Extractor.h"

class FollowsExtractor : public Extractor {
private:
    void addToPkb(std::vector<std::shared_ptr<StatementNode>> stmtList);
public:
    explicit FollowsExtractor(PKBInterface *pkb) : Extractor(pkb) {}

    void extractFromProcedure(std::shared_ptr<ProcedureNode> ptr) override;
    void extractFromIf(std::shared_ptr<IfNode> ptr) override;
    void extractFromWhile(std::shared_ptr<WhileNode> ptr) override;
};

