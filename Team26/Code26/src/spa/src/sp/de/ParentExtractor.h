#include <memory>
#include <vector>
#include "Extractor.h"

class ParentExtractor : public Extractor {
public:
    explicit ParentExtractor(PKBInterface *pkb) : Extractor(pkb) {}

    void extractFromIf(std::shared_ptr<IfNode> ptr) override;
    void extractFromWhile(std::shared_ptr<WhileNode> ptr) override;
    void extractFromStatementsWithStatementList(int stmtNum, std::vector<std::shared_ptr<StatementNode>> &stmtList);
};
