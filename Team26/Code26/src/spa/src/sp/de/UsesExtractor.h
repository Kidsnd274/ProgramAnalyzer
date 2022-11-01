#include <memory>
#include <queue>
#include <unordered_set>
#include <string>
#include <vector>
#include "Extractor.h"

class UsesExtractor : public Extractor {
public:
    explicit UsesExtractor(PKBInterface *pkb) : Extractor(pkb) {}

    void extractFromProcedure(std::shared_ptr<ProcedureNode> ptr) override{};
    void extractFromIf(std::shared_ptr<IfNode> ptr) override;
    void extractFromWhile(std::shared_ptr<WhileNode> ptr) override;
    void extractFromRead(std::shared_ptr<ReadNode> ptr) override {};
    void extractFromPrint(std::shared_ptr<PrintNode> ptr) override;
    void extractFromAssign(std::shared_ptr<AssignNode> ptr) override;
    void extractFromExpressionTree(std::shared_ptr<TNode> ptr, bool isCond);
    void extractFromStatementsWithCond(int stmtNumber, std::shared_ptr<TNode> cond);
};
